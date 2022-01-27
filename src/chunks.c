// Chunk specific functions
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "structs.h"
#include "bytes.h"
#include "misc.h"

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


void parse_IDAT(FILE *f, Image *img, Chunk *c) {
    printf("=========IDAT=========\n");

    uint8_t *chunkData = (uint8_t *) malloc(c->size);

    read_bytes(f, chunkData, c->size);
    uint8_t pixelMultipler = 0;

    switch(img->colorType) {
        case 2:  // Each pixel is an RGB triple
            pixelMultipler = 3;
            break;
        case 6: // Each pixel is an RGBA quadruple
            pixelMultipler = 4;
            break;
        default:
            printf("ERROR: We don't support colorType: %zu\n", img->colorType);
            exit(1);
    }


    printf("Pixel Multiplier <: %zu\n", pixelMultipler);
    uint32_t uncompressedDataSize = img->width*pixelMultipler*img->height + img->height;
    
    printf("Uncompressed size <: %d\n", uncompressedDataSize);

    decompress(chunkData, c->size, chunkData, uncompressedDataSize);
     
    c->size = uncompressedDataSize;
    chunkData = (uint8_t *) realloc(chunkData, uncompressedDataSize); // Shorten the length of chunkData array
    c->data = chunkData;
    
    for(int i=0; i<c->size; i++) {
       //TODO: Apply filter to decompressed data and print pixels nicely, 
    }

    read_bytes(f, &c->CRC, 4);
    printf("CRC <: %d\n", c->CRC);

    printf("======================\n");
}
