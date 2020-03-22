#ifndef NAUTILUS_LOGGER_CPP
#define NAUTILUS_LOGGER_CPP

#include "NautilusLogger.hpp"

namespace nautilus {

    namespace logger {

        bool                loggerInitialized = false;
        std::ofstream       standardLog;
        std::mutex          logLock;

        namespace fs = std::filesystem;

        NautilusStatus init(const char* _logdir) {
            if(!nautilus::logger::loggerInitialized) {
                fs::create_directory("logs");
                standardLog.open("logs/nautilus.log", std::ios::trunc);
                nautilus::logger::loggerInitialized = true;
            }
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus log(std::string _logEntry, NautilusStatus _status) {
            if(nautilus::logger::loggerInitialized) {
                std::scoped_lock< std::mutex > lock(nautilus::logger::logLock);
                std::cout << _logEntry << std::endl;
                standardLog << _logEntry << std::endl;
            }
            return NAUTILUS_STATUS_OK;
        }

    }

}

#endif      // NAUTILUS_LOGGER_CPP