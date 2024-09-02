#include "names.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

int main(void) { 
	
	typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
	const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };
	// Set up pig
	
	int num_players = 2;
	printf("Number of players (2 to 10)? ");
	int num_assignments = scanf("%d", &num_players);
	// Set up players
	
	if ((num_assignments == 0) || (num_players < 2) || (num_players > 10)) { 
	
		fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
		num_players = 2;
		
	}
	// Validate number of players
	
	unsigned seed = 2023;
	printf("Random-number seed? ");
	num_assignments = scanf("%u", &seed);
	// Set up seed
	
	if (num_assignments < 1) { 
		fprintf(stderr, "Invalid seed. Using 2023 instead.\n");
	}
	// Validate seed number
	
	srandom(seed);
	// Set up initial point for randomization of seeds
	
	// Set up points for all the players
	char points[10];
	for (int person = 0; person < num_players; person += 1) { 
		
		points[person] = 0;
	
	}
	
	// Game begin
	int win = 0;
	while (win != 1) {
		// loop through players as long as no one has won 
		for (int player = 0; player < num_players; player += 1) { 
			// who is rolling the pig
			printf("%s\n", player_name[player]);
			int end_of_round = 0;
			
			// players turn begin
			while ((end_of_round != 1) && (win == 0)) { 
			
				switch (pig[random() % 7]) { 
				
				case JOWLER: 
					// player will get 5 points
					points[player] += 5;
					printf(" rolls 5, has %d\n", points[player]);
					break;
					
				case RAZORBACK: 
					// player will get 10 points
					points[player] += 10;
					printf(" rolls 10, has %d\n", points[player]);
					break;
					
				case TROTTER: 
					// player will get 10 points
					points[player] += 10;
					printf(" rolls 10, has %d\n", points[player]);
					break;
					
				case SNOUTER: 
					// player will get 15 points
					points[player] += 15;
					printf(" rolls 15, has %d\n", points[player]);
					break;
					
				default:
					// pig rolls on side, then end turn
					points[player] += 0;
					printf(" rolls 0, has %d\n", points[player]);
					end_of_round = 1;
					break;
					
				}
				
				// if one player has 100 or more points, he wins
				if (points[player] >= 100) { 
					
					printf("%s won!\n", player_name[player]);
					win = 1;
					break;
				
				}
				
			}
			
			// break out of the for loop if had one winner
			if (win == 1) { 
			
				break;
				
			}
			
		}
		
	}
	
	return 0;
	
}
