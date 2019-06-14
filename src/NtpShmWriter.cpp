#include <iostream>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
                sizeof(shmTime), 0600|IPC_CREAT);

            // Now attach to the handle
            pShmStruct_ = reinterpret_cast<shmTime*>(shmat( shmHandle_, nullptr, sharedMemoryFlags));

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

        return false;
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
