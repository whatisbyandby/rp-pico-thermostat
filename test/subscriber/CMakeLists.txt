

file(GLOB TEST_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/subscriber/test_subscriber_main.cpp
    ${PROJECT_SOURCE_DIR}/test/subscriber/test_subscriber.cpp
)

file(GLOB SOURCE 
    ${PROJECT_SOURCE_DIR}/src/subscriber/subscriber.cpp
)

file(GLOB MOCK_SOURCE
    ${PROJECT_SOURCE_DIR}/test/mocks/mock_wifi.cpp
    ${PROJECT_SOURCE_DIR}/test/mocks/mock_mqtt.cpp
    ${PROJECT_SOURCE_DIR}/test/mocks/mock_json.cpp
)


add_executable(test-subscriber
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)

    
target_include_directories(test-subscriber PRIVATE
    ${PROJECT_SOURCE_DIR}/src/subscriber
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/wifi
    ${PROJECT_SOURCE_DIR}/src/mqtt
    ${PROJECT_SOURCE_DIR}/src/json
)


target_link_libraries(test-subscriber
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)



if(ON_TARGET)
    target_compile_definitions(test-subscriber PRIVATE ON_TARGET=1 PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

    target_link_libraries(test-subscriber
        pico_stdlib
    )
else()
    target_compile_definitions(test-subscriber PRIVATE ON_TARGET=0)
endif()

add_test(NAME TestSubscriber COMMAND test-subscriber)
