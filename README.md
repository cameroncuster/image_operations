# Image Operations Program
Supports operations on PPM images: negate, brighten, sharpen, smooth, grayscale,
and contrast. The program was written with documentation in mind for ease of
modification and customization.

## Example
*Converted from PPM to PNG format for display*
Before | After
:-------------------------:|:-------------------------:
![Image of city day and night](Images/day_and_night_after.png) | ![Image of city day and night negated](Images/day_and_night_after.png)

## Usage
```
C:\> image_operations [option] -o[ab] basename image.ppm
   -n - negate
   -b - brighten
   -p - sharpen
   -s - smooth
   -g - grayscale
   -c - contrast
```
