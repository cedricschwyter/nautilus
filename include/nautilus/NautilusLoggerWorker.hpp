#ifndef NAUTILUS_LOGGER_WORKER_HPP
#define NAUTILUS_LOGGER_WORKER_HPP

#include <iostream>
#include <fstream>

class NautilusLoggerWorker {
public:

    /**
     * Default constructor
     */ 
    NautilusLoggerWorker(void) = default;

    /**
     * Overload invocation operator as class serves as functor to start a new thread
     */ 
    void operator()(void);

    /**
     * Executes the logging operations
     * @param _msg The log message
     * @param _lvl The message level
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus log(std::string _msg, NautilusStatus _lvl);

    /**
     * Default destructor
     */ 
    ~NautilusLoggerWorker(void) = default;

};

#endif      // NAUTILUS_LOGGER_WORKER_HPP