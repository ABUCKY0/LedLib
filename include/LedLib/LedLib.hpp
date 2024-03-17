#pragma once
#include <vector>
#include "effects/LedEffect.hpp"
namespace LedLib {
    class LedLib {
        public:
            LedLib();
            int addEffect(LedEffect* customEffect);
            void updateEffects();
        protected:
            std::vector<LedEffect*> effects;
            int activeEffect;
    };
};