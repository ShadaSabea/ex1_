#ifndef ASCII_ART
#define ASCII_ART

#include "RLEList.h"
#include <stdio.h>


/**
 * asciiArtRead : Converts the contents in a given file to RLEList.
 *
 * @param in_stream - A descriptor to a file containing ascii art image.
 * @return
 *   Null  if a NULL was sent as one of the parameter.
 *   A new RLEList that contains the characters in the given file (in_stream).
 */

RLEList asciiArtRead(FILE* in_stream);


/**
 * asciiArtPrint : prints the image described in a given RLE list to the given file.
 * 
 * @param list  - The RLE list to be written in the given file.
 * @param out_stream  - A descriptor to a file that the image will be written in .
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
 * 	RLE_LIST_ERROR  if the operation failed.
 * 	LIST_SUCCESS if the image has been printed successfully.
 *
 */
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream);


/**
 * asciiArtPrintEncoded : Prints encoded image to the image described
 * in RLE list into the given file.
 *
 * @param list - The RLE list that describes the image ;
 * @param out_stream - A descriptor to a file that the encoded image will be written in .
 * @return
 *   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
 *   RLE_LIST_ERROR  if the operation failed.
 *   LIST_SUCCESS if the encoded image has been printed successfully.
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream);


#endif
