#pragma once
namespace LedLib {

    class LedLib;

    class LedEffect {
        public:
            virtual void setup( LedLib& ledLib) = 0;
            virtual void update( LedLib& ledLib) = 0;
    };
};

