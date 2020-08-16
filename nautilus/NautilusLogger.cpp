#ifndef NAUTILUS_LOGGER_CPP
#define NAUTILUS_LOGGER_CPP

#include "NautilusLogger.hpp"
#include "NautilusAssert.hpp"

namespace nautilus {

    namespace logger {

        bool                loggerInitialized   = false;
        std::ofstream       standardLog;
        std::mutex          logLock;
        auto                start               = std::chrono::system_clock::now();
        namespace           fs                  = std::filesystem;

        NautilusStatus init(const char* _logdir) {
            if(logger::loggerInitialized) return NAUTILUS_STATUS_OK;
            fs::create_directory("logs");
            standardLog.open("logs/nautilus.log", std::ios::trunc);
            logger::loggerInitialized = true;
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus log(std::string _logEntry, NautilusStatus _status) {
            logger::init();
            if(logger::loggerInitialized) {
                auto now = std::chrono::system_clock::now();
                std::chrono::duration< double > elapsedTime = now - logger::start;
                std::string timeStringTerm = std::to_string(elapsedTime.count()) + ": ";
                std::string logString = _logEntry;
                std::string log = timeStringTerm + logString; 
                std::unique_lock< std::mutex > lock(logger::logLock);
                std::cout << log << std::endl;
                standardLog << log << std::endl;
                lock.unlock();
                ASSERT_NAUTILUS(_status);
            }
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus meta() {
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus terminate() {
            logger::log("Terminating...");
            return NAUTILUS_STATUS_OK;
        }

    }

}

#endif      // NAUTILUS_LOGGER_CPP