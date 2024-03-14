#pragma once

#include "main.h"

namespace LedLib {

    class StripSizeTooLarge : public std::exception {
        public:
    char * what () {
            return "Strip Size is outside specified range 1-64";
        }
    };

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

        const int size;
        pros::ADILED strip;

        
        /**
         * @brief Construct a new Led object
         * 
         * @param adiport 1-8 representing Triports A-H
         * @param length 1-64 representing the length of the LEDs
         *
         * @throws StripSizeTooLarge if size is > 64
         */
        Led(uint8_t adiport, int length);

        /**
         * @brief Construct a new Led object
         * 
         * @param smartport 1-21 representing SmartPorts 1-21
         * @param adiport 1-8 representing Triports A-H
         * @param length 1-64 representing the length of the LEDs
         *
         * @throws StripSizeTooLarge if size is > 64
         */
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

        /**
         * @brief Sets the entire RGB strip to a specified Graident
         * 
         * @param colora Color Represented as a 6 digit hex code (0xFF00FF)
         * @param colorb Color Represented as a 6 digit hex code (0xFF00FF)
         *
         * @note Converts RGB to uint32_t then calls setGraident(uint32_t, uint32_t) for simplicity
         */
        setGraident(uint32_t colora, uint32_t colorb);

        /**
         * @brief Sets the entire RGB strip to a specified Graident
         *
         * @param colora Color Represented as an HSV struct
         * @param colorb Color Represented as an HSV struct
         *
         * @note Converts RGB to uint32_t then calls setGraident(uint32_t, uint32_t) for simplicity
         */
        setGraident(HSV colora, HSV colorb);

        /**
         * @brief Sets the entire RGB strip to a specified Graident
         * 
         * @param colora Color Represented as an RGB struct
         * @param colorb Color Represented as an RGB struct
         *
         * @note Converts RGB to uint32_t then calls setGraident(uint32_t, uint32_t) for simplicity
         */
        setGraident(RGB colora, RGB colorb);


        /// Static Functions

        /**
         * @brief 
         * 
         * @note Credits to https://gist.github.com/peacefixation/5eeb6e992a012ea2f42cd5419df65ea7
         */
        static lerpRGB(uint32_t color1, uint32_t color2);
    }
}