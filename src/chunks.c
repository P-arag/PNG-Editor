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

    //print_bytes(chunkData, c->size);   

    uint8_t parsedChunk[c->size];
    memset(parsedChunk, 0, c->size);   

    int t=0, stride=img->width*pixelMultipler;
    
    for(int i=0; i<img->height; i++) {
        uint8_t filterType = chunkData[t];
        t++;
        
        for(int j=0; j<stride; j++) {
            uint8_t filtX = chunkData[t]; // byte to be filtered
            uint8_t byteToAdd = 0;

            switch(filterType) {
                case 0: // No filter
                    byteToAdd = 0;
                    break;
                case 1: // Sub filter 
                    byteToAdd = (j/pixelMultipler != 0) ? parsedChunk[t-pixelMultipler] : 0;
                    break;
                default:
                    printf("ERROR: We don't support filter type %u\n", filterType);
                    exit(1);
            }

            parsedChunk[t] = filtX + byteToAdd;
            t++;
        }  
    }
    
    free(chunkData);

    c->data = parsedChunk;
    print_bytes(c->data, c->size);
   
    read_bytes(f, &c->CRC, 4);
    printf("CRC <: %d\n", c->CRC);

    printf("======================\n");
}
