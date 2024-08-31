#include "io.h"
#include <stdio.h>

#include <stdint.h>

void read_uint8(FILE *fin, uint8_t *px) {
    int result = fgetc(fin);
    if (result == EOF) {
        fprintf(stderr, "unexpected end of file\n");
        exit(1);
    }
    *px = (uint8_t)result;
}

void read_uint16(FILE *fin, uint16_t *px) {
    uint8_t low_byte, high_byte;
    read_uint8(fin, &low_byte);
    read_uint8(fin, &high_byte);
    *px = (uint16_t)((high_byte << 8) | low_byte);
}

void read_uint32(FILE *fin, uint32_t *px) {
    uint16_t low_word, high_word;
    read_uint16(fin, &low_word);
    read_uint16(fin, &high_word);
    *px = (uint32_t)((high_word << 16) | low_word);
}

void write_uint8(FILE *fout, uint8_t x) {
    int result = fputc((int)x, fout);
    if (result == EOF) {
        fprintf(stderr, "unable to write file\n");
        exit(1);
    }
}

void write_uint16(FILE *fout, uint16_t x) {
    write_uint8(fout, (uint8_t)x);
    write_uint8(fout, (uint8_t)(x >> 8));
}

void write_uint32(FILE *fout, uint32_t x) {
    write_uint16(fout, (uint16_t)x);
    write_uint16(fout, (uint16_t)(x >> 16));
}

