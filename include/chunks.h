#include<stdlib.h>
#include<stdint.h>
#include "structs.h"

void parse_IHDR(FILE *f, Image *img, Chunk *c);
void parse_IDAT(FILE *f, Image *img, Chunk *c);
