#pragma once

#include "LedEffect.hpp"
#include "../LedLib.hpp"
namespace LedLib
{
    class TurnSignal : public LedEffect
    {
    public:
        void setup(LedLib &ledLib) override;
        void update(LedLib &ledLib) override;
    };
};