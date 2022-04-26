#ifndef ASCII_ART
#define ASCII_ART

#include "RLEList.h"
#include <stdio.h>


/**
 * @brief Converts the contents in a given file to RLEList
 * @param in_stream - A descriptor to a file containing ascii art image
 * @return 
 *   A new RLEList that contains the characters in in_stream
 */

RLEList asciiArtRead(FILE* in_stream);


/**
 * @brief 
 * 
 * @param list 
 * @param out_stream 
 * @return RLEListResult 
 */
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream);


/**
 * @brief 
 * 
 * @param list 
 * @param out_stream 
 * @return RLEListResult 
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream);


#endif
