#pragma once

#include <string>

namespace publicntp {
    class PhcReader {
        public:
            PhcReader(); 

            virtual ~PhcReader(); 

            void open(const std::string& ptpDeviceNode);

            void close();

        protected:
            bool        isOpen_;
            std::string deviceNode_;
    };
}
