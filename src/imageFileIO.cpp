/** ***************************************************************************
* @file
*
* @brief contains functions that read and write files both binary and ascii
******************************************************************************/

#include "netPBM.h"
using namespace std;

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function outputs an error message and exits the program if the
 * incorrect command line arguments are provided. The functions also specifies
 * the correct arguments for the programmer.
 *
 * @returns none
 *****************************************************************************/
void usageStatement( )
{
    cout << "Usage: image_operations [option] -o[ab] basename image.ppm" << endl;
    cout << "\t-n negate\t-oa ascii" << endl;
    cout << "\t-b brighten #\t-ob binary" << endl;
    cout << "\t-p sharpen" << endl;
    cout << "\t-s smooth" << endl;
    cout << "\t-g grayscale" << endl;
    cout << "\t-c contrast" << endl;
    // exit without fail
    exit( 0 );
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This functions validates the number of command line arguments provided and
 * appends the file type of the image to the output file name. The fucntion
 * will exit with a zero and output a usage statemet if it fails to validate.
 *
 * @param[in] specifications  - the structure containing the content of the
 * image
 * @param[in] argc - an intiger containing the number of command line
 * arguments provided
 * @param[in] argv - a character array containing the command line arguments
 * provided by the programmer
 * @param[in, out] grayCheck - a boolean specifying wether the image is going
 * to be grayscaled or not
 * @param[in, out] outFileName - the name of the output file to be appended to
 * have a file type of PPM (Color) or PGM (Grayscale)
 *
 * @returns none
 *****************************************************************************/
void checkCMD( image specifications, int argc, char *argv[], bool &grayCheck,
               string &outFileName )
{
    // check for proper amount of arguments
    if( argc < 4 || argc > 6 )
    {
        usageStatement( );
    }
    // see if an operations was give and add extenstsion
    else if( argc == 5 )
    {
        outFileName = (string) argv[argc - 2];
        if( (string) argv[argc - 4] == "-g" ||
            (string) argv[argc - 4] == "-c" )
        {
            outFileName += ".pgm";
            grayCheck = true;
        }
        else
        {
            outFileName += ".ppm";
            grayCheck = false;
        }
    }
    // no operations, just add extension
    else
    {
        outFileName = (string) argv[argc - 2];
        outFileName += ".ppm";
        grayCheck = false;
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function checks the operation type and returns the
 * enumerated operation type, based on the command line arguments provided.
 * The function will exit if an invalid argument is given or return none if
 * there is no operation specified.
 *
 * @param[in] specifications  - the structure containing the content of the
 * image
 * @param[in] argc - an intiger containing the number of command line
 * arguments provided
 * @param[in] argv - a character array containing the command line arguments
 * provided by the programmer
 *
 * @returns Negate - negate is the operation
 * @returns Brighten - brigthen is the operaiton
 * @returns Sharpen - sharpen is the operation
 * @returns Smooth - smooth is the operation
 * @returns Grayscale - grayscale is the operation
 * @returns Contrast - contrast is the operation
 * @returns None - there is no operation
 *****************************************************************************/
operation operationType( image specifications, int argc, char *argv[] )
{
    // check the operation specified by the command line
    if( (string) argv[argc - 4] == "-n" )
    {
        return Negate;
    }
    else if( argc == 6 )
    {
        if( (string) argv[argc - 5] == "-b" )
        {
            return Brighten;
        }
        else
        {
            usageStatement( );
        }
    }
    else if( (string) argv[argc - 4] == "-p" )
    {
        return Sharpen;
    }
    else if( (string) argv[argc - 4] == "-s" )
    {
        return Smooth;
    }
    else if( (string) argv[argc - 4] == "-g" )
    {
        return Grayscale;
    }
    else if( (string) argv[argc - 4] == "-c" )
    {
        return Contrast;
    }
    // if no operation is given return None and output the data as it was read
    if( argc != 4 )
    {
        usageStatement( );
    }
    return None;
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function dynamically allocates the 2 dimensional arrays for red,
 * green, and blue pixels. The function then calls another function to read
 * the data in Ascii or Binary based on the encoder type provided in the
 * image header.
 *
 * @param[in] imageFile - the input image file to provide the data
 * @param[in, out] specifications - the content of the image file in a
 * structure hosting the pixel (unsigned character) arrays to be read into
 * @param[in] argc - an intiger containing the number of command line
 * arguments provided
 * @param[in] argv - a character array containing the command line arguments
 * provided
 *
 * @returns None
 *****************************************************************************/
void read( ifstream &imageFile, image &specifications,
           int argc, char *argv[] )
{
    // allocate 2d arrays for each color
    allocArray( specifications.red, specifications.rows,
                specifications.cols );
    allocArray( specifications.green, specifications.rows,
                specifications.cols );
    allocArray( specifications.blue, specifications.rows,
                specifications.cols );

    // check the encoder type of the image and read the data respectively
    if( specifications.encType == "P3" )
    {
        readAscii( imageFile, specifications );
    }
    else if( specifications.encType == "P6" )
    {
        readBinary( imageFile, specifications );
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function will write the image data in ascii or binary based on the
 * command line. The encoder type is also specified in this function, and a
 * gray array is allocated and erased if necessary. This function will also
 * free the memory from the two dimensional arrays, and if incorrect command
 * line arguments are provided then a usage statement is output and the
 * program exits with a 0.
 *
 * @param[in] writeFile - the output image file to output the data too
 * @param[in, out] specifications - the content of the image file in a
 * structure containing the pixel (unsigned character) arrays which are
 * written too
 * @param[in] grayCheck - a boolean specifiying wether the output image will
 * be grayscaled or not
 * @param[in] argc - an intiger containing the number of command line
 * arguments provided
 * @param[in] argv - a character array containing the command line arguments
 * provided
 *
 * @returns None
 *****************************************************************************/
void write( ofstream &writeFile, image &specifications, bool grayCheck,
            int argc, char *argv[] )
{
    // check the read type specified in the command line
    if( (string) argv[argc - 3] == "-oa" )
    {
        // set the encoder type based on the operation and file type and
        // output the data
        if( grayCheck == true )
        {
            specifications.encType = "P2";
            writeAscii( writeFile, specifications, grayCheck );
            free2d( specifications.gray, specifications.rows );
        }
        else if( grayCheck == false )
        {
            specifications.encType = "P3";
            writeAscii( writeFile, specifications, grayCheck );
        }
    }
    else if( (string) argv[argc - 3] == "-ob" )
    {
        if( grayCheck == true )
        {
            specifications.encType = "P5";
            writeBinary( writeFile, specifications, grayCheck );
            free2d( specifications.gray, specifications.rows );
        }
        else if( grayCheck == false )
        {
            specifications.encType = "P6";
            writeBinary( writeFile, specifications, grayCheck );
        }
    }
    // if the incorrect arguments are provided output a usage statement
    else
    {
        usageStatement( );
    }

    // free the memory from the 2d arrays previously allocated dynamically
    free2d( specifications.red, specifications.rows );
    free2d( specifications.green, specifications.rows );
    free2d( specifications.blue, specifications.rows );
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function takes the operation value specified from the previous
 * function and perfroms the operation by calling to the operation funcitons.
 * If no operation is specified the function returns.
 *
 * @param[in, out] specifications - the content of the image file in a
 * structure which hosts the data to be modified in the pixel (unsigned
 * character) arrays
 * @param[in] operationValue- this value is of the enumerated type operation
 * and tells the function which operaiton to perform
 * @param[in] argc - an intiger containing the number of command line
 * arguments provided
 * @param[in] argv - a character array containing the command line arguments
 * provided
 *
 * @returns None
 *****************************************************************************/
void performOperation( image &specifications, operation operationValue,
                       int argc, char *argv[] )
{
    // store the minimum and maximum values of the array for gray
    int max = 0;
    int min = 255;
    // perform the operation based on the image data
    if( operationValue == Negate )
    {
        _negate( specifications );
    }
    else if( operationValue == Brighten )
    {
        brighten( specifications, argc, argv );
    }
    else if( operationValue == Sharpen )
    {
        sharpen( specifications );
    }
    else if( operationValue == Smooth )
    {
        smooth( specifications );
    }
    else if( operationValue == Grayscale )
    {
        grayscale( specifications, max, min );
    }
    else if( operationValue == Contrast )
    {
        contrast( specifications );
    }
    // if no operation is specified just return
    else if( operationValue == None )
    {
        return;
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function reads the header of the image to the image structure. The
 * function reads the encoder type, the comments, the columns and rows, and
 * the maximum value of a pixel contained in the image. This function uses the
 * encoder type of the image to identify the image file type.
 *
 * @param[in] imageFile - this is the input image file containing the
 * origional content of the image in Binary or Ascii
 * @param[in, out] specifications - the content of the image file in a
 * structure which is read into
 *
 * @returns None
 *****************************************************************************/
void readImageHeader( ifstream &imageFile, image &specifications )
{
    string fileType;
    string line;

    imageFile.clear( );
    imageFile.seekg( 0, ios::beg );

    imageFile >> specifications.encType;
    imageFile.ignore( );

    // read as many lines of comments as necessary
    while( imageFile.peek( ) == '#' )
    {
        getline( imageFile, line );
        if( specifications.comments.size( ) != 0 )
        {
            specifications.comments += '\n';
        }
        specifications.comments += line;
    }
    // output the image data to the image structure
    imageFile >> specifications.cols >>
        specifications.rows >>
        specifications.maxValue;
    imageFile.ignore( );
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function reads the data from an Ascii (P3) type image into the
 * specifications structure. The data from the image is stored in the 2
 * dimensional arrays perviously allocated for red, green, and blue.
 *
 * @param[in] imageFile - this is the input image file containing the
 * origional content of the image in Binary or Ascii
 * @param[in, out] specifications - the content of the image file in a
 * structure which contains the 2 dimensional arrays that are read into.
 *
 * @returns None
 *****************************************************************************/
void readAscii( ifstream &imageFile, image &specifications )
{
    int i, j;
    int color;
    // read the data for as many cols and rows exist in the image
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            imageFile >> color;
            specifications.red[i][j] = color;

            imageFile >> color;
            specifications.green[i][j] = color;

            imageFile >> color;
            specifications.blue[i][j] = color;
        }
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function reads the data from an Binary (P6) type image into the
 * specifications structure. The data from the image is stored in the 2
 * dimensional arrays perviously allocated for red, green, and blue.
 *
 * @param[in] imageFile - this is the input image file containing the
 * origional content of the image in Binary or Ascii
 * @param[in, out] specifications - the content of the image file in a
 * structure which contains the pixel (unsigned character) 2 dimensional
 * arrays which must be read into.
 *
 * @returns None
 *****************************************************************************/
void readBinary( ifstream &imageFile, image &specifications )
{
    int i, j;
    int color;
    // read the data for as many cols and rows exist in the image
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            imageFile.read( (char *) &color, 1 );
            specifications.red[i][j] = color;

            imageFile.read( (char *) &color, 1 );
            specifications.green[i][j] = color;

            imageFile.read( (char *) &color, 1 );
            specifications.blue[i][j] = color;
        }
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function writes the data to an Ascii (P3) type image. This includes
 * writing the image header and all of that data, as well as the image
 * content, after being modified as specified.
 *
 * @param[in] writeFile - the output file that the data from the image
 * contained in the image structure is written too
 * @param[in, out] specifications - the content of the image file in a
 * structure which contains the pixel (unsigned character) 2 dimensional
 * arrays which are written too
 * @param[in] grayCheck - a boolean value specifying wether the image
 * was grayscaled or not
 *
 * @returns None
 *****************************************************************************/
void writeAscii( ofstream &writeFile, image specifications, bool grayCheck )
{
    int i, j;
    // check for comments in the header and write the data
    if( specifications.comments.size( ) == 0 )
    {
        writeFile << specifications.encType << endl
            << specifications.cols << ' ' << specifications.rows << endl
            << specifications.maxValue << '\n';
    }
    else
    {
        writeFile << specifications.encType << endl
            << specifications.comments << endl
            << specifications.cols << ' ' << specifications.rows << endl
            << specifications.maxValue << '\n';
    }

    // write the data of the image for each row in each column
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            if( grayCheck == true )
            {
                writeFile << (int) specifications.gray[i][j] << ' ';
            }
            else if( grayCheck == false )
            {
                writeFile
                    << (int) specifications.red[i][j] << ' '
                    << (int) specifications.green[i][j] << ' '
                    << (int) specifications.blue[i][j] << ' ';
            }
        }
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function writes the data to an Binary (P6) type image. This includes
 * writing the image header and all of that data, as well as the image
 * content, after being modified as specified.
 *
 * @param[in] writeFile - the output file that the data from the image
 * contained in the image structure is written too
 * @param[in, out] specifications - the content of the image file in a
 * structure which contains the pixel (unsigned character) arrays which the
 * function writes too
 * @param[in] grayCheck - a boolean value specifying wether the image
 * was grayscaled or not
 *
 * @returns None
 *****************************************************************************/
void writeBinary( ofstream &writeFile, image specifications, bool grayCheck )
{
    int i, j;
    // check for comments in the image header and output the data
    if( specifications.comments.size( ) == 0 )
    {
        writeFile << specifications.encType << endl
            << specifications.cols << ' ' << specifications.rows << endl
            << specifications.maxValue << '\n';
    }
    else
    {
        writeFile << specifications.encType << endl
            << specifications.comments << endl
            << specifications.cols << ' ' << specifications.rows << endl
            << specifications.maxValue << '\n';
    }

    // write the data for image to the output file
    for( i = 0; i < specifications.rows; i++ )
    {
        for( j = 0; j < specifications.cols; j++ )
        {
            if( grayCheck == true )
            {
                writeFile.write( (char *) &specifications.gray[i][j], 1 );
            }
            else if( grayCheck == false )
            {
                writeFile.write( (char *) &specifications.red[i][j], 1 );
                writeFile.write( (char *) &specifications.green[i][j], 1 );
                writeFile.write( (char *) &specifications.blue[i][j], 1 );
            }
        }
    }
}
