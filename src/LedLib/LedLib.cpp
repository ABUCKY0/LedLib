#include "LedLib/LedLib.hpp"

using namespace LedLib;
using namespace std;

namespace LedLib
{
    /**
     * @brief Construct a new Led object
     *
     * @param adiport 1-8 representing Triports A-H
     * @param length 1-64 representing the length of the LEDs
     *
     * @throws StripSizeTooLarge if size is > 64
     */
    LedLib::LedLib(uint8_t adiport, int length)
        : size(length), strip(adiport, length)
    {
        // Constructor body (if any)
    }

    /**
     * @brief Construct a new Led object
     *
     * @param smartport 1-21 representing SmartPorts 1-21
     * @param adiport 1-8 representing Triports A-H
     * @param length 1-64 representing the length of the LEDs
     *
     * @throws StripSizeTooLarge if size is > 64
     */
    LedLib::LedLib(uint8_t smartport, uint8_t adiport, int length) : strip({smartport, adiport}, length)
    {
        this->strip = pros::ADILed({smartport, adiport}, length);
        this->size = length;
    }

    /**
     * @brief Set all leds to a given RGB color
     *
     * @param rgb an RGB value represented as a struct
     */
    void LedLib::setAll(RGB rgb)
    {
        this->strip.set_all(RGBtoUINT32(rgb));
    }

    /**
     * @brief Set all leds to a given RGB color
     *
     * @param hsv an HSV value represented as a struct
     *
     * @note Converts HSV to RGB, then calls setAll(RGB) for simplicity
     */
    void LedLib::setAll(HSV hsv)
    {
        this->strip.set_all(HSVtoUINT32(hsv));
    }

    /**
     * @brief Set all LEDs to a specified color loopy style
     *
     * If your LED strip is being b*tchy about setting all the colors at once (like mine do), call this function instead.
     *
     * @param rgb
     */
    void LedLib::setAllButchy(RGB rgb)
    {
        uint32_t color = RGBtoUINT32(rgb);
        for (int index = 0; index < this->size; index++)
        {
            this->strip.set_pixel(color, index);
            pros::delay(5);
        }
    }

    /**
     * @brief Set all LEDs to a specified color loopy style
     *
     * If your LED strip is being b*tchy about setting all the colors at once (like mine do), call this function instead.
     *
     * @param hsv a HSV struct
     */
    void LedLib::setAllButchy(HSV hsv)
    {
        uint32_t color = HSVtoUINT32(hsv);
        for (int index = 0; index < this->size; index++)
        {
            this->strip.set_pixel(color, index);
            pros::delay(5);
        }
    }

    /**
     * @brief Set a given pixel to a specified color
     *
     * @param rgb the RGB color to set the strip to
     * @param index the index of the LED
     */
    void LedLib::setPixel(RGB rgb, uint8_t index)
    {
        this->strip.set_pixel(RGBtoUINT32(rgb), index);
    }

    /**
     * @brief Set a given pixel to a specified color
     *
     * @param hsv rgb the RGB color to set the strip to
     * @param index the index of the LED
     *
     * @note Converts HSV to RGB, then calls setPixel(RGB) for simplicity
     */
    void LedLib::setPixel(HSV hsv, uint8_t index)
    {
        this->strip.set_pixel(HSVtoUINT32(hsv), index);
    }

    /**
     * @brief Sets the entire RGB strip to a specified Graident
     *
     * @param colora Color Represented as a 6 digit hex code (0xFF00FF)
     * @param colorb Color Represented as a 6 digit hex code (0xFF00FF)
     *
     * @note Converts RGB to uint32_t then calls setGraident(uint32_t, uint32_t) for simplicity
     */
    void LedLib::setGraident(uint32_t colora, uint32_t colorb)
    {
    }

    /**
     * @brief Sets the entire RGB strip to a specified Graident
     *
     * @param colora Color Represented as an HSV struct
     * @param colorb Color Represented as an HSV struct
     *
     * @note Converts RGB to uint32_t then calls setGraident(uint32_t, uint32_t) for simplicity
     */
    void LedLib::setGraident(HSV colora, HSV colorb)
    {
    }

