#include "mathlib.h"

#include <stdio.h>

static int iters = 0;

double e(void) { 

	iters = 0;
	
	double e_approx = 0.0;
	
	double term = 1.0;
	
	double k = 0.0;
	
	// for loop to get e_approx
	for (int i = 0; term >= EPSILON; i++) { 
		
		if ((i == 0) || (i == 1)) { 
			k = 1.0;
		}
		else { 
			k += 1.0;
		}
		
		double multiplier = 1.0 / k;
		
		term *= multiplier;
		
		e_approx += term;
		
		iters += 1;
	
	}
	
	return e_approx;
	
}

int e_terms(void) { 
	
	// get iters
	return iters;
	
}
