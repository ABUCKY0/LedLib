#pragma once

#include "main.h"

namespace LedLib {
    struct RGB {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    }

    struct HSV {
        double hue;
        double saturation;
        double value;
    }

    class Led {
        public:
        
        Led(uint8_t adiport, int length);
        Led(uint8_t smartport, uint8_t adiport, int length);

        /**
         * @brief Set all leds to a given RGB color
         * 
         * @param rgb an RGB value represented as a struct
         */
        setAll(RGB rgb);

        /**
         * @brief Set all leds to a given RGB color
         * 
         * @param hsv an HSV value represented as a struct
         *
         * @note Converts HSV to RGB, then calls setAll(RGB) for simplicity
         */
        setAll(HSV hsv);

        /**
         * @brief Set all LEDs to a specified color loopy style
         *
         * If your LED strip is being b*tchy about setting all the colors at once (like mine do), call this function instead.
         * 
         * @param rgb 
         */
        setAllButchy(RGB rgb);

        /**
         * @brief Set all LEDs to a specified color loopy style
         *
         * If your LED strip is being b*tchy about setting all the colors at once (like mine do), call this function instead.
         * 
         * @param hsv a HSV struct
         * @note Converts to RGB, then calls setAllButchy(RGB) for simplicity
         */
        setAllButchy(RGB hsv);

        /**
         * @brief Set a given pixel to a specified color
         * 
         * @param rgb the RGB color to set the strip to
         * @param index the index of the LED
         */
        setPixel(RGB rgb, uint8_t index);

        /**
         * @brief Set a given pixel to a specified color 
         * 
         * @param hsv rgb the RGB color to set the strip to
         * @param index the index of the LED
         *
         * @note Converts HSV to RGB, then calls setPixel(RGB) for simplicity
         */
        setPixel(HSV hsv, uint8_t index);
    }
}