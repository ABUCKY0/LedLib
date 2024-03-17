// Include Effect
#include "LedLib/effects/GraidentEffect.hpp"
#include "LedLib/LedLib.hpp"
#include "main.h"
namespace LedLib
{
    GraidentEffect::GraidentEffect(RGB start, RGB end)
    {
        std::cout << "hi";
        this->startColor = LedLib::RGBtoHSV(start);
        this->endColor = LedLib::RGBtoHSV(end);
    };

    GraidentEffect::GraidentEffect(HSV start, HSV end)
    {
        this->startColor = start;
        this->endColor = end;
    };

    void GraidentEffect::setup(LedLib &ledLib)
    {
        return;
    };
    void GraidentEffect::update(LedLib &ledLib)
    {
        if (ledLib.size < 1)
        {
            // Ensure the LED strip size is valid
            std::cout << "LED strip size is less than 1." << std::endl;
            return;
        }

        // std::cout << "Updating gradient effect..." << std::endl;

        for (int i = 0; i < ledLib.size; ++i)
        {
            // Calculate the scale for interpolation
            double scale = static_cast<double>(i) / (ledLib.size - 1);

            // std::cout << "Interpolation scale: " << scale << std::endl;

            // Interpolate between start and end colors
            //HSV lerped = LedLib::lerpHSV(startColor, endColor, scale);
            //std::cout << "LERPED: H" << lerped.hue << " S" << lerped.saturation << " V" << lerped.value << "\n";
            // RGB interpolatedColor = LedLib::HSVtoRGB(lerped);
            RGB interpolatedColor = LedLib::lerpRGB(LedLib::HSVtoRGB(startColor), LedLib::HSVtoRGB(endColor), scale);
            std::cout << "CONVERT: R" << interpolatedColor.red << " G" << interpolatedColor.green << " B" << interpolatedColor.blue << "\n";

            // std::cout << "Interpolated color (RGB): R=" << interpolatedColor.red << ", G=" << interpolatedColor.green << ", B=" << interpolatedColor.blue << std::endl;

            // Set the pixel color on the LED strip
            ledLib.setPixel(interpolatedColor, i);
            pros::delay(5);
        }
    }

};