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
            if(nautilus::logger::loggerInitialized) return NAUTILUS_STATUS_OK;
            fs::create_directory("logs");
            standardLog.open("logs/nautilus.log", std::ios::trunc);
            nautilus::logger::loggerInitialized = true;
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus log(std::string _logEntry, NautilusStatus _status) {
            if(nautilus::logger::loggerInitialized) {
                static auto start = std::chrono::system_clock::now();
                auto now = std::chrono::system_clock::now();
                std::time_t nowT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::string timeString = std::ctime(&nowT);
                std::chrono::duration< double > elapsedTime = now - start;
                std::string log = timeString + "RT: " + std::to_string(elapsedTime.count()) + " === " + _logEntry; 
                std::scoped_lock< std::mutex > lock(nautilus::logger::logLock);
                std::cout << log << std::endl;
                standardLog << log << std::endl;
            }
            return NAUTILUS_STATUS_OK;
        }

    }

}

#endif      // NAUTILUS_LOGGER_CPP