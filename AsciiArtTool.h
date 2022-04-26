//
// Created by Shada Sabea on 24/04/2022.
//

#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include "RLEList.h"
#include <stdio.h>

RLEList asciiArtRead(FILE* in_stream);
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //HW1_ASCIIARTTOOL_H


