# DEPRECATED gCode Generator for Vector Slicer
This package was superseded by https://github.com/Zmmyslony/VectorSlicerGCode, and is no longer maintained. 
### Description

This program is meant to be used together with Vector Slicer
(https://github.com/Zmmyslony/Vector_Slicer) in order to translate the generated
print paths from a pixel based sequence of coordinates that Vector Slicer generates,
into a gcode file compatible with a Hyrel3D printer (built for 30M model with a
KR2 print head and UV array).

The code allows for simple transformations of the generated pattern, such as
scaling it (for example to use with a different nozzle diameter) or moving
it on the print bed. Furthermore, it allows for generation of a simple
configuration patterns in order to tune the printing parameters.

### Compatibility

Due to using the Boost library for path handling it should be able to run on any
operating system, although it was only tested on Windows 10 and Ubuntu 20.04.5 LTS.

### Guarantee

Software is published without any guarantee or promise of maintenance. It is
developed for internal use, and is published without extensive documentation.

