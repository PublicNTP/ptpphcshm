#include <iostream>
#include <cstdlib>
#include "main.hpp"
#include "PhcReader.hpp"
#include "NtpShmWriter.hpp"


int main(int argc, char** argv)
{
    validateArgCount(argc, argv);

    publicntp::PhcReader phcReader();

    publicntp::NtpShmWriter ntpShmWriter();



    return 0;
}


void validateArgCount(const int argc, char** argv)
{
    if ( argc != 3 )
    {
        std::cerr << "Usage: " << argv[0] << " <PTP device node, e.g. \"/dev/ptp0\"> "
            << " <SHM segment number (0-2)>" << std::endl;

        std::exit(1);
    }
}
