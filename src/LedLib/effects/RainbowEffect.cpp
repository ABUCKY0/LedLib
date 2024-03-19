#include "RainbowEffect.hpp"
#include "LedLib/LedLib.hpp"
#include <cmath>
#include "main.h"
namespace LedLib {
    void RainbowEffect::setup(LedLib &ledLib) {
        int divisions = 2;
        // Calculate hue step based on the number of LEDs and divisions
        static double hue_step = 2.0;

        for (int i = 0; i < ledLib.size; ++i)
        {
            // Calculate the hue for each LED based on the offset and divisions
            double hue_offset = (i / (double)(ledLib.size)) * 360.0 / divisions;
            RGB rgb = LedLib::HSVtoRGB({fmod(hue_offset, 360.0), 1.0, 1.0});
            ledLib.setPixel(rgb, i);
        }
    };

    void RainbowEffect::update(LedLib &ledLib) {
        // Hardcoded value for initial offset hue
            static double offsetHue = 9999999999999;
            // Calculate the hue range covered by the rainbow based on the number of divisions
            double hue_range = 360.0 / 2;

            // Increment hue for each pixel using the static hue_step
            for (int i = ledLib.size; i >= 0; --i)
            {
                // Calculate the hue for this LED within the range covered by the rainbow
                double hue = fmod((offsetHue + i * 2.0), 360.0);
                RGB rgb = LedLib::HSVtoRGB({hue, 100, 100});
                ledLib.setPixel(rgb, i);
            }
            ledLib.strip.update();   // Update the LED strip
            offsetHue -= 2.0; // Increment offset hue, adjust as needed
    };
}