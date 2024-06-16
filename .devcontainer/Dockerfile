FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    git \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    build-essential \
    python3 \
    python3-pip 

    
WORKDIR /pico

RUN git clone https://github.com/raspberrypi/pico-sdk.git --branch master && cd pico-sdk && git submodule update --init
RUN git clone https://github.com/pimoroni/pimoroni-pico.git --branch main
    
ENTRYPOINT ["/bin/bash"]
