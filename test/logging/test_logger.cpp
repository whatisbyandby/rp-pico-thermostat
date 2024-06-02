#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport.h>
#include "logger.hpp"
#include <sstream>

static Logger *logger;

TEST_GROUP(LoggingTestGroup)
{
    void setup()
    {
        logger = new Logger();
       
    }

    void teardown()
    {   
        mock().checkExpectations();
        mock().clear();
        delete logger;
    }
};

TEST(LoggingTestGroup, TestLogger_Error)
{

    enableLogging();

    std::ostringstream oss;
    
    logger->setOutputStream(oss);

    logger->setLogLevel(Logger::ERROR);

    logger->error("Error message");

    STRCMP_EQUAL("[ERROR] Error message\n", oss.str().c_str());

    
}

TEST(LoggingTestGroup, TestLogger_Warn)
{
    enableLogging();

    std::ostringstream oss;
    
    logger->setOutputStream(oss);

    logger->setLogLevel(Logger::WARN);

    logger->warn("Warning message");

    STRCMP_EQUAL("[WARN] Warning message\n", oss.str().c_str());

}

TEST(LoggingTestGroup, TestLogger_Info)
{

    enableLogging();

    std::ostringstream oss;
    
    logger->setOutputStream(oss);

    logger->setLogLevel(Logger::INFO);

    logger->info("Info message");

    STRCMP_EQUAL("[INFO] Info message\n", oss.str().c_str());

}

TEST(LoggingTestGroup, TestLogger_Debug)
{

    enableLogging();

    std::ostringstream oss;
    
    logger->setOutputStream(oss);

    logger->setLogLevel(Logger::DEBUG);

    logger->debug("Debug message");

    STRCMP_EQUAL("[DEBUG] Debug message\n", oss.str().c_str());

}

TEST(LoggingTestGroup, TestLogger_Trace)
{
    enableLogging();

    std::ostringstream oss;
    
    logger->setOutputStream(oss);

    logger->setLogLevel(Logger::TRACE);

    logger->trace("Debug message");

    STRCMP_EQUAL("[TRACE] Debug message\n", oss.str().c_str());

}

TEST(LoggingTestGroup, TestLogger_Disabled)
{   
    enableLogging();

    std::ostringstream oss;
    
    logger->setOutputStream(oss);

    logger->setLogLevel(Logger::TRACE);

    disableLogging();

    logger->trace("Debug message");

    CHECK_EQUAL(oss.str().empty(), true);

}