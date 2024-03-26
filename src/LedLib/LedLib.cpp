#include "LedLib.hpp"
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
        this->activeEffect = -1;
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
        // this->strip = pros::ADILed({smartport, adiport}, length);
        this->size = length;
        this->activeEffect = -1;
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

    void LedLib::setActiveEffect(int active)
    {
        this->activeEffect = active;
    }

    int LedLib::addEffect(LedEffect *customEffect)
    {
        this->effects.push_back(customEffect);
        return effects.size() - 1;
    }

    void LedLib::updateEffects()
    {
        if (this->activeEffect < 0)
            return;
        if (effects.size() <= 0)
            return;
        LedEffect *effect = this->effects[this->activeEffect];
        effect->update(*this);
        return;
    }

    /// Static Functions

    /**
     * @brief Lerps in RGB
     *
     * @note Credits to https://gist.github.com/peacefixation/5eeb6e992a012ea2f42cd5419df65ea7
     */
    RGB LedLib::lerpRGB(RGB color1, RGB color2, double scale)
    {
        RGB lerpedColor;
        lerpedColor.red = static_cast<uint8_t>(color1.red * (1.0 - scale) + color2.red * scale);
        lerpedColor.green = static_cast<uint8_t>(color1.green * (1.0 - scale) + color2.green * scale);
        lerpedColor.blue = static_cast<uint8_t>(color1.blue * (1.0 - scale) + color2.blue * scale);
        return lerpedColor;
    }
    HSV LedLib::lerpHSV(HSV color1, HSV color2, double scale)
    {
        HSV interpolatedColor;
        interpolatedColor.hue = color1.hue + (color2.hue - color1.hue) * scale;
        interpolatedColor.saturation = color1.saturation + (color2.saturation - color1.saturation) * scale;
        interpolatedColor.value = color1.value + (color2.value - color1.value) * scale;
        return interpolatedColor;
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

        // h, s, v = hue, saturation, value
        double cmax = std::max(r, std::max(g, b)); // maximum of r, g, b
        double cmin = std::min(r, std::min(g, b)); // minimum of r, g, b
        double diff = cmax - cmin;                 // diff of cmax and cmin.
        double h = -1, s = -1;

        // if cmax and cmax are equal then h = 0
        if (cmax == cmin)
            h = 0;

        // if cmax equal r then compute h
        else if (cmax == r)
            h = fmod(60 * ((g - b) / diff) + 360, 360);

        // if cmax equal g then compute h
        else if (cmax == g)
            h = fmod(60 * ((b - r) / diff) + 120, 360);

        // if cmax equal b then compute h
        else if (cmax == b)
            h = fmod(60 * ((r - g) / diff) + 240, 360);

        // if cmax equal zero
        if (cmax == 0)
            s = 0;
        else
            s = (diff / cmax) * 100;

        // compute v
        double v = cmax * 100;

        hsv.hue = h;
        hsv.saturation = s;
        hsv.value = v;

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
        double h = hsv.hue;                // 0-360
        double s = hsv.saturation / 100.0; // 0-100 mapping to 0-1
        double v = hsv.value / 100.0;      // 0-100 mapping to 0-1

        // Normalize hue to [0, 360]
        h = std::fmod(h, 360.0);
        if (h < 0)
            h += 360.0;

        int hi = static_cast<int>(std::floor(h / 60.0)) % 6;
        double f = (h / 60.0) - static_cast<int>(h / 60.0);
        double p = v * (1.0 - s);
        double q = v * (1.0 - f * s);
        double t = v * (1.0 - (1.0 - f) * s);

        double r, g, b;

        switch (hi)
        {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        case 5:
            r = v;
            g = p;
            b = q;
            break;
        default:
            r = g = b = 0.0;
            break;
        }

        // Scale to [0, 255] and convert to int
        RGB result;
        result.red = static_cast<int>(r * 255);
        result.green = static_cast<int>(g * 255);
        result.blue = static_cast<int>(b * 255);
        return result;
    }

    /**
     * @brief uint32_t Color to RGB
     *
     * @param color the Color to Convert
     */
    RGB LedLib::UINT32toRGB(uint32_t color)
    {   
        /*
         * Bits are stored 0xRRGGBB
         * Aka, 0xFF = 1111 1111
         * So, The full binary is RRRR RRRR GGGG GGGG BBBB BBBB
         * 
         * To get the Red, we need to remove the GGGG GGGG BBBB BBBB
         * Then resulting from that operation, you get 0000 0000 0000 0000 RRRR RRRR
         * use Binary AND to ignore the 0 bits and get the RRRR RRRR
         *
         * Repeat above but shift Green 8 bits to the right, then AND with 0xFF to ignore RRRR RRRR
         * 0000 0000 RRRR RRRR GGGG GGGG
         *
         * Repeat above but since no shifting is required, just AND with 0xFF to Ignore RRRR RRRR GGGG GGGG
         *
         * 0xFF
         */
        RGB rgb;
        // To get the Red, we need to remove the GGGG GGGG BBBB BBBB
        // Then resulting from that operation, you get 0000 0000 0000 0000 RRRR RRRR
        // use Binary AND to ignore the 0 bits and get the RRRR RRRR (Technically, we don't need to do the AND operation, but it's good practice to do so.)
        rgb.red = (color >> 16) & 0xFF; 


        // To get the Green, we need to remove the BBBB BBBB with BIT shifting
        // RRRR RRRR GGGG GGGG BBBB BBBB >> 8 = 0000 0000 RRRR RRRR GGGG GGGG
        // Binary AND with 0xFF to ignore the RRRR RRRR bits and get only the GGGG GGGG (Here we do, because otherwise we'd get RRRR RRRR and GGGG GGGG, which is a no-no)
        rgb.green = (color >> 8) & 0xFF;
        
        // Since Blue is at the rightmost side, we can just ignore RED and GREEN. 
        // Binary AND with 0xFF to ignore the RRRR RRRR and GGGG GGGG bits and get only the BBBB BBBB
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
        if (rgb.red > 255)
        {
            rgb.red = 255;
            std::cout << "[DEBUG FA/CLRCHK] R>255";
        }
        if (rgb.green > 255)
        {
            rgb.green = 255;
            std::cout << "[DEBUG FA/CLRCHK] G>255";
        }
        if (rgb.blue > 255)
        {
            rgb.blue = 255;
            std::cout << "[DEBUG FA/CLRCHK] B>255";
        }
        // Shifts Red 16 bits to the right, Green 8 bits to the right, and Blue 0 bits to the right
        // Then adds them together
        return ((uint8_t)rgb.red << 16) | ((uint8_t)rgb.green << 8) | (uint8_t)rgb.blue;
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

}