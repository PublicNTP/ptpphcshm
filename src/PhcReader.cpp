#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <time.h>
#include <limits>
#include <chrono>
#include "PhcReader.hpp"
#include "phc.h"


namespace publicntp {

    PhcReader::PhcReader(): 
        isOpen_(false),
        clockId_(CLOCK_INVALID)
    { } 

    PhcReader::~PhcReader()
    {
        close();
    }

    // TODO: throw an exception if this fails
    void PhcReader::open(const std::string&  deviceName )
    {
        close();

        std::cout << "PHC device: " << deviceName << std::endl;

        clockId_ = phc_open( const_cast<char*>(deviceName.c_str()) );

        if ( clockId_ != CLOCK_INVALID )
        {
            isOpen_ = true;
            std::cout << "Clock opened successfully" << std::endl;
        }
        else
        {
            std::cerr << "Clock open failed" << std::endl;
        }
    }

    void PhcReader::close()
    {
        if ( isOpen_ == true )
        {
            phc_close(clockId_);
            clockId_ = CLOCK_INVALID;
            std::cout << "Clock closed" << std::endl;
            isOpen_ = false;
        }
    }

    bool PhcReader::getTime(
        std::uint64_t& phcNsSinceEpoch,
        std::uint64_t& sysNsSinceEpoch ) const
    {
        bool retVal = false;

        if ( isOpen_ == true )
        {
            timespec phcTimespec;

            // Zero out all bytes of the structure before reading into it
            std::memset( &phcTimespec, 0, sizeof(timespec) );

            if ( clock_gettime(clockId_, &phcTimespec) == 0 )
            {
                phcNsSinceEpoch = (phcTimespec.tv_sec * NS_IN_SECOND) + phcTimespec.tv_nsec;

                const auto sysTimeChrono = std::chrono::system_clock::now();
                sysNsSinceEpoch = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    sysTimeChrono.time_since_epoch()).count();

                std::cout << "Read clock successfully: " << phcTimespec.tv_sec <<
                    "." << phcTimespec.tv_nsec << std::endl;

                retVal = true;
            }
            else
            {
                // TODO: error in system call
                std::cerr << "Could not read PHC clock!" << std::endl;
            }
        }
        else
        {
            // TODO: throw exception
            std::cerr << "Tried to read clock when clock wasn't open!" << std::endl;
        }

        return retVal;
    }
}
