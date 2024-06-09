

file(GLOB TEST_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/producer/test_producer_main.cpp
    ${PROJECT_SOURCE_DIR}/test/producer/test_producer.cpp
)

file(GLOB SOURCE 
    ${PROJECT_SOURCE_DIR}/src/producer/producer.cpp
)

file(GLOB MOCK_SOURCE
    ${PROJECT_SOURCE_DIR}/test/mocks/mock_wifi.cpp
    ${PROJECT_SOURCE_DIR}/test/mocks/mock_mqtt.cpp
    ${PROJECT_SOURCE_DIR}/test/mocks/mock_json.cpp
)


add_executable(test-producer
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)

    
target_include_directories(test-producer PRIVATE
    ${PROJECT_SOURCE_DIR}/src/producer
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/wifi
    ${PROJECT_SOURCE_DIR}/src/mqtt
    ${PROJECT_SOURCE_DIR}/src/json
)


target_link_libraries(test-producer
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)



if(ON_TARGET)
    target_compile_definitions(test-producer PRIVATE ON_TARGET=1 PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

    target_link_libraries(test-producer
        pico_stdlib
    )
else()
    target_compile_definitions(test-producer PRIVATE ON_TARGET=0)
endif()

add_test(NAME TestProducer COMMAND test-producer)
