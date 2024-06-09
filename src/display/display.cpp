#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>

#include "display.hpp"

#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;

extern unsigned char _binary_fox_tga_start[];

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

int display_init()
{
    graphics.set_font(&font8);

    Pen BG = graphics.create_pen(120, 40, 60);
    Pen WHITE = graphics.create_pen(255, 255, 255);


    uint32_t i = 0;
    while (true)
    {
       
    }

    return 0;
}

void update() {
 // Do Something
};