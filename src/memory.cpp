/** ***************************************************************************
* @file
*
* @brief contains functions which allocate dynamic memory and clear the memory
******************************************************************************/

#include "netPBM.h"
using namespace std;

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function dynamically allocates a 2 dimensional array for a set of
 * pixel (unsigned character) values to occupy, based on a given number of
 * rows of columns. The function checks for enough memory to allocate the
 * array, and if the memory
 * is not avaliable outputs an error message and exits if not enough memory is
 * avaliable.
 *
 * @param[in, out] color - the pixel (unsigned char) set to dynamically
 * allocate a 2 dimensional array for
 * @param[in] rows - an intiger representing the number of rows in the array
 * @param[in] cols - an intiger representing the number of columns in the
 * array
 *
 * @returns none
 *****************************************************************************/
void allocArray( pixel **&color, int rows, int cols )
{
    int i, j;
    // dynamically allocate an array and ensure the storage is avaliable
    color = new ( nothrow ) pixel * [rows];
    if( color == nullptr )
    {
        usageStatement( );
    }

    // dynamically allocate an array for each column in each row and ensure
    // the storage is avaiable if it is not avaible free the memory and exit
    for( i = 0; i < rows; i++ )
    {
        color[i] = new ( nothrow ) pixel[cols];
        if( color[i] == nullptr )
        {
            for( j = 0; j < i; j++ )
            {
                delete[] color[j];
            }
            delete[] color;

            usageStatement( );
        }
    }
}

/** ***************************************************************************
 * @author Cameron Custer
 *
 * @par Description:
 * This function frees the memory from a dynamically allocated 2 dimensional
 * array by freeing the space in every column of every row. This function uses
 * a nested for loop.
 *
 * @param[in] color - the pixel (unsigned char) 2 dimensional array to clear
 * @param[in] rows - an intiger representing the number of rows in the array
 *
 * @returns none
 *****************************************************************************/
void free2d( pixel **&color, int rows )
{
    int i;
    // free the data allocated for the 2 dimensional arrays of pixels
    for( i = 0; i < rows; i++ )
    {
        delete[] color[i];
    }
    delete[] color;
}
