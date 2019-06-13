#include <iostream>
#include <string>
#include <cstring>
#include <time.h>
#include <limits>
#include "PhcReader.hpp"
#include "phc.h"


namespace publicntp {

    PhcReader::PhcReader(): 
        isOpen_(false),
        clockId_(CLOCK_INVALID)
    {
    }

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

    timespec PhcReader::getTime() const
    {
        timespec timeSpec = { 0, 0 };

        if ( isOpen_ == true )
        {

            // Zero out all bytes of the structure
            std::memset( &timeSpec, 0, sizeof(timeSpec) );

            if ( clock_gettime(clockId_, &timeSpec) == 0 )
            {
                std::cout << "Read clock successfully!" << std::endl;
                // Set seconds
                std::cout << "Raw time from system call: " << timeSpec.tv_sec <<
                    "." << timeSpec.tv_nsec << std::endl;
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

        return timeSpec;
    }
}
