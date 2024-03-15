# A PROS LED Library for Vex V5

### A Few Notes:
1) This is still early development, and as such only has basic features.
2) This probably isn't thread-safe. I haven't implemented any locks, so its possible that the main function and another thread could access the strip at the same time, which is a no-no. This will be fixed later in development.
3) As this is still early development, the way certain things are setup are bound to change as I find better ways of implementing it.

I highly recommend __*NOT*__ using this in any competition unless you have heavily tested it both with and without the brain hooked up to a field controller.