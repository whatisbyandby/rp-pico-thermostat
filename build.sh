
export PICO_SDK_PATH=/pico/pico-sdk
cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DPIMORONI_PICO_PATH:STRING=/pico/pimoroni-pico -DTARGET_ARCH:STRING=aarch64 -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/aarch64-linux-gnu-gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/aarch64-linux-gnu-g++ -S/pico/rp-pico-thermostat -B/pico/rp-pico-thermostat/build/aarch64
cmake --build /pico/rp-pico-thermostat/build/aarch64 --config Debug --target all -- -j 4

ctest --test-dir /pico/rp-pico-thermostat/build/aarch64 --output-on-failure

cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DPIMORONI_PICO_PATH:STRING=/pico/pimoroni-pico -DTARGET_ARCH:STRING=arm -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/arm-none-eabi-g++ -S/pico/rp-pico-thermostat -B/pico/rp-pico-thermostat/build/arm
cmake --build /pico/rp-pico-thermostat/build/arm --config Debug --target all -- -j 4


