#pragma once

#include "LedEffect.hpp"
#include "../LedLib.hpp"
namespace LedLib
{
    class GraidentEffect : public LedEffect
    {
    public:
        HSV startColor;
        HSV endColor;
        GraidentEffect(RGB start, RGB end);
        GraidentEffect(HSV start, HSV end);
        void setup(LedLib &ledLib) override;
        void update(LedLib &ledLib) override;
    };
};