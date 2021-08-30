/** ***************************************************************************
* @file
*
* @brief contains the operation functions
******************************************************************************/
#include <algorithm>
#include "netPBM.h"

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function checks the boundry for each pixel in the 2 dimensional arrays
 * to be between 0 and 255 and sets the values of the pixels after the
 * operations for the functions brighten, sharpen, and smooth.
 *
 * @param[in, out] colorRed - the red pixel color to be given a value
 * @param[in, out] colorGreen - the green pixel color to be given a value
 * @param[in, out] colorBlue - the blue pixel color to be given a value
 * @param[in] testValueRed - the value to be set to the red pixel location
 * @param[in] testValueGreen - the value to be set to the green pixel location
 * @param[in] testValueBlue - the value to be set to the blue pixel location
 * @param[in] i - row location in two dimensional array of pixels
 * @param[in] j - column location in two dimensional array of pixels
 *
 * @returns none
 *****************************************************************************/
void checkBoundry( pixel **&colorRed, pixel **&colorGreen, pixel **&colorBlue,
                   int testValueRed, int testValueGreen,
                   int testValueBlue, int i, int j )
{
    // reset the value of a pixel to limit if out of boundry
    if( testValueRed > 255 )
    {
        testValueRed = 255;
    }
    if( testValueRed < 0 )
    {
        testValueRed = 0;
    }

    if( testValueGreen > 255 )
    {
        testValueGreen = 255;
    }
    if( testValueGreen < 0 )
    {
        testValueGreen = 0;
    }

    if( testValueBlue > 255 )
    {
        testValueBlue = 255;
    }
    if( testValueBlue < 0 )
    {
        testValueBlue = 0;
    }

    // initialize array values
    colorRed[i][j] = testValueRed;
    colorGreen[i][j] = testValueGreen;
    colorBlue[i][j] = testValueBlue;
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function negates the image for the red, green, and blue pixels in each
 * array by subtracting the value of the pixel from the value 255. It moves
 * through the arrray by specificying a row then a column in a nested for-
 * loop.
 *
 * @param[in, out] specifications - the structure containing the content of the
 * image to be modified
 *
 * @returns none
 *****************************************************************************/
void _negate( image &specifications )
{
    // variables
    int i, j;

    // negate each pixel
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            specifications.red[i][j] = 255 - specifications.red[i][j];
            specifications.green[i][j] = 255 - specifications.green[i][j];
            specifications.blue[i][j] = 255 - specifications.blue[i][j];
        }
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function brightens the image for red, green, and blue in each pixel
 * based on amount specified by adding a specified value to the value in the
 * pixel. It moves through the arrray by specificying a row then a column in a
 * nested for-loop.
 *
 * @param[in, out] specifications - the structure containing the content of the
 * image to be modified
 * @param[in] argc - the number of arguments given in the command line
 * @param[in] argv - an array containing the arguments given in the command
 * prompt
 *
 * @returns none
 *****************************************************************************/
void brighten( image &specifications, int argc, char *argv[] )
{
    // variables
    int value = stoi( (string) argv[argc - 4] );
    int i, j, testValueRed, testValueGreen, testValueBlue;

    // brighten each pixel with limits of 255 and 0
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            // determine the pixel value based on the amount specified
            testValueRed = specifications.red[i][j] + value;
            testValueGreen = specifications.green[i][j] + value;
            testValueBlue = specifications.blue[i][j] + value;

            // reset the value to limit if out of boundry
            checkBoundry( specifications.red, specifications.green,
                          specifications.blue, testValueRed,
                          testValueGreen, testValueBlue, i, j );
        }
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function sharpens the image for red, green, and blue in each pixel
 * based on an algorithm provided which multiplies the value in the pixel by
 * 5 and subtracts the surrounding (up, down, left ,right) values of the
 * array from the pixel. It moves through the arrray by specificying a row then
 * a column in a nested for-loop. The values of all border pixels are set to
 * zero.
 *
 * @param[in, out] specifications - the structure containing the content of
 * the image to be modified
 *
 * @returns none
 *****************************************************************************/
void sharpen( image &specifications )
{
    // variables
    int i, j, testValueRed, testValueGreen, testValueBlue;

    // allocate new arrays to host temporary calculated values
    allocArray( specifications.newred, specifications.rows,
                specifications.cols );
    allocArray( specifications.newgreen, specifications.rows,
                specifications.cols );
    allocArray( specifications.newblue, specifications.rows,
                specifications.cols );

    // sharpen each pixel utilizing the provided algorithm
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            // ensure the pixel is not a border pixel
            if( i != 0 && j != 0 && i != ( specifications.rows - 1 ) &&
                j != ( specifications.cols - 1 ) )
            {
                // use test values to set temporary values in the new array
                testValueRed = 5 * specifications.red[i][j] -
                    specifications.red[i + 1][j] -
                    specifications.red[i - 1][j] -
                    specifications.red[i][j + 1] -
                    specifications.red[i][j - 1];
                testValueGreen = 5 * specifications.green[i][j] -
                    specifications.green[i + 1][j] -
                    specifications.green[i - 1][j] -
                    specifications.green[i][j + 1] -
                    specifications.green[i][j - 1];
                testValueBlue = 5 * specifications.blue[i][j] -
                    specifications.blue[i + 1][j] -
                    specifications.blue[i - 1][j] -
                    specifications.blue[i][j + 1] -
                    specifications.blue[i][j - 1];

                // boundry checking
                checkBoundry( specifications.newred, specifications.newgreen,
                              specifications.newblue, testValueRed,
                              testValueGreen, testValueBlue, i, j );
            }
            else
            {
                // set the border pixels to zero
                specifications.newred[i][j] = 0;
                specifications.newgreen[i][j] = 0;
                specifications.newblue[i][j] = 0;
            }
        }
    }

    // use algorithm swap to remove excess memory
    swap( specifications.red, specifications.newred );
    swap( specifications.green, specifications.newgreen );
    swap( specifications.blue, specifications.newblue );

    // free the excess memory from the temporary arrays utilized
    free2d( specifications.newred, specifications.rows );
    free2d( specifications.newgreen, specifications.rows );
    free2d( specifications.newblue, specifications.rows );
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function smooths the image for red, green, and blue in each pixel
 * based on an algorithm provided which sums the 8 directly surrounding values
 * in the array and the pixel itself, and then divides by nine to determine the
 * new pixels value. It moves through the arrray by specificying a row then
 * a column in a nested for-loop. The values of all border pixels are set to
 * zero.
 *
 * @param[in, out] specifications - the structure containing the content of the
 * image which contains the image content which is modified
 *
 * @returns none
 *****************************************************************************/
