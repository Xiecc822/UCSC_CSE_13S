#include "shell.h"
#include "gaps.h"
#include "stats.h"

#include <stdio.h>
#include <stdint.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {

	reset(stats); 
	// reset all stats to 0
    
    for (uint32_t gap = 0; gap < GAPS; gap += 1) {
    
        for (uint32_t i = gaps[gap]; i < n; i+= 1) {
    
            uint32_t j = move(stats, i);
    
            uint32_t temp = A[i];
    
            while (j >= gaps[gap] && cmp(stats, temp, A[j - gaps[gap]]) == -1) { 
    
                A[j] = move(stats, A[j - gaps[gap]]);
    
                j -= gaps[gap];
    
            }
    
            A[j] = move(stats, temp);
    
        }
    
    }
    
    return;
	
}


