#ifndef NAUTILUS_LOGGER_HPP
#define NAUTILUS_LOGGER_HPP

#include "Nautilus.hpp"

#include <filesystem>
#include <fstream>
#include <mutex>

namespace nautilus {

    namespace logger {

        extern bool                 loggerInitialized;
        extern std::ofstream        standardLog;
        extern std::mutex           logLock;

        /**
         * Initializes the logger
         * @param _logdir The directory to store the logs. If null, logs will not be written to disk.
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus init(const char* _logdir = nullptr);

        /**
         * Creates a new log entry with status level
         * @param _logEntry The entry to log
         * @param _status The status level
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus log(std::string _logEntry, NautilusStatus _status = NAUTILUS_STATUS_OK);

    }

}

#endif      // NAUTILUS_LOGGER_HPP