void smooth( image &specifications )
{
    // variables
    int i, j, testValueRed, testValueGreen, testValueBlue;

    // allocate new arrays to host temporary calculated values
    allocArray( specifications.newred, specifications.rows,
                specifications.cols );
    allocArray( specifications.newgreen, specifications.rows,
                specifications.cols );
    allocArray( specifications.newblue, specifications.rows,
                specifications.cols );

    // smooth each pixel utilizing the provided algorithm
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            // ensure the pixel is not a border pixel
            if( i != 0 && j != 0 && i != ( specifications.rows - 1 ) &&
                j != ( specifications.cols - 1 ) )
            {
                // use test values to set temporary values in the new array
                testValueRed = ( specifications.red[i + 1][j - 1] +
                                 specifications.red[i + 1][j] +
                                 specifications.red[i + 1][j + 1] +
                                 specifications.red[i][j - 1] +
                                 specifications.red[i][j] +
                                 specifications.red[i][j + 1] +
                                 specifications.red[i - 1][j - 1] +
                                 specifications.red[i - 1][j] +
                                 specifications.red[i - 1][j + 1] ) / 9;
                testValueGreen = ( specifications.green[i + 1][j - 1] +
                                   specifications.green[i + 1][j] +
                                   specifications.green[i + 1][j + 1] +
                                   specifications.green[i][j - 1] +
                                   specifications.green[i][j] +
                                   specifications.green[i][j + 1] +
                                   specifications.green[i - 1][j - 1] +
                                   specifications.green[i - 1][j] +
                                   specifications.green[i - 1][j + 1] ) / 9;
                testValueBlue = ( specifications.blue[i + 1][j - 1] +
                                  specifications.blue[i + 1][j] +
                                  specifications.blue[i + 1][j + 1] +
                                  specifications.blue[i][j - 1] +
                                  specifications.blue[i][j] +
                                  specifications.blue[i][j + 1] +
                                  specifications.blue[i - 1][j - 1] +
                                  specifications.blue[i - 1][j] +
                                  specifications.blue[i - 1][j + 1] ) / 9;

                // boundry checking
                checkBoundry( specifications.newred, specifications.newgreen,
                              specifications.newblue, testValueRed,
                              testValueGreen, testValueBlue, i, j );
            }
            else
            {
                // set the border pixels to zero
                specifications.newred[i][j] = 0;
                specifications.newgreen[i][j] = 0;
                specifications.newblue[i][j] = 0;
            }
        }
    }

    // use algorithm swap to remove excess memory
    swap( specifications.red, specifications.newred );
    swap( specifications.green, specifications.newgreen );
    swap( specifications.blue, specifications.newblue );

    // free the excess memory from the temporary arrays utilized
    free2d( specifications.newred, specifications.rows );
    free2d( specifications.newgreen, specifications.rows );
    free2d( specifications.newblue, specifications.rows );
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function converts the image from color to grayscale by calculating
 * a given value for each pixel, and appending the value to the gray-scaled
 * array. The gray scaled array is then output to the respective image type
 * P2 (Ascii) or P5 (Binary). This function walks through each value in each
 * row utilizing a nested for-loop.
 *
 * @param[in, out] specifications - the structure containing the content of
 * the image which is modified
 * @param[in, out] max - an intiger to hold the maximum value of a pixel
 * contained in the image
 * @param[in, out] min - an intiger to hold the minimum value of a pixel
 * contained in the image
 *
 * @returns none
 *****************************************************************************/
