#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <time.h>
#include "main.hpp"
#include "PhcReader.hpp"
#include "NtpShmWriter.hpp"


int main(int argc, char** argv)
{
    validateArgCount(argc, argv);

    publicntp::PhcReader phcReader;
    phcReader.open(argv[1]);

    publicntp::NtpShmWriter ntpShmWriter;
    ntpShmWriter.open( std::atoi(argv[2]) );

    timespec phcTime;
    timespec sysTime;

    while ( true ) 
    {
        if ( phcReader.getTime(phcTime, sysTime) == true )
        {
            // Get current time
            ntpShmWriter.write(phcTime, sysTime);
        }
        std::this_thread::sleep_for( std::chrono::seconds(1) );
    }

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
