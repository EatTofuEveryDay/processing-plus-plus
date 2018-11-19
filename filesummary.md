`basewin.h`:
- Defines SafeRelease

`win32decl.h`:
- Declares the Direct2D window class

`win32private.h`:
- Declares static variables in the prxx::__private namespace
- Define the macro EXT as /* */ to make non-extern

`win32ev.cpp`:
- Implements the processing events
- Defines WndProc and other windows-required functions

`win32impl2d.cpp`:
- Implements the 2D primitives functions