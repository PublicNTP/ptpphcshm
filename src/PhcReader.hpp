#pragma once

#include <string>

// Provide extern wrappers for the C code we call
extern "C" { 
    clockid_t phc_open(char *phc);
}

namespace publicntp {
    class PhcReader {
        public:
            PhcReader(); 
            virtual ~PhcReader(); 
            void open(const std::string& ptpDeviceNode);
            void close();

        protected:
            bool        isOpen_;
            int         clockId_;
    };
}
