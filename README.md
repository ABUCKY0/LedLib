# A PROS LED Library for Vex V5

### A Few Notes:
1) This is still early development, and as such only has basic features.
2) This probably isn't thread-safe. I haven't implemented any locks, so its possible that the main function and another thread could access the strip at the same time, which is a no-no. This will be fixed later in development.
3) As this is still early development, the way certain things are setup are bound to change as I find better ways of implementing it.

I highly recommend __*NOT*__ using this in any competition unless you have heavily tested it both with and without the brain hooked up to a field controller.


## Custom Effects

> This guide was designed around me making Builtin effects, but most of this should still apply for custom effects.

Make a EffectName.hpp file, and put in the following:

```cpp
//EffectName.hpp
#pragma once

#include "LedEffect.hpp" //May need Changing
#include "../LedLib.hpp" //May need Changing
namespace LedLib
{
    class CustomEffect : public LedEffect
    {
    public:
        void setup(LedLib &ledLib) override;
        void update(LedLib &ledLib) override;
    };
};
```

And then implement it in a cpp file:

