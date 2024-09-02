#include "heap.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>



uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {

	uint32_t left =  2 * first;
	
	uint32_t right = left + 1;
	
	if((right <= last) && (cmp(stats, A[right - 1], A[left - 1]) > 0)) {
	
		return right;
		// right child is the largest value
		
	}
	
	return left;
	// left child is the largest value
	
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) { 

	bool found = false;
	
	uint32_t parent = first;
	
	uint32_t great = max_child(stats, A, parent, last);
	
	while((parent <= (last / 2)) && !(found)) { 
	
		if(cmp(stats, A[great - 1], A[parent - 1]) > 0) {
		// if largest child > parent
		
			swap(stats, &A[parent - 1], &A[great - 1]);
			// swap them
			
			parent = great;
			
			great = max_child(stats, A, parent, last);
			// check the next child
			
		}
		
		else {
		
			found = true;
			// parent > largest child
			
		}
		
	}
	
	return;
	
}

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) { 
	
	for(uint32_t track = (last / 2); track > (first - 1); track -= 1) {
	
		fix_heap(stats, A, track, last);
		// create a max heap
		
	}
	
	return;
	
}


void heap_sort(Stats *stats, uint32_t *A, uint32_t n) { 

	reset(stats);
	
	uint32_t first = 1;
	
	uint32_t last = n;
	
	build_heap(stats, A, first, last);
	// creats a max heap with initial values
	
	for(uint32_t count = last; count > first; count -= 1) {
	
		swap(stats, &A[first - 1], &A[count - 1]);
		
		fix_heap(stats, A, first, count - 1);
		// fix heap until array is ordered
		
	}
	
	return;

}