// converts the image to grayscale from the r, g, and b in each pixel
void grayscale( image &specifications, int &max, int &min )
{
    // variables
    int i, j;
    double testValue;

    // allocate a gray array for gray scaling
    allocArray( specifications.gray, specifications.rows,
                specifications.cols );

    // grayscale each pixel and append it to the two dimensional gray array
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            // algorithm for grayscaling
            testValue = specifications.red[i][j] * .3 +
                specifications.green[i][j] * .6 +
                specifications.blue[i][j] * .1;

            // boundry checking
            if( testValue > 255 )
            {
                specifications.gray[i][j] = 255;
            }
            else
            {
                specifications.gray[i][j] = (int) ( testValue + .5 );
            }

            // set max and min values for contrast function
            if( specifications.gray[i][j] > max )
            {
                max = specifications.gray[i][j];
            }
            if( specifications.gray[i][j] < min )
            {
                min = specifications.gray[i][j];
            }
        }
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This functions grayscales the image using the function listed for
 * grayscaling and then contrasts the image by scaling the grayscaled image
 * using a given value which is based on the minimum and maximum pixel values
 * found in each array in the grayscale fucntion. This function walks through
 * each value in each row utilizing a nested for-loop.
 *
 * @param[in, out] specifications - the structure containing the content of
 * the image which is modified
 *
 * @returns none
 *****************************************************************************/
void contrast( image &specifications )
{
    // variables
    int max = 0;
    int min = 255;
    int i, j;
    double scale, testValue;

    // grayscale the image before contrasting
    grayscale( specifications, max, min );

    // determine the scale value based on the maximum and minimum values
    // determined for each pixel in the grayscale operation
    scale = 255.0 / ( max - min );

    // contrast each pixel in the gray array based on the scale
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            // algorithm
            testValue = scale * ( specifications.gray[i][j] - min );

            // boundry checking
            if( testValue > 255.0 )
            {
                specifications.gray[i][j] = 255;
            }
            else
            {
                specifications.gray[i][j] = (int) testValue;
            }
        }
    }
}
