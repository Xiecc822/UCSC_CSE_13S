#include "bmp.h"
#include "io.h"

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

    int opt;
    char *input_file = NULL;
    char *output_file = NULL;

    while ((opt = getopt(argc, argv, "hi:o:")) != -1) {

        // Command line options
        switch (opt) {

        case 'h':
            printf("Usage: colorb -i infile -o outfile\n");
            printf("       colorb -h\n");
            return 0;
            break;

        case 'i': input_file = optarg; break;

        case 'o': output_file = optarg; break;

        default:
            printf("colorb:  unknown or poorly formatted option %s\n", optarg);
            printf("Usage: colorb -i infile -o outfile\n");
            printf("       colorb -h\n");
            return 1;
        }
    }

    // Check if required options are provided
    if (input_file == NULL || output_file == NULL) {

        fprintf(stderr, "error reading input file %s\n", input_file);
        printf("Usage: colorb -i infile -o outfile\n");
        printf("       colorb -h\n");
        return 1;
    }

    // Read the input BMP file
    Buffer *input_buffer = read_open(input_file);
    if (input_buffer == NULL) {

        fprintf(stderr, "Failed to open input file %s/n", input_file);
        return 1;
    }

    BMP *bmp = bmp_create(input_buffer);

    if (bmp == NULL) {

        fprintf(stderr, "Failed to read input BMP file %s\n", input_file);
        read_close(&input_buffer);
        return 1;
    }

    // Perform color transformation
    bmp_reduce_palette(bmp);

    // Write the transformed BMP to the output file
    Buffer *output_buffer = write_open(output_file);

    if (output_buffer == NULL) {

        fprintf(stderr, "Failed to open output file %s\n", output_file);
        bmp_free(&bmp);
        read_close(&input_buffer);
        return 1;
    }

    bmp_write(bmp, output_buffer);

    // Close files and free memory
    write_uint8(output_buffer, 0);
    write_close(&output_buffer);
    bmp_free(&bmp);
    read_close(&input_buffer);

    return 0;
}
