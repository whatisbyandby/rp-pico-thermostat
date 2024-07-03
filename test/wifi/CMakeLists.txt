if(ON_TARGET)
    # target_compile_definitions(test-wifi PRIVATE ON_TARGET=1 PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

    # target_link_libraries(test-wifi
    #     pico_stdlib
    # )
else()

file(GLOB TEST_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/wifi/test_wifi_main.cpp
    ${PROJECT_SOURCE_DIR}/test/wifi/test_wifi.cpp
)

file(GLOB SOURCE 
    ${PROJECT_SOURCE_DIR}/src/wifi/wifi.cpp
)

file(GLOB MOCK_SOURCE
    ${PROJECT_SOURCE_DIR}/test/mocks/pico_mocks/pico/cyw43_arch.cpp
    ${PROJECT_SOURCE_DIR}/test/mocks/mock_configuration.cpp
)



add_executable(test-wifi
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)

    
target_include_directories(test-wifi PRIVATE
    ${PROJECT_SOURCE_DIR}/src/wifi
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/test/mocks/pico_mocks
    ${PROJECT_SOURCE_DIR}/src/configuration
)


target_link_libraries(test-wifi
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)




    target_compile_definitions(test-wifi PRIVATE ON_TARGET=0)
endif()

add_test(NAME TestWifi COMMAND test-wifi)
