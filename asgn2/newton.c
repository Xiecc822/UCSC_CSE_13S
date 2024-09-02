#include "mathlib.h"

#include <stdio.h>

static int iters = 0;

double sqrt_newton(double num) { 
	
	iters = 0;
	
	double x = num;
	
	double y = 1.0;
	
	double z = 0.0;
	
	// while loop to get y
	while (absolute(y - z) > EPSILON) { 
	
		z = y;
		
		y = 0.5 * (z + (x / z));
		
		iters += 1;
		
	}
	
	return y;
	
}

int sqrt_newton_iters(void) { 
	
	// get iters
	return iters;
	
}