    /**
     * @brief Sets the entire RGB strip to a specified Graident
     *
     * @param colora Color Represented as an RGB struct
     * @param colorb Color Represented as an RGB struct
     *
     * @note Converts RGB to uint32_t then calls setGraident(uint32_t, uint32_t) for simplicity
     */
    void LedLib::setGraident(RGB colora, RGB colorb)
    {
    }

    /// Static Functions

    /**
     * @brief
     *
     * @note Credits to https://gist.github.com/peacefixation/5eeb6e992a012ea2f42cd5419df65ea7
     */
    uint32_t LedLib::lerpRGB(RGB color1, RGB color2, double scale)
    {
        if (scale > 1)
        {
            scale = 1;
        }
        else if (scale < 0)
        {
            scale = 0;
        }
        RGB lerped;

        lerped.red = color1.red + static_cast<uint8_t>((color2.red - color1.red) * scale);
        lerped.green = color1.green + static_cast<uint8_t>((color2.green - color1.green) * scale);
        lerped.blue = color1.blue + static_cast<uint8_t>((color2.blue - color1.blue) * scale);

        return RGBtoUINT32(lerped);
    }

    /**
     * @brief Converts RGB to HSV
     *
     * @param rgb The RGB struct to convert from
     *
     * @note Credits: https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
     * @return hsv A HSV struct
     */
    HSV LedLib::RGBtoHSV(RGB rgb)
    {
        HSV hsv;

        double r = rgb.red / 255.0;
        double g = rgb.green / 255.0;
        double b = rgb.blue / 255.0;

        double cmax = std::max(r, std::max(g, b));
        double cmin = std::min(r, std::min(g, b));
        double diff = cmax - cmin;
        double h = -1;
        double s = -1;

        if (cmax == cmin)
            h = 0;
        else if (cmax == r)
            h = fmod(60 * ((g - b) / diff) + 360, 360);
        else if (cmax == g)
            h = fmod(60 * ((b - r) / diff) + 120, 360);
        else if (cmax == b)
            h = fmod(60 * ((r - g) / diff) + 240, 360);

        if (cmax == 0)
            s = 0;
        else
            s = (diff / cmax) * 255.0;

        double v = cmax * 255.0;

        hsv.hue = static_cast<uint16_t>(h);
        hsv.saturation = static_cast<uint8_t>(s);
        hsv.value = static_cast<uint8_t>(v);

        return hsv;
    }

    /**
     * @brief Converts HSV to RGB
     * @note Credits: https://stackoverflow.com/questions/51203917/math-behind-hsv-to-rgb-conversion-of-colors
     *
     * @param hsv The HSV struct to convert from
     * @return A HSV struct
     */
    RGB LedLib::HSVtoRGB(HSV hsv)
    {
        RGB rgb;

        if (hsv.saturation == 0)
        { // Black
            rgb.red = 0;
            rgb.green = 0;
            rgb.blue = 0;
            return rgb;
        }

        double c = hsv.value * hsv.saturation;
        double x = c * (1 - fabs(fmod(hsv.hue / 60.0, 2) - 1));
        double m = hsv.value - c;

        double r, g, b;

        if (hsv.hue >= 0 && hsv.hue < 60)
        {
            r = c;
            g = x;
            b = 0;
        }
        else if (hsv.hue >= 60 && hsv.hue < 120)
        {
            r = x;
            g = c;
            b = 0;
        }
        else if (hsv.hue >= 120 && hsv.hue < 180)
        {
            r = 0;
            g = c;
            b = x;
        }
        else if (hsv.hue >= 180 && hsv.hue < 240)
        {
            r = 0;
            g = x;
            b = c;
        }
        else if (hsv.hue >= 240 && hsv.hue < 300)
        {
            r = x;
            g = 0;
            b = c;
        }
        else
        {
            r = c;
            g = 0;
            b = x;
        }

        rgb.red = (r + m) * 255;
        rgb.green = (g + m) * 255;
        rgb.blue = (b + m) * 255;

        return rgb;
    }

