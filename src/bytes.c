// Everything realted to bytes
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<zlib.h>
#include "structs.h"

void read_bytes(FILE *f, void *buffer, size_t buf_sz) {
    size_t n = fread(buffer, buf_sz, 1, f); // Read buf_sz no of bytes from the f

    if (n != 1) {
        if (ferror(f)) {
            fprintf(stderr, "ERROR: could not read %zu bytes from f", buf_sz);
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
        printf("%zu", buf[i]);
        if(i != len-1) {
            printf(", ");
        }
    }
    printf("\n");
}

void decompress(uint8_t *in, size_t in_sz, uint8_t *out, size_t out_sz) {
  // zlib struct
  z_stream infstream;
  infstream.zalloc = Z_NULL;
  infstream.zfree = Z_NULL;
  infstream.opaque = Z_NULL;

  // setup "in" as the compressed input and "out" as the output
  infstream.avail_in = (uInt) in_sz; // size of input
  infstream.next_in = (Bytef *) in;
  infstream.avail_out = (uInt) out_sz; // size of output
  infstream.next_out = (Bytef *) out;

  // the actual DE-compression work.
  inflateInit(&infstream);
  inflate(&infstream, Z_NO_FLUSH);
  inflateEnd(&infstream);
}
