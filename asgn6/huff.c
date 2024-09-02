#include "bitwriter.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Code {

    uint64_t code;
    uint8_t code_length;

} Code;

uint64_t fill_histogram(Buffer *inbuf, double *histogram) {

    uint64_t filesize = 0;
    // Clear histogram array
    for (int i = 0; i < 256; i++) {

        histogram[i] = 0.0;
    }

    // Read bytes from inbuf and update histogram
    uint8_t byte;
    while (read_uint8(inbuf, &byte)) {

        histogram[byte]++;
        filesize++;
    }

    // Apply the hack to ensure at least two non-zero histogram entries
    histogram[0x00]++;
    histogram[0xff]++;

    return filesize;
}

Node *create_tree(double *histogram, uint16_t *num_leaves) {

    PriorityQueue *pq = pq_create();

    // Create nodes for non-zero histogram entries and enqueue them
    for (int i = 0; i < 256; i++) {

        if (histogram[i] > 0) {

            Node *node = node_create(i, histogram[i]);
            enqueue(pq, node);
            ++(*num_leaves);
        }
    }

    // Run Huffman Coding algorithm
    while (!pq_size_is_1(pq)) {

        Node *left, *right;
        dequeue(pq, &left);
        dequeue(pq, &right);

        Node *internal = node_create(0, left->weight + right->weight);
        internal->left = left;
        internal->right = right;

        enqueue(pq, internal);
    }

    Node *code_tree = NULL;
    dequeue(pq, &code_tree);

    pq_free(&pq);

    return code_tree;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {

    if (node->left == NULL && node->right == NULL) {

        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;

    } else {

        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= ((uint64_t) 1 << code_length);
        fill_code_table(code_table, node->right, code, code_length + 1);
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {

    if (node->left == NULL && node->right == NULL) {

        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);

    } else {

        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {

    // Write file signature
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);

    // Write code tree
    huff_write_tree(outbuf, code_tree);

    // Compress input file using Huffman coding
    uint8_t byte;
    while (read_uint8(inbuf, &byte)) {

        Code code = code_table[byte];

        for (int i = 0; i < code.code_length; i++) {

            bit_write_bit(outbuf, code.code & 1);
            code.code >>= 1;
        }
    }
}

int main(int argc, char **argv) {

    int opt;
    char *input_filename = NULL;
    char *output_filename = NULL;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "i:o:h")) != -1) {

        switch (opt) {

        case 'i': input_filename = optarg; break;

        case 'o': output_filename = optarg; break;

        case 'h':
            printf("Usage: huff -i infile -o outfile\n");
            printf("       huff -v -i infile -o outfile\n");
            printf("       huff -h\n");
            return 1;

        default:
            fprintf(stderr, "huff:  unknown or poorly formatted option -%c\n", optopt);
            printf("Usage: huff -i infile -o outfile\n");
            printf("       huff -v -i infile -o outfile\n");
            printf("       huff -h\n");
            return 1;
        }
    }

    // Check if input and output filenames are provided
    if (input_filename == NULL || output_filename == NULL) {

        printf("huff:  error reading input file %s\n", input_filename);
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile\n");
        printf("       huff -h\n");
        return 1;
    }

    Buffer *inbuf = read_open(input_filename);
    if (inbuf == NULL) {

        printf("huff:  error reading input file %s\n", input_filename);
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile\n");
        printf("       huff -h\n");
        return 1;
    }

    // Step 1: Fill histogram
    double histogram[256];
    uint64_t filesize = fill_histogram(inbuf, histogram);

    // Step 2: Create code tree
    uint16_t num_leaves;
    Node *code_tree = create_tree(histogram, &num_leaves);

    // Step 3: Fill code table
    Code code_table[256];
    fill_code_table(code_table, code_tree, 0, 0);

    read_close(&inbuf);

    inbuf = read_open(input_filename);

    // Open output file for writing
    BitWriter *outbuf = bit_write_open(output_filename);
    if (outbuf == NULL) {

        printf("huff:  error writing output file %s\n", output_filename);
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile\n");
        printf("       huff -h\n");
        read_close(&inbuf);
        return 1;
    }

    // Step 4 and 5: Compress input file
    huff_compress_file(outbuf, inbuf, filesize, num_leaves, code_tree, code_table);

    // Clean up
    read_close(&inbuf);
    bit_write_close(&outbuf);
    node_free(&code_tree);

    return 0;
}
