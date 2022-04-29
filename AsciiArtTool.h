//
// Created by Shada Sabea on 24/04/2022.
//

#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include "RLEList.h"
#include <stdio.h>


/**
 * asciiArtRead : changing the content of the file given to RLEList.
 *
 * @param in_stream - file contains the asci art image .
 * @return
 *   RLEList  contains the characters in the file given .
 *   Null  if a NULL was sent as one of the parameter.
 */
RLEList asciiArtRead(FILE* in_stream);
/**
 * asciiArtPrint : moving the content of the RLEList given to the file given.
 *
 * @param list  - RLEList .
 * @param out_stream  - the file on which will be written the content .
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
 * 	LIST_SUCCESS if the content was moved successfully.
 *RLE_LIST_ERROR  any other reason.
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
/**
 * asciiArtPrintEncoded : printing encoded image to the file given.
 *
 * @param list - RLEList contains the characters of the image ;
 * @param out_stream - file on which the image will be printed .
 * @return
 *   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
 *   LIST_SUCCESS if the charcters were moved successfully.
 *    RLE_LIST_ERROR  any other reason.
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif //HW1_ASCIIARTTOOL_H


