

file(GLOB_RECURSE TEST_SOURCE ${PROJECT_SOURCE_DIR}/test/json/*.cpp)
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/json/*.cpp)


add_executable(test-json
    ${TEST_SOURCE}
    ${SOURCE}
)

target_include_directories(test-json PRIVATE
    ${PROJECT_SOURCE_DIR}/src/json
    ${PROJECT_SOURCE_DIR}/src/common
)

target_link_libraries(test-json
    CppUTest::CppUTest
    CppUTest::CppUTestExt
    json_maker
)

if(ON_TARGET)
    target_compile_definitions(test-json PRIVATE
        ON_TARGET=1
        PICO_CXX_DISABLE_ALLOCATION_OVERRIDES
    )

    target_link_libraries(test-json
        pico_stdlib
    )

else()
    target_compile_definitions(test-json PRIVATE ON_TARGET=0)
endif()

# Add the test to CTest
add_test(NAME TestJson COMMAND test-json)

