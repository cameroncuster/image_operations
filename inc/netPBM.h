/** ***************************************************************************
* @file
*
* @brief contains protoypes a typedef and the image structure
******************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#ifndef __NETPBM__H__
/** ***************************************************************************
 * @brief variable to stop redefinition errors
 *****************************************************************************/
#define __ NETPBM__H__
using namespace std;

/** **************************************************************************!
 * \typedef unsigned char to pixel.
 *****************************************************************************/
typedef unsigned char pixel;

/** ***************************************************************************
 * @brief image structure holds all the data for the image both the header,
 * and the content of the image.
 *****************************************************************************/
struct image
{
    string encType; /*!< the string containing the encoder type of the image */
    string comments; /*!< the string containing the comments of the image in
                     the image header */
    int rows; /*!< the number of rows of content in the image */
    int cols; /*!< the number of columns of conntent in the image */
    string maxValue; /*!< the string containing the maximum value of a pixel */
    pixel **red; /*!< a 2d array contianing the red pixel values */
    pixel **green; /*!< a 2d array containing the green pixel values */
    pixel **blue; /*!< a 2d array containing the blue pixel values */
    pixel **gray; /*!< a 2d array containing the gray pixel values */
    pixel **newred; /*!< a 2d array for modified red pixel values */
    pixel **newgreen; /*!< a 2d array for modified green pixel values */
    pixel **newblue; /*!< a 2d array for modified blue pixel values */
};

/** ***************************************************************************
 * @brief the enumerated type referered to as operation holds the operations
 * that can be performed on the image with the funcitons in this program.
 *****************************************************************************/
enum operation
{
    Negate, /**< operation Negate */
    Brighten, /**< operation Brighten */
    Sharpen, /**< operation Sharpen */
    Smooth, /**< operation Smooth */
    Grayscale, /**< operation Grayscale */
    Contrast, /**< operation Contrast */
    None /**< operation None */
};


/******************************************************************************
 *                         Function Prototypes
 *****************************************************************************/

// check commandl line arguments and direct operations
void usageStatement( );
void checkCMD( image specifications, int argc, char *argv[], bool &grayCheck,
               string &outFileName );
operation operationType( image specifications, int argc, char *argv[] );
void read( ifstream &imageFile, image &specifications, int argc,
           char *argv[] );
void performOperation( image &specifications, operation operationValue,
                       int argc, char *argv[] );
void write( ofstream &writeFile, image &specifications, bool grayCheck,
            int argc, char *argv[] );


// fileio
void readImageHeader( ifstream &imageFile, image &specificaitons );
void readAscii( ifstream &imageFile, image &specifications );
void readBinary( ifstream &imageFile, image &specifications );
void writeAscii( ofstream &writeFile, image specifications, bool grayCheck );
void writeBinary( ofstream &writeFile, image specifications, bool grayCheck );


// check the boundry for operations
void checkBoundry( pixel **&colorRed, pixel **&colorGreen, pixel **&colorBlue,
                   int testValueRed, int testValueGreen,
                   int testValueBlue, int i, int j );

// operations
void _negate( image &specifications );
void brighten( image &specifications, int argc, char *argv[] );
void sharpen( image &specifications );
void smooth( image &specifications );
void grayscale( image &specifications, int &max, int &min );
void contrast( image &specifications );

// memory
void allocArray( pixel **&color, int rows, int cols );
void free2d( pixel **&color, int rows );

#endif
