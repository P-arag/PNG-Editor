#pragma once
#include<stdint.h>
#include<stdbool.h>


//uint8_t VALID_PNG_HEADER[] = {137, 80, 78, 71, 13, 10, 26, 10};

typedef struct Chunk {
    uint32_t index;
    uint32_t size; 
    char type[5]; //4 byte type, extra byte for null termination
    uint32_t CRC;
    struct Chunk *nextChunk;
} Chunk;

typedef struct {
    uint8_t sig[8]; // First 8bytes png signature
    bool isSigValid;
    uint32_t width, height;
    uint8_t bitDepth, colorType, methods[3]; //Compression, Filter, Interlace methods
    uint32_t totalChunks;
    Chunk *head, *tail;
} Image;
