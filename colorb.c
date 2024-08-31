#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "bmp.h"  // Include the BMP structure definition
#include "io.h"   // Include read and write functions

void print_help() {
    printf("Usage: colorb -i <input_file> -o <output_file>\n");
}

int main(int argc, char *argv[]) {
    char *input_file = NULL;
    char *output_file = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "i:o:h")) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'h':
                print_help();
                return 0;
            default:
                fprintf(stderr, "Error: Invalid option or missing argument.\n");
                print_help();
                return 1;
        }
    }

    // Check if both input and output files are provided
    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Error: Both input and output files must be specified.\n");
        print_help();
        return 1;
    }

    // Open the input file
    FILE *fin = fopen(input_file, "rb");
    if (fin == NULL) {
        fprintf(stderr, "Error: Unable to open input file '%s'.\n", input_file);
        return 1;
    }

    // Open the output file
    FILE *fout = fopen(output_file, "wb");
    if (fout == NULL) {
        fprintf(stderr, "Error: Unable to open output file '%s'.\n", output_file);
        fclose(fin);
        return 1;
    }

    // Create a BMP structure and read the input BMP file
    BMP *pbmp = bmp_create(fin);

    // Check if bmp_create encountered any errors
    if (pbmp == NULL) {
        fprintf(stderr, "Error: Failed to create BMP structure.\n");
        fclose(fin);
        fclose(fout);
        return 1;
    }
  
    // Reduce the palette to simulate deuteranopia
    bmp_reduce_palette(pbmp);

    // Write the modified BMP structure to the output file
    bmp_write(pbmp, fout);

    // Free the allocated memory
    bmp_free(&pbmp);

    // Close the files
    fclose(fin);
    fclose(fout);

    return 0;
}
