#include<stdlib.h>
#include<stdint.h>
#include "structs.h"
// Bytes
void read_bytes(FILE *f, void *buffer, size_t buf_sz); 
void reverse_bytes(void *buf, size_t buf_sz);

// Printing
void print_bytes(void *buf, size_t len);

// Chunk specific
void parse_IHDR(FILE *f, Image *img, Chunk *c);
void parse_IDAT(FILE *f, Image *img, Chunk *c);

// Misc
void check_tailed_data(FILE *f, uint8_t *buf, uint32_t buf_sz); // Assuming cursor is at end of IEND chunk

//void print_chunk(Chunk c);
