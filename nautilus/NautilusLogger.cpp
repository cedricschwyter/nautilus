#ifndef NAUTILUS_LOGGER_CPP
#define NAUTILUS_LOGGER_CPP

#include "NautilusLogger.hpp"

namespace nautilus {

    namespace logger {

        bool                loggerInitialized   = false;
        std::ofstream       standardLog;
        std::mutex          logLock;
        auto                start               = std::chrono::system_clock::now();
        namespace           fs                  = std::filesystem;

        nautilus::NautilusStatus init(const char* _logdir) {
            if(nautilus::logger::loggerInitialized) return NAUTILUS_STATUS_OK;
            fs::create_directory("logs");
            standardLog.open("logs/nautilus.log", std::ios::trunc);
            nautilus::logger::loggerInitialized = true;
            return NAUTILUS_STATUS_OK;
        }

        nautilus::NautilusStatus log(std::string _logEntry, nautilus::NautilusStatus _status) {
            nautilus::logger::init();
            if(nautilus::logger::loggerInitialized) {
                auto now = std::chrono::system_clock::now();
                std::chrono::duration< double > elapsedTime = now - nautilus::logger::start;
                std::string timeStringTerm = std::to_string(elapsedTime.count()) + ": ";
                std::string logString = _logEntry;
                std::string log = timeStringTerm + logString; 
                std::scoped_lock< std::mutex > lock(nautilus::logger::logLock);
                std::cout << log << std::endl;
                standardLog << log << std::endl;
            }
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus meta() {
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus terminate() {
            nautilus::logger::log("Terminating...");
            return NAUTILUS_STATUS_OK;
        }

    }

}

#endif      // NAUTILUS_LOGGER_CPP