/** ***************************************************************************
* @file
*
* @brief contains the main function
******************************************************************************/

/** ***************************************************************************
 * @mainpage Image Manipulation
 *
 * @authors Cameron Custer
 *
 * @date 16 Oct. 2020
 *
 * @section program_section Program Information
 * The program reads ppm image data in either ascii or binary format, and
 * operates on the image to alter it to the users specificaitons if required.
 * The program then proceeds to write the data from the image to a specified file
 * from the command line.
 *
 * The operations which can be utilized on the image include: negate,
 * brighten, sharpen, smooth, grayscale, and contrast. The operations are
 * performed by reading ascii or binary values for the red, green, and blue
 * colors in the file into two dimensional arrays. One array for the red
 * values, one for the green values, and one for the blue values.
 *
 * The image is then output to an output file after the operation, if required
 * is performed. The data can then be read as an image or viewed as raw text.
 *
 * Note: While the data read can only be in P3 or P6 image format
 * the output data can host the form of P2, P3, P5, or P6.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage
   @verbatim
   C:\> image_operations [option] -o[ab] basename image.ppm
   -n - negate
   -b - brighten
   -p - sharpen
   -s - smooth
   -g - grayscale
   -c - contrast
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @todo none
 *
 *****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "netPBM.h"
using namespace std;

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This is the main function in the program. The programmer specifies how the
 * program is run based on the command line arguments provided to the main
 * function. The input image and output image paths are varified and file are
 * opened in the main function. If unable to open either file, an error
 * message is output and program exits. The data is read as specified by a
 * function refrenced in main based on the command line arguments which are
 * verified. The data is then modified if necessary and output to the output
 * file. The files are closed and the and the program ends.
 *
 * @param[in] argc - an intiger containing the number of command line
 * arguments provided
 * @param[in] argv - a character array containing the command line arguments
 * provided
 *
 * @returns 0 exits with code 0 after the program has run, and exit value of a
 * 1 indicates a program failure.
 *****************************************************************************/
int main( int argc, char *argv[] )
{
    // variables
    image specifications;
    operation operationValue;
    ifstream imageFile;
    ofstream writeFile;
    bool grayCheck;
    string outFileName;

    //check command line arguments
    checkCMD( specifications, argc, argv, grayCheck, outFileName );

    imageFile.open( argv[argc - 1], ios::in | ios::binary );

    // make sure the file is open
    if( !imageFile.is_open( ) )
    {
        cout << "Unable to open: " << argv[argc - 1] << endl;
        exit( 0 );
    }

    writeFile.open( outFileName, ios::out | ios::trunc | ios::binary );

    // make sure the file is open
    if( !writeFile.is_open( ) )
    {
        cout << "Unable to open: " << argv[argc - 2] << endl;
        exit( 0 );
    }

    // read in the header and determine the filetype of the imagefile
    readImageHeader( imageFile, specifications );

    // evaluate the operation type
    operationValue = operationType( specifications, argc, argv );

    // read the data
    read( imageFile, specifications, argc, argv );

    // operate on the data
    performOperation( specifications, operationValue, argc, argv );

    // write the data
    write( writeFile, specifications, grayCheck, argc, argv );

    // close the files and exit the program
    imageFile.close( );
    writeFile.close( );
    return 0;
}
