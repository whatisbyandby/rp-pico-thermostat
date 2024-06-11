

file(GLOB TEST_SOURCE 
    ${PROJECT_SOURCE_DIR}/test/wifi/test_wifi_main.cpp
    ${PROJECT_SOURCE_DIR}/test/wifi/test_wifi.cpp
)

file(GLOB SOURCE 
    ${PROJECT_SOURCE_DIR}/src/wifi/wifi.cpp
)

file(GLOB MOCK_SOURCE
    ${PROJECT_SOURCE_DIR}/test/mocks/pico/cyw43_arch.cpp
)



add_executable(test-wifi
    ${SOURCE}
    ${TEST_SOURCE}
    ${MOCK_SOURCE}
)

    
target_include_directories(test-wifi PRIVATE
    ${PROJECT_SOURCE_DIR}/src/wifi
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/test/mocks
)


target_link_libraries(test-wifi
    CppUTest::CppUTest
    CppUTest::CppUTestExt
)



if(ON_TARGET)
    target_compile_definitions(test-wifi PRIVATE ON_TARGET=1 PICO_CXX_DISABLE_ALLOCATION_OVERRIDES)

    target_link_libraries(test-wifi
        pico_stdlib
    )
else()
    target_compile_definitions(test-wifi PRIVATE ON_TARGET=0)
endif()

add_test(NAME TestWifi COMMAND test-wifi)
