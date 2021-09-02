# Image Operations Program
Supports operations on PPM images: negate, brighten, sharpen, smooth, grayscale,
and contrast. The program was written with documentation in mind for ease of
modification and customization.

## Example
*Converted from PPM to PNG format for display*
Before | After
|-------------------------|-------------------------|
| Original | Negated |
| ![Image of city day and night](Images/day_and_night.png) | ![Image of city day and night negated](Images/day_and_night_negated.png) |
| Original | Brightened by 45 |
| ![Image of city day and night](Images/day_and_night.png) | ![Image of city day and night brightened](Images/day_and_night_brightened_45.png) |
| Original | Sharpened |
| ![Image of city day and night](Images/day_and_night.png) | ![Image of city day and night sharpened](Images/day_and_night_sharpened.png) |
| Original | Smoothed |
| ![Image of city day and night](Images/day_and_night.png) | ![Image of city day and night smoothed](Images/day_and_night_smoothed.png) |
| Original | Grayscaled |
| ![Image of city day and night](Images/day_and_night.png) | ![Image of city day and night grayscaled](Images/day_and_night_grayscaled.png) |
| Original | Contrasted |
| ![Image of city day and night](Images/day_and_night.png) | ![Image of city day and night contrasted](Images/day_and_night_contrasted.png) |

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
