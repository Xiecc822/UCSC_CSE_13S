#include "mathlib.h"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

#define OPTIONS "aebmrvwnsh"

int main(int argc, char **argv) { 

	int opt = 0;
	
	bool test_e = false;
	bool test_bbp = false;
	bool test_euler = false;
	bool test_madhava = false;
	bool test_viete = false;
	bool test_wallis = false;
	bool test_sqrt = false;
	bool print_stats = false;
	bool print_help = false;
	bool empty = true;
	//define options
	
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) { 
		
		switch (opt) {
			
			case 'a':
				test_e = test_bbp = test_madhava = test_euler = test_viete = test_wallis = test_sqrt = true;
				empty = false;
				break;
				
			case 'e': 
				test_e = true;
				empty = false;
				break;
				
			case 'b': 
				test_bbp = true;
				empty = false;
				break;
				
			case 'm': 
				test_madhava = true;
				empty = false;
				break;
				
			case 'r': 
				test_euler = true;
				empty = false;
				break;
				
			case 'v': 
				test_viete = true;
				empty = false;
				break;
				
			case 'w': 
				test_wallis = true;
				empty = false;
				break;
			
			case 'n': 
				test_sqrt = true;
				empty = false;
				break;
				
			case 's': 
				print_stats = true;
				empty = false;
				break;
				
			case 'h': 
				print_help = true;
				empty = false;
				break;
				
			}
			
		}
		
		// print e test
		if (test_e) { 
			
			double e_value = e();
			
			printf("e() = %16.15lf,", e_value);
			
			printf(" M_E = %16.15lf,", M_E);
			
			printf(" diff = %16.15lf\n", absolute(e_value - M_E));
			
			if (print_stats) { 
				printf("e() terms = %d\n", e_terms());
			}
			
		}
		
		// print bbp test
		if (test_bbp) { 
		
			double bbp_value = pi_bbp();
			
			printf("pi_bbp() = %16.15lf,", bbp_value);
			
			printf(" M_PI = %16.15lf,", M_PI);
			
			printf(" diff = %16.15lf\n", absolute(bbp_value - M_PI));
			
			if (print_stats) { 
				printf("pi_bbp() terms = %d\n", pi_bbp_terms());
			}
			
		}
		
		// print madhava test
		if (test_madhava) { 
			
			double madhava_value = pi_madhava();
			
			printf("pi_madhava() = %16.15lf,", madhava_value);
			
			printf(" M_PI = %16.15lf,", M_PI);
			
			printf(" diff = %16.15lf\n", absolute(madhava_value - M_PI));
			
			if (print_stats) { 
				printf("pi_madhava() terms = %d\n", pi_madhava_terms());
			}
			
		}
		
		// print euler test
		if (test_euler) { 
			
			double euler_value = pi_euler();
			
			printf("pi_euler() = %16.15lf,", euler_value);
			
			printf(" M_PI = %16.15lf,", M_PI);
			
			printf (" diff = %16.15lf\n", absolute(euler_value - M_PI));
			
			if (print_stats) { 
				printf("pi_euler() terms = %d\n", pi_euler_terms());
			}
			
		}

		// print viete test
		if (test_viete) { 
			
			double viete_value = pi_viete();
			
			printf("pi_viete() = %16.15lf,", viete_value);
			
			printf(" M_PI = %16.15lf,", M_PI);
			
			printf(" diff = %16.15lf\n", absolute(viete_value - M_PI));
			
			if (print_stats) { 
				printf("pi_viete() terms = %d\n", pi_viete_factors());
			}
			
		}
		
		// print wallis series test
		if (test_wallis) { 
		
			double wallis_value = pi_wallis();
			
			printf("pi_wallis() = %16.15lf,", wallis_value);
			
			printf(" M_PI = %16.15lf,", M_PI);
			
			printf(" diff = %16.15lf\n", absolute(wallis_value - M_PI));
			
			if (print_stats) { 
			
				printf("pi_wallis() terms = %d\n", pi_wallis_factors());
			
			}
		
		}
		
		// print newton's sqrt test
		if (test_sqrt) { 
		
			double k = 0.10;
			
			for (double i = 0.00; i <= 9.90; i += k) { 
				
				double newton_value = sqrt_newton(i);
				
				double sqrt_value = sqrt(i);
				
				printf("sqrt_newton(%.2lf) = %16.15lf,", i, newton_value);
				
				printf(" sqrt(%.2lf) = %16.15lf,", i, sqrt_value);
				
				printf(" diff = %16.15lf\n", absolute(newton_value - sqrt_value));
				
				if (print_stats) { 
					printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
				}
				
			}
			
		}
		
		
		// print help message
		if (print_help || empty) { 
			
			printf("SYNOPSIS\n   A test harness for the small numerical library.\n\n");
			
			printf("USAGE\n    ./mathlib-test [-aebmrvwnsh]\n\n");
			
			printf("OPTIONS\n  -a   Runs all tests.\n  -e   Runs e test.\n");
			
			printf("  -b   Runs BBP pi test.\n  -m   Runs Madhava pi test.\n");
			
			printf("  -r   Runs Euler pi test.\n  -v   Runs Viete pi test.\n");
			
			printf("  -w   Runs Wallis pi test.\n");
			
			printf("  -n   Runs Newton square root tests.\n");
			
			printf("  -s   Print verbose statistics.\n");
			
			printf("  -h   Display program synopsis and usage.\n");
			
		}
		
		
		
		return 0;
		
}
		
		
		
