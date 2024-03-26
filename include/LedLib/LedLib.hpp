#pragma once
#include <vector>
#include "effects/LedEffect.hpp"
#include "main.h"
namespace LedLib
{
    struct RGB
    {
        int red;
        int green;
        int blue;
    };

    struct HSV
    {
        double hue = 0;
        double saturation = 0;
        double value = 0;
    };
    class LedLib
    {
    public:
        pros::ADILED strip;
        int addEffect(LedEffect *customEffect);
        void updateEffects();
        void setActiveEffect(int active);
        int size;

        /**
         * @brief Construct a new Led object
         *
         * @note DO NOT USE. WILL NOT WORK
         *
         */
        LedLib();

        /**
         * @brief Construct a new Led object
         *
         * @param adiport 1-8 representing Triports A-H
         * @param length 1-64 representing the length of the LEDs
         *
         * @throws StripSizeTooLarge if size is > 64
         */
        LedLib(uint8_t adiport, int length);

        /**
         * @brief Construct a new Led object
         *
         * @param smartport 1-21 representing SmartPorts 1-21
         * @param adiport 1-8 representing Triports A-H
         * @param length 1-64 representing the length of the LEDs
         *
         * @throws StripSizeTooLarge if size is > 64
         */
        LedLib(uint8_t smartport, uint8_t adiport, int length);

        /**
         * @brief Set all leds to a given RGB color
         *
         * @param rgb an RGB value represented as a struct
         */
        void setAll(RGB rgb);

        /**
         * @brief Set all leds to a given RGB color
         *
         * @param hsv an HSV value represented as a struct
         */
        void setAll(HSV hsv);

        /**
         * @brief Set all LEDs to a specified color loopy style
         *
         * If your LED strip is being b*tchy about setting all the colors at once (like mine do), call this function instead.
         *
         * @param rgb
         */
        void setAllButchy(RGB rgb);

        /**
         * @brief Set all LEDs to a specified color loopy style
         *
         * If your LED strip is being b*tchy about setting all the colors at once (like mine do), call this function instead.
         *
         * @param hsv a HSV struct
         */
        void setAllButchy(HSV hsv);

        /**
         * @brief Set a given pixel to a specified color
         *
         * @param rgb the RGB color to set the strip to
         * @param index the index of the LED
         */
        void setPixel(RGB rgb, uint8_t index);

        /**
         * @brief Set a given pixel to a specified color
         *
         * @param hsv rgb the RGB color to set the strip to
         * @param index the index of the LED
         */
        void setPixel(HSV hsv, uint8_t index);

        /// Static Functions

        /**
         * @brief
         *
         * @note Credits to https://gist.github.com/peacefixation/5eeb6e992a012ea2f42cd5419df65ea7
         */
        static RGB lerpRGB(RGB color1, RGB color2, double scale);


        static HSV lerpHSV(HSV color1, HSV color2, double scale);
        /**
         * @brief Converts RGB to HSV
         *
         * @param rgb The RGB struct to convert from
         * @return hsv A HSV struct
         */
        static HSV RGBtoHSV(RGB rgb);

        /**
         * @brief Converts HSV to RGB
         *
         * @param hsv The HSV struct to convert from
         * @return A HSV struct
         */
        static RGB HSVtoRGB(HSV hsv);

        /**
         * @brief uint32_t Color to RGB
         *
         * @param color the Color to Convert
         * @return RGB
         */
        static RGB UINT32toRGB(uint32_t color);

        /**
         * @brief uint32_t Color to RGB
         *
         * @param color the Color to Convert
         * @return HSV
         */
        static HSV UINT32toHSV(uint32_t color);

        /**
         * @brief Converts RGB to HSV
         *
         * @param rgb The RGB struct to convert from
         * @return A uint32_t color
         */
        static uint32_t RGBtoUINT32(RGB rgb);

        /**
         * @brief Converts HSV to RGB
         *
         * @param hsv The HSV struct to convert from
         * @return A uint32_t color
         */
        static uint32_t HSVtoUINT32(HSV hsv);

        
        std::vector<LedEffect *> effects;
        int activeEffect;
    };
};