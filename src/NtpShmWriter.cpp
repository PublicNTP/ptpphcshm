#include <iostream>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include "NtpShmWriter.hpp"
#include "NtpShmTimeStruct.hpp"

namespace publicntp {

    bool NtpShmWriter::open(const int segmentNumber)
    {
        bool retVal = false;
        const int sharedMemoryFlags = 0;
        if ( (segmentNumber >= 0) && (segmentNumber <= 9) )
        {
            // Get a handle to it
            shmHandle_ = shmget(ntpShmKeyBase_ + segmentNumber, 
                sizeof(shmTime), 0644|IPC_CREAT);

            if ( shmHandle_ == -1 )
            {
                std::cerr << "shmget call failed" << std::endl;
                return retVal;
            }


            // Now attach to the handle
            pShmStruct_ = reinterpret_cast<shmTime*>(shmat( shmHandle_, nullptr, sharedMemoryFlags));

            // Is a forced cast here ugly? Yes. 
            // Do I know any better way? Not at the moment.
            if ( pShmStruct_ == (shmTime*)-1 )
            {
                std::cerr << "shmat call failed" << std::endl;
                return retVal;
            }

            // Do some initial population of the shared memory region
            std::memset( pShmStruct_, 0, sizeof(shmTime) );
            pShmStruct_->mode = 1;
            pShmStruct_->precision = -5;
            pShmStruct_->nsamples = 3;

            segmentNumber_ = segmentNumber;
            isOpen_ = true;
            retVal = true;
            std::cout << "SHM segment " << segmentNumber_ << " opened successfully" << std::endl;
        }

        return retVal;
    }


    bool NtpShmWriter::write(
        const timespec& phcTime,
        const timespec& sysTime ) const
    {
        // Increment times this shared memory structure has been read or written
        pShmStruct_->count++;

        // Set the clock (meaning "read from PHC") values in the struct
        pShmStruct_->clockTimeStampSec  = phcTime.tv_sec;
        pShmStruct_->clockTimeStampUSec = phcTime.tv_nsec * 1000;
        pShmStruct_->clockTimeStampNSec = phcTime.tv_nsec;

        // Set the receive timestamps (meaning "what the system clock read when we got the PHC clock values")
        pShmStruct_->receiveTimeStampSec  = sysTime.tv_sec;
        pShmStruct_->receiveTimeStampUSec = sysTime.tv_nsec * 1000;
        pShmStruct_->receiveTimeStampNSec = sysTime.tv_nsec;

        // Set precision -- supposedly nanosecond accuracy, so let's say 2^-20 (each tick is ~ 0.000009)
        pShmStruct_->precision = -20;

        // We can't know a damn thing about leap seconds
        pShmStruct_->leap = 0;  // aka "LEAP_NOWARNING"

        // Bump the count one more time, this way people read twice and if it hasn't changed, they know
        //      they got consistent results
        pShmStruct_->count++;
         
        // Finally set the valid bit so people will read it
        pShmStruct_->valid = 1;

        return true;
    }

    void NtpShmWriter::close()
    {
        if ( isOpen_ == true )
        {
            std::cout << "Closed NTP SHM segment " << segmentNumber_ << std::endl;
            segmentNumber_ = -1;
            isOpen_ = false;
        }
    }

}