    /**
     * @brief uint32_t Color to RGB
     *
     * @param color the Color to Convert
     */
    RGB LedLib::UINT32toRGB(uint32_t color)
    {
        RGB rgb;
        rgb.red = (color >> 16) & 0xFF;
        rgb.green = (color >> 8) & 0xFF;
        rgb.blue = color & 0xFF;

        return rgb;
    }

    /**
     * @brief uint32_t Color to RGB
     *
     * @param color the Color to Convert
     */
    HSV LedLib::UINT32toHSV(uint32_t color)
    {
        return RGBtoHSV(UINT32toRGB(color));
    }

    /**
     * @brief Converts RGB to HSV
     *
     * @param rgb The RGB struct to convert from
     * @return A uint32_t color
     */
    uint32_t LedLib::RGBtoUINT32(RGB rgb)
    {
        return ((uint32_t)rgb.red << 16) | ((uint32_t)rgb.green << 8) | rgb.blue;
    }

    /**
     * @brief Converts HSV to UINT32
     *
     * @param hsv The HSV struct to convert from
     * @return A uint32_t color
     */
    uint32_t LedLib::HSVtoUINT32(HSV hsv)
    {
        return RGBtoUINT32(HSVtoRGB(hsv));
    }

    /// Specialty Functions:

    /**
     * @brief Set the LED strip to display a rainbow effect.
     */
    void LedLib::setRainbow()
    {
        int num_leds = this->size;
        double hue_step = 360.0 / num_leds;

        for (int i = 0; i < num_leds; ++i)
        {
            // Calculate the hue for this LED
            double hue = i * hue_step;
            // Convert hue to RGB color
            RGB rgb = HSVtoRGB({hue, 1.0, 1.0});
            // Set the pixel color
            setPixel(rgb, i);
        }
    };

    /**
     * @brief Set the LED strip to display a color-changing rainbow effect.
     *
     * @param delay_ms Delay in milliseconds between color changes.
     */

    // void LedLib::fullRainbow(int delay_ms)
    // {
    //     pros::Task rainbow_task([this, delay_ms]()
    //                             {
    //             int num_leds = size;
    //             double hue_step = 360.0 / num_leds;

    //             while (true) {
    //                 for (int i = 0; i < num_leds; ++i) {
    //                     // Calculate the hue for this LED
    //                     double hue = i * hue_step;
    //                     // Convert hue to RGB color
    //                     RGB rgb = HSVtoRGB({hue, 1.0, 1.0});
    //                     // Set the pixel color
    //                     setAll(rgb);
    //                     // Delay before updating to the next color
    //                     pros::delay(delay_ms);
    //                 }
    //             } });
    // }

    /**
     * @brief Set up the LED strip to display an offset rainbow effect.
     *
     * @param divisions Number of divisions to split the strip by.
     */
    void LedLib::offsetRainbow(int divisions)
    {
        this->divisions = divisions;
        // Calculate hue step based on the number of LEDs and divisions
        hue_step = 360.0 / (size * divisions);

        for (int i = 0; i < size; ++i)
        {
            // Calculate the hue for each LED based on the offset and divisions
            double hue_offset = (i / (double)(size)) * 360.0 / divisions;
            RGB rgb = HSVtoRGB({fmod(hue_offset, 360.0), 1.0, 1.0});
            setPixel(rgb, i);
        }

        mode = LEDOffsetRainbow;
    }

    void LedLib::cycle()
    {
        switch (mode)
        {
        case LEDOffsetRainbow:
            // Hardcoded value for initial offset hue
            static double offsetHue = 0.0; // Static to retain value between calls

            // Calculate the hue range covered by the rainbow based on the number of divisions
            double hue_range = 360.0 / divisions;

            // Increment hue for each pixel using the static hue_step
            for (int i = 0; i < size; ++i)
            {
                // Calculate the hue for this LED within the range covered by the rainbow
                double hue = fmod((offsetHue + i * hue_step), hue_range) + (divisions * i * hue_step);
                RGB rgb = HSVtoRGB({hue, 1.0, 1.0});
                setPixel(rgb, i);
            }
            strip.update();   // Update the LED strip
            offsetHue += 2.0; // Increment offset hue, adjust as needed
            break;
            // Add cases for other LED modes if needed
        }
    }
};
