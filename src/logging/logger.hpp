#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <ostream>

void disableLogging();
void enableLogging();

class Logger {
public:
    enum LogLevel {
        ERROR,
        WARN,
        INFO,
        DEBUG,
        TRACE
    };

    Logger();
    ~Logger();

    void setLogLevel(LogLevel level);
    void setOutputStream(std::ostream& stream);

    void log(const char* message);
    void error(const char* message);
    void warn(const char* message);
    void info(const char* message);
    void debug(const char* message);
    void trace(const char* message);

private:
    LogLevel logLevel;
    std::ostream* outputStream;

    void log(LogLevel level, const char* message);
    const char* logLevelToString(LogLevel level);
};

#endif // LOGGER_HPP
