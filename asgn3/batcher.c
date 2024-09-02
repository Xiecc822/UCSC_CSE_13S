#include "batcher.h"
#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {

	reset(stats);
	// reset all stats to 0
	
	if (n == 0) { 
	
		return;
	
	}
	
	uint32_t t = 0; 
	
	while (n >> t) { 
	// n.bit length
	
		t++;
	
	}
	
	uint32_t p = 1 << (t - 1);
	
	while (p > 0) { 
	
		uint32_t q = 1 << (t - 1);
		// q = 2^(t - 1)
		
		uint32_t r = 0; 
		
		uint32_t d = p; 
		
		while (d > 0) { 
		
			for (uint32_t i = 0; i < n - d; i++) { 
			
				if ((i & p) == r && cmp(stats, A[i], A[i + d]) == 1) { 
				
					swap(stats, &A[i], &A[i + d]);
				
				}
			
			}
			
			d = q - p;
			
			q >>= 1;
			
			r = p;
		
		}
		
		p >>= 1;
	
	}
		
	return;
	
}

