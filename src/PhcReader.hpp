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
            PhcReader(); 
            virtual ~PhcReader(); 
            void open(const std::string& ptpDeviceNode);
            timespec getTime() const;
            void close();

        protected:
            bool        isOpen_;
            int         clockId_;
    };
}
