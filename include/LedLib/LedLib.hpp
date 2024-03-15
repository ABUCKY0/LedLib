#pragma once

#include "main.h"

namespace LedLib
{
    enum LEDMode {
        LEDOff = 0,
        LEDManual = 1, // When the user gets the buffer or when a pixel is manually set by the user.
        LEDFullRainbow = 2, // When The Strip is set to be all one color rainbow
        LEDOffsetRainbow = 3 // When each pixel is a slightly different color;

    };

    class StripSizeTooLarge : public std::exception
    {
    public:
        char *what()
        {
            return "Strip Size is outside specified range 1-64";
        }
    };

    struct RGB
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    struct HSV
    {
        double hue = 0;
        double saturation = 0;
        double value = 0;
    };

    class LedLib
    {
    private:
        double hue_step = 0; // Member variable to store hue step
        int divisions = 0;
    public:
        int size;
        pros::ADILED strip;
        enum LEDMode mode = LEDManual;

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

        /**
         * @brief Sets the entire RGB strip to a specified Graident
         *
         * @param colora Color Represented as a 6 digit hex code (0xFF00FF)
         * @param colorb Color Represented as a 6 digit hex code (0xFF00FF)
         */
        void setGraident(uint32_t colora, uint32_t colorb);

        /**
         * @brief Sets the entire RGB strip to a specified Graident
         *
         * @param colora Color Represented as an HSV struct
         * @param colorb Color Represented as an HSV struct
         */
        void setGraident(HSV colora, HSV colorb);

        /**
         * @brief Sets the entire RGB strip to a specified Graident
         *
         * @param colora Color Represented as an RGB struct
         * @param colorb Color Represented as an RGB struct
         */
        void setGraident(RGB colora, RGB colorb);

        /// Static Functions

        /**
         * @brief
         *
         * @note Credits to https://gist.github.com/peacefixation/5eeb6e992a012ea2f42cd5419df65ea7
         */
        static uint32_t lerpRGB(RGB color1, RGB color2, double scale);

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

        /// Specialty Functions

        /**
         * @brief Set the LED strip to display a rainbow effect.
         */
        void setRainbow();

        /**
         * @brief Set the LED strip to display a color-changing rainbow effect.
         *
         * @param delay_ms Delay in milliseconds between color changes.
         */
        void fullRainbow(int delay_ms);

        /**
         * @brief Set up the LED strip to display an offset rainbow effect.
         *
         * @param divisions Number of divisions to split the strip by.
         */
        void offsetRainbow(int divisions = 2);

        /**
         * @brief Update the built-in PROS ADILED buffer based on the selected LED mode.
         */
        void cycle();
    };
}