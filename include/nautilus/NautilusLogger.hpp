#ifndef NAUTILUS_LOGGER_HPP
#define NAUTILUS_LOGGER_HPP

#include "NautilusStatus.hpp"

#include <filesystem>
#include <string>
#include <cmath>
#include <iostream>
#ifndef _WIN32
#include <curses.h>
#include <ncurses.h>
#endif      // _WIN32
#include <fstream>
#include <mutex>
#include <chrono>

namespace nautilus {

    namespace logger {

        extern bool                 loggerInitialized;
        extern std::ofstream        standardLog;
        extern std::mutex           logLock;

        /**
         * Initializes the logger
         * @param _logdir The directory to store the logs. If null, logs will not be written to disk.
         * @return Returns a nautilus::NautilusStatus status code
         */ 
        nautilus::NautilusStatus init(const char* _logdir = nullptr);

        /**
         * Creates a new log entry with status level
         * @param _logEntry The entry to log
         * @param _status The status level
         * @return Returns a nautilus::NautilusStatus status code
         */ 
        nautilus::NautilusStatus log(std::string _logEntry, nautilus::NautilusStatus _status = NAUTILUS_STATUS_OK);

        /**
         * Prints metadata about the application
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus meta(void);

        /**
         * Terminates the logger
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus terminate(void);

    }

}

#endif      // NAUTILUS_LOGGER_HPP