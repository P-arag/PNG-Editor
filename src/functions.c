#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "structs.h"

void read_bytes(FILE *f, void *buffer, size_t buf_sz) {
    size_t n = fread(buffer, buf_sz, 1, f); // Read buf_sz no of bytes from the f

    if (n != 1) {
        if (ferror(f)) {
            fprintf(stderr, "ERROR: could not read %zu bytes from f",
                    buf_sz);
            exit(1);
        } else if (feof(f)) {
            fprintf(stderr, "ERROR: could not read %zu bytes from f: reached the end of file\n",
                    buf_sz);
            exit(1);
        }
    }
}

void reverse_bytes(void *buf, size_t buf_sz) {
    uint8_t *bytes = buf;
    for(size_t i=0; i<buf_sz/2; i++) {
        uint8_t temp = bytes[i];
        bytes[i] = bytes[buf_sz -i -1];
        bytes[buf_sz -i -1] = temp;
    }
}


void print_bytes(uint8_t *buf, size_t len) {
    for(int i=0; i<len; i++) {
        printf("%zu ", buf[i]);
    }
    printf("\n");
}
/*
   void print_chunk(Chunk c) {
   printf("-----\n");
   printf("Chunk type <: %s\n", c.type);
   printf("Chunk size <: %d\n", c.size);
   }*/


// Chunk specific functions 
void parse_IHDR(FILE *f, Image *img, Chunk *c) {
    printf("=========IHDR=========\n");
    read_bytes(f, &img->width, 4);
    reverse_bytes(&img->width, 4);
    
    read_bytes(f, &img->height, 4);
    reverse_bytes(&img->height, 4);

    printf("Width,height <: %d, %d\n", img->width, img->height);


    read_bytes(f, &img->bitDepth, 1);  
    read_bytes(f, &img->colorType, 1);

    printf("Color Type <: %zu, Bit Depth <: %zu\n", img->colorType, img->bitDepth);
    
    read_bytes(f, &img->methods, 3); 
    
    printf("Compression, Filter, Interlace methods <: ");
    print_bytes(img->methods, 3);
    
    if(c->size != 13) { //Read 13bytes till now
        printf("WARNING: Chunk size does not match 13 bytes of IHDR chunk\n");
    }
    
    read_bytes(f, &c->CRC, 4);
    printf("CRC <: %d\n", c->CRC);
    
    printf("======================\n");
}
