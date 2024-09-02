#include "heap.h"
#include "batcher.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "insert.h"
#include "stats.h"
#include "gaps.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "Hahbsqir:n:p:"

void random_arr_gen(uint32_t *arr, int seed, uint32_t size) { 

	srandom(seed);
	// set the seed of gen
	
	for (uint32_t i = 0; i < size; i++) { 
	
		uint64_t num = random() & (1 << 30) - 1;
		// bit masks to 30 bits
		
		arr[i] = num;
	
	}
	
	return;

}

void usage(char *exec) { 

	fprintf(stderr,
		"SYNOPSIS\n"
		"  A collection of comparison-based sorting algorithms.\n\n"
		"USAGE\n"
		"  %s [-Hahbsqi] [-n length] [-p elements] [-r seed]\n\n"
		"OPTIONS\n"
		"   -H              Display program help and usage.\n"
		"   -a              Enable all sorts.\n"
		"   -h              Enable Heap Sort.\n"
		"   -b              Enable Batcher Sort.\n"
		"   -s              Enable Shell Sort.\n"
		"   -q              Enable Quick Sort.\n"
		"   -i              Enable Insertion Sort.\n"
		"   -n length       Specify number of array elements (default: 100).\n"
		"   -p elements     Specify number of elements to print (default: 100).\n"
		"   -r seed         Specify random seed (default: 13371453).\n", 
		exec);

}

int main(int argc, char **argv) { 

	Stats stats;
	
	int opt = 0;
	// default values
	
	int seed = 13371453;
	
	uint32_t length = 100;
	
	uint32_t elements = 100;
	
	enum sorts { INSERTION, HEAP, SHELL, QUICK, BATCHER, END };
	
	char *sort_names[] = { "Insertion Sort", "Heap Sort", "Shell Sort", "Quick Sort", "Batcher Sort" };
	
	Set set = set_empty();
	
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) { 
	
		switch (opt) { 
		
		case 'H': usage(argv[0]); return 0;
		case 'a': 
			set = set_insert(set, INSERTION);
			set = set_insert(set, HEAP);
			set = set_insert(set, SHELL);
			set = set_insert(set, QUICK);
			set = set_insert(set, BATCHER);
			break;
		case 'h': set = set_insert(set, HEAP); break;
		case 'b': set = set_insert(set, BATCHER); break;
		case 's': set = set_insert(set, SHELL); break;
		case 'q': set = set_insert(set, QUICK); break;
		case 'i': set = set_insert(set, INSERTION); break;
		case 'n': length = strtoul(optarg, NULL, 10); break;
		case 'p': elements = strtoul(optarg, NULL, 10); break;
		case 'r': seed = strtoul(optarg, NULL, 10); break;
		
		}
	
	}
	
	if (elements > length) { 
	// check not print too many elements
	
		elements = length;
	
	}
	
	if (set == 0) { 
	// if no sorts are entered prompt user to enter at least one sort
	
		printf("Select at least one sort to perform.\n");
		usage(argv[0]);
		return -1;
	
	}
	
	// initialize array
	uint32_t *random_arr;
	
	random_arr = malloc(length * sizeof(uint32_t));
	
	void (*sorts_ptr[5])(Stats * stats, uint32_t * arr, uint32_t length) 
		= { insertion_sort, heap_sort, shell_sort, quick_sort, batcher_sort };
	// pointer to functions to know which one to call in for loop
	
	for (int i = 0; i < END; i++) { 
	
		if (set_member(set, i)) { 
		
			random_arr_gen(random_arr, seed, length);
			
			sorts_ptr[i](&stats, random_arr, length);
			
			print_stats(&stats, sort_names[i], length);
			
			for (uint32_t i = 0; i < elements; i++) { 
			
				if (i % 5 == 0 && i != 0) { 
				
					printf("\n");
				
				}
				
				printf("%13" PRIu32, random_arr[i]);
				
				if (i == elements - 1) { 
				
					printf("\n");
				
				}
			
			}
		
		}
	
	}
	
	free(random_arr);
	
	return 0;

}

