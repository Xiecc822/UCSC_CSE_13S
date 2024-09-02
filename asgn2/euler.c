#include "mathlib.h"

#include <stdio.h>

static int iters = 1;

double square(double x) { 
	
	return (x * x);

}

double pi_euler(void) { 
	
	iters = 1;
	
	double pi_approx = 1.0;
	
	double term = 1.0;
	
	double k = 2.0;
	
	// for loop to get value
	for (int i = 1; term >= EPSILON; i++) { 
		
		term = 1.0 / (square(k));
		
		pi_approx += term;
		
		iters += 1;
		
		k += 1.0;
		
	}
	
	return sqrt_newton(pi_approx * 6.0);
	
}

int pi_euler_terms(void) { 
	
	// get iters
	return iters;

}


