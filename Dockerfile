FROM whatisbyandby1/pico-build:latest


WORKDIR /pico
COPY . ./rp-pico-thermostat

RUN chmod +x ./rp-pico-thermostat/build.sh


ENTRYPOINT ["/bin/bash",  "./rp-pico-thermostat/build.sh"]


