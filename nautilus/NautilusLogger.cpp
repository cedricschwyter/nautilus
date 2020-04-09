#ifndef NAUTILUS_LOGGER_CPP
#define NAUTILUS_LOGGER_CPP

#include "NautilusLogger.hpp"

namespace nautilus {

    namespace logger {

        bool                loggerInitialized = false;
        std::ofstream       standardLog;
        std::mutex          logLock;
        WINDOW*             logWindow;
        WINDOW*             metaDataWindow;
        auto                start = std::chrono::system_clock::now();
        namespace fs = std::filesystem;

        NautilusStatus init(const char* _logdir) {
            if(nautilus::logger::loggerInitialized) return NAUTILUS_STATUS_OK;
            fs::create_directory("logs");
            standardLog.open("logs/nautilus.log", std::ios::trunc);
            initscr();
            start_color();
            noecho();
            nautilus::logger::logWindow = newwin(LINES, std::floor(COLS / 2), 0, 1);
            nautilus::logger::metaDataWindow = newwin(std::floor(LINES / 2), std::floor(COLS / 2), std::floor(LINES / 2), 1);
            scrollok(nautilus::logger::logWindow, true);
            scrollok(nautilus::logger::metaDataWindow, true);
            nautilus::logger::loggerInitialized = true;
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus log(std::string _logEntry, NautilusStatus _status) {
            nautilus::logger::init();
            if(nautilus::logger::loggerInitialized) {
                auto now = std::chrono::system_clock::now();
                std::time_t nowT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::string timeString = std::ctime(&nowT);
                std::chrono::duration< double > elapsedTime = now - nautilus::logger::start;
                std::string timeStringTerm = std::to_string(elapsedTime.count()) + " : ";
                std::string logString = _logEntry + "\n";
                std::string log = timeString + logString; 
                std::scoped_lock< std::mutex > lock(nautilus::logger::logLock);
                wmove(nautilus::logger::logWindow, LINES, 1);
                attron(A_UNDERLINE);
                waddstr(nautilus::logger::logWindow, timeStringTerm.c_str()); 
                attroff(A_UNDERLINE);
                waddstr(nautilus::logger::logWindow, logString.c_str());
                wrefresh(nautilus::logger::logWindow);
                standardLog << log << std::endl;
            }
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus meta() {
            if(nautilus::logger::loggerInitialized) {
                auto now = std::chrono::system_clock::now();
                std::time_t nowT = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::string timeString = std::ctime(&nowT);
                std::chrono::duration< double > elapsedTime = now - nautilus::logger::start;
                std::string meta = "Time: " + std::to_string(elapsedTime.count());
                std::scoped_lock< std::mutex > lock(nautilus::logger::logLock);
                wmove(nautilus::logger::metaDataWindow, 0, std::floor(COLS / 2));
                wclear(nautilus::logger::metaDataWindow);
                waddstr(nautilus::logger::metaDataWindow, meta.c_str());
                wrefresh(nautilus::logger::metaDataWindow);
            }
            return NAUTILUS_STATUS_OK;
        }

        NautilusStatus terminate() {
            endwin();
        }

    }

}

#endif      // NAUTILUS_LOGGER_CPP