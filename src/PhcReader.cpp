#include <iostream>
#include <string>
#include "PhcReader.hpp"
#include <phc.h>


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

        std::cout << "Node: " << deviceName << std::endl;
    }

    void PhcReader::close()
    {
        if ( isOpen_ == true )
        {
            

        }
    }
}
