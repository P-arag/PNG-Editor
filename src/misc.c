// Miscellaneous functions
//#pragma once
#include<stdio.h>
#include<stdint.h>
#include<zlib.h>
#include "bytes.h"

int min(int a, int b) {
    if(a<b) return a;
    return b;
}

int max(int a, int b) {
    if(a>b) return a;
    return b;
}

void check_tailed_data(FILE *f, uint8_t *buf, uint32_t buf_sz) {
    long curPos = ftell(f);
    fseek(f, 0L, SEEK_END);
    long extraBytes = ftell(f) - curPos;
    if(extraBytes != 0) {
        printf("INFO: The image has extra information at the end of it\n");
        fseek(f, -extraBytes, SEEK_CUR); // Go back extraBytes number of bytes
        read_bytes(f, buf, min(buf_sz, extraBytes));
    }
}
