#include <iostream>
#include <string>
#include "PhcReader.hpp"
#include "phc.h"


namespace publicntp {

    PhcReader::PhcReader(): 
        isOpen_(false)
    {
    }

    PhcReader::~PhcReader()
    {
        close();
    }

    void PhcReader::open(const std::string&  deviceName )
    {
        close();

        std::cout << "PHC device: " << deviceName << std::endl;

        clockId_ = phc_open(deviceName.c_str());

        if ( clockId_ != CLOCK_INVALID )
        {
            isOpen_ = true;
            std::cout << "Clock opened successfully, clock ID = " << clockId_ << std::endl;
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
            std::cout << "Trying to close clock ID " << clockId_ << std::endl;    

        }
    }
}
