#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include "structs.h"
#include "functions.h"

uint8_t VALID_PNG_HEADER[] = {137, 80, 78, 71, 13, 10, 26, 10};

int main() {
    FILE *f = fopen("../img.png", "rb");
    Image img;
    img.totalChunks = 0;

    read_bytes(f, img.sig, 8);
    printf("Png header <: ");
    print_bytes(img.sig, 8);

    if(memcmp(img.sig, VALID_PNG_HEADER, 8) != 0) {
        printf("WARNING: Image does not appear to be a valid png image, wrong header\n"); 
    };

    while(1) {
        Chunk c;
        
        printf("--------\n");
        read_bytes(f, &c.size, sizeof(c.size)); // 4byte chunk len 
        reverse_bytes(&c.size, sizeof(c.size));
        
        read_bytes(f, c.type, 4); // 4byte chunk type
        c.type[4] = '\0';
        
        printf("Chunk type <: %s\n", c.type);
        printf("Chunk size <: %d\n", c.size);
        
        img.chunks[img.totalChunks] = c;
        img.totalChunks++;
        
        if(strcmp(c.type, "IHDR") == 0) {
            parse_IHDR(f, &img, &c);
            continue;
        } else if(strcmp(c.type, "IEND") == 0) {
            read_bytes(f, &c.CRC, 4);
            break;
        }

        fseek(f, c.size+4, SEEK_CUR);
//TODO: Parse IDAT chunk using zlib
        //parse_IHDR(f, &img, &c);
    }
    
    /*for(int i=0; i<img.totalChunks; i++) {
        printf("%s\n", img.chunks[i].type);
     }*/

    uint8_t tailed_data[10];
    check_tailed_data(f, tailed_data, 10);  
    printf("Tailed data <: ");
    print_bytes(tailed_data, 10);
    fclose(f);
}
// Another branch
