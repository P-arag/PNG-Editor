#pragma once
#include<stdint.h>

void print_bytes(void *buf, size_t len);

void read_bytes(FILE *f, void *buffer, size_t buf_sz);
void reverse_bytes(void *buf, size_t buf_sz);

void decompress(uint8_t *in, size_t in_sz, uint8_t *out, size_t out_sz);
