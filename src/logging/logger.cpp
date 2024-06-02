#include "logger.hpp"

volatile static bool isEnabled = true;

void disableLogging() {
    isEnabled = false;
}

void enableLogging() {
    isEnabled = true;
}

Logger::Logger() : outputStream(&std::cout), logLevel(INFO) {}

Logger::~Logger() {}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::setOutputStream(std::ostream& stream) {
    outputStream = &stream;
}

void Logger::log(const char* message) {
    log(INFO, message);
}

void Logger::error(const char* message) {
    log(ERROR, message);
}

void Logger::warn(const char* message) {
    log(WARN, message);
}

void Logger::info(const char* message) {
    log(INFO, message);
}

void Logger::debug(const char* message) {
    log(DEBUG, message);
}

void Logger::trace(const char* message) {
    log(TRACE, message);
}

void Logger::log(LogLevel level, const char* message) {
    if (isEnabled && level <= logLevel) {
        if (outputStream) {
            *outputStream << "[" << logLevelToString(level) << "] " << message << std::endl;
        }
    }
}

const char* Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case ERROR: return "ERROR";
        case WARN:  return "WARN";
        case INFO:  return "INFO";
        case DEBUG: return "DEBUG";
        case TRACE: return "TRACE";
        default:    return "UNKNOWN";
    }
}
