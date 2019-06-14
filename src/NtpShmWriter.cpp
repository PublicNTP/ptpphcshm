#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "NtpShmWriter.hpp"
#include "NtpShmTimeStruct.hpp"

namespace publicntp {

    bool NtpShmWriter::open(const int segmentNumber)
    {
        bool retVal = false;
        if ( (segmentNumber >= 0) && (segmentNumber <= 9) )
        {
            shmHandle_ = shmget(ntpShmKeyBase_ + segmentNumber, 
                sizeof(shmTime), 0600|IPC_CREAT);

            segmentNumber_ = segmentNumber;
            isOpen_ = true;
            retVal = true;

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
            segmentNumber_ = -1;
            isOpen_ = false;
        }
    }

}
