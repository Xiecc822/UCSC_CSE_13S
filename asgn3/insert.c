#include "insert.h"
#include "stats.h"

#include <stdio.h>
#include <stdint.h>

void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) { 

	reset(stats);
	// reset all stats to 0
	
	for (uint32_t i = 1; i < length; i += 1) { 
	
		uint32_t j = i;
		// begin at second element of array
		
		uint32_t temp = move(stats, arr[i]);
		
		while (j > 0 && cmp(stats, arr[j - 1], temp) > 0) { 
		// while previous number > current number
		
			arr[j] = move(stats, arr[j - 1]);
			
			j -= 1;
		
		}
		
		arr[j] = move(stats, temp);
	
	}
	
	return;

}

