#pragma once

#include <cstdint>
#include "NtpShmTimeStruct.hpp"

namespace publicntp {

    class NtpShmWriter 
    {
        public:
            NtpShmWriter():
                segmentNumber_(-1),
                isOpen_(false), 
                shmHandle_(0),
                pShmStruct_(nullptr) { }

            virtual ~NtpShmWriter() { close(); }

            bool open(const int segmentNumber);

            bool write(const std::uint64_t phcTime, const std::uint64_t sysTime) const;

            void close();

        protected:
            int                 segmentNumber_;     ///< Shared memory segment number 
            bool                isOpen_;            ///< Do we have a shared memory segment open currently?
            static const int    ntpShmKeyBase_ = 0x4E545030; ///< The magic key used for NTP segment 0 (+1 for SHM1, +2 for SHM2, etc.)
            int                 shmHandle_;
            shmTime*            pShmStruct_;

            static const std::uint64_t  NS_IN_SECOND = 1000000000;
    };
}
