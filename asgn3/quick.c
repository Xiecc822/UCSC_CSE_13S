#include "quick.h"
#include "stats.h"

#include <stdio.h>
#include <stdint.h>

uint32_t partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {

	uint32_t i = low -1;
	
	for (uint32_t j = low; j < high; j += 1) {
	
		if (cmp(stats, A[high - 1], A[j - 1]) > 0) {
		// compare each value to pivot
		
			i += 1;
			
			swap(stats, &A[j - 1], &A[i - 1]);
			// put value to the left half if smaller than pivot
			
		}
	
	}
	
	swap(stats, &A[i], &A[high - 1]);
	// pivot placed after all values smaller than it
	
	return i + 1;
	
}

void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) { 
	
	if (low < high) {
	
		uint32_t pivot = partition(stats, A, low, high);
		// gets index of partition
		
		quick_sorter(stats, A, low, pivot - 1);
		// sorts left half of partition recursively
		
		quick_sorter(stats, A, pivot + 1, high);
		// sorts right half of partition recursively
				
	}
	
	return;
	
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) { 

	reset(stats);
	
	quick_sorter(stats, A, 1, n);
	
	return;	

}
