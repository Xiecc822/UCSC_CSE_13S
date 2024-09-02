#include "mathlib.h"

#include <stdio.h>

static int iters = 0;

double pi_wallis(void){ 
	
	iters = 0;
	
	double terms = 1.0;
	
	double x = 1.0;
	
	// for loop to get value
	for (int i = 1; x >= EPSILON; i++) { 
		
		double numerator = 4.0 * i * i;
		
		double denominator = numerator - 1.0; 
		
		terms *= (numerator / denominator);
		
		iters += 1;
		
		x = (numerator / denominator) - 1.0;
		
	}
	
	return 2 * terms;

}

int pi_wallis_factors(void) { 
	
	// get iters
	return iters;
	
}
