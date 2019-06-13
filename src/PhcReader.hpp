#pragma once

#include <string>
#include <time.h>

// Provide extern wrappers for the C code we call
extern "C" { 
    clockid_t phc_open(char *phc);
    void phc_close(clockid_t clkid);
}

namespace publicntp {

    class PhcReader {

        public:

	        /** 
	         * Constructor.
             *
             * isOpen_ initalized to false, clockId_ initialized to INVALID_CLOCK.
	         */
            PhcReader(); 


	        /**
	         * Destructor.
             *
             * Will ensure clock is cleanly closed before terminating, if it wasn't already
	         */
            virtual ~PhcReader(); 


            /**
             * Open a PHC clock device 
             *
             * @param [in] ptpDeviceNode Full path to a PHC device node (e.g., "/dev/ptp0")
             */
            void open(const std::string& ptpDeviceNode);


            /**
             * Return the current time from an open clock device
             *
             * @return Current time from open PHC device
             */
            timespec getTime() const;


            /**
             * Close an open PHC clock device
             *
             * @note Will throw an exeption if no device is open currently
             */
            void close();


        protected:

            bool        isOpen_;    ///< Indicates if the clock object is currently open
            int         clockId_;   ///< Tracks clock ID handle from most recent phc_open

    };
}
