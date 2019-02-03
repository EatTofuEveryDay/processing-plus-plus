# How do I compile this?

Simple.

1. Build the library.

All platforms:
  `portsrc/*`

Windows:
  `win32src/*`

Mac:
  `osxsrc/*`

Produce a .lib or .dll file from these sources.

2. Make your program.

Make sure you include processing.h. This API differs from the other processing
APIs because of its low level. Differences:
- You can only draw in draw().
- Both setup() and draw() must be defined.
- createCanvas() must be called in setup()

Also, different from a classical C program, the library defines an entry point
already. Do not define `main` or `WinMain` or similar. Use setup() as an entry
point.

3. Link the library.

Link the library, the .lib file output in the first step.

GCC:

Compile with

    gcc path/to/my.cpp -o path/to/output.exe -lpath/to/processing.lib

For easy access, put processing.lib into your compiler's `lib` directory. Then
you can type

    gcc path/to/my.cpp -o path/to/output.exe -lprocessing

Microsoft Visual Studio:

Set processing.lib as a dependancy.

XCode/Clang/Other: WIP
