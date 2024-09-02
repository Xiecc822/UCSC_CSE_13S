#include "stack.h"
#include "path.h"
#include "graph.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#define MAX_LINE_LENGTH 1024

// Function to print the help message
void print_help() { 

	printf("Usage: tsp [options]\n");
	printf("\n");
	printf("-i infile    Specify the input file path containing the cities and edges\n");
	printf("             of a graph. If not specified, the default input should be\n");
	printf("             set as stdin.\n");
	printf("\n");
	printf("-o outfile   Specify the output file path to print to. If not specified,\n");
	printf("             the default output should be set as stdout.\n");
	printf("\n");
	printf("-d           Specifies the graph to be directed.\n");
	printf("\n");
	printf("-h           Prints out a help message describing the purpose of the\n");
	printf("             graph and the command-line options it accepts, exiting the\n");
	printf("             program afterwards.\n");

}

// Depth First Search (DFS) to find the Hamiltonian cycle
void dfs(Graph *g, Path *current_path, Path *best_path, uint32_t current_vertex, bool *visited) { 

	uint32_t num_vertices = graph_vertices(g);
	
	visited[current_vertex] = true;
	path_add(current_path, current_vertex, g);
	
	if (path_vertices(current_path) == num_vertices && graph_get_weight(g, current_vertex, START_VERTEX) > 0) { 
	
		uint32_t cycle_weight = path_distance(current_path) + graph_get_weight(g, current_vertex, START_VERTEX);
		
		if (path_vertices(best_path) == 0 || cycle_weight < path_distance(best_path)) { 
		
			path_copy(best_path, current_path);
			path_add(best_path, START_VERTEX, g);
		
		}
	
	}
	
	for (uint32_t i = 0; i < num_vertices; i++) { 
	
		if (!visited[i] && graph_get_weight(g, current_vertex, i) > 0) { 
		
			dfs(g, current_path, best_path, i, visited);
		
		}
	
	}
	
	visited[current_vertex] = false;
	path_remove(current_path, g);

}

int main(int argc, char **argv) { 

	int opt;
	bool directed = false;
	char *input_file = NULL;
	char *output_file = NULL;
	FILE *infile = stdin;
	FILE *outfile = stdout;
	
	while ((opt = getopt(argc, argv, "hdi:o:")) != -1) { 
	
		// Command line options
		switch (opt) { 
		
			case 'h': 
				print_help();
				return 0;
				break;
			
			case 'd': 
				directed = true; 
				break;
			
			case 'i': 
				infile = fopen(optarg, "r");
				if (infile == NULL) { 
				
					printf("tsp:  error reading input file %s\n", optarg);
					print_help();
					return EXIT_FAILURE;
				
				}
				break;
				
			case 'o': 
				outfile = fopen(optarg, "w");
				if (outfile == NULL) { 
				
					printf("Error: Cannot open file %s\n", optarg);
					return EXIT_FAILURE;
				
				}
				break;
				
			default: 
				fprintf(stderr, "Invalid option\n");
				print_help();
				return 1;
		
		}
	
	}
	
	// Read the graph from a file
	// Read vertex names
	uint32_t vertices;
	fscanf(infile, "%d\n", &vertices);
	
	char vertex_names[vertices][MAX_LINE_LENGTH];
	
	for (uint32_t i = 0; i < vertices; i++) { 
	
		if (fgets(vertex_names[i], MAX_LINE_LENGTH, infile) == NULL) { 
		
			return 1;
		
		}
		
		vertex_names[i][strcspn(vertex_names[i], "\n")] = '\0';
		
	}
	
	Graph *g = graph_create(vertices, directed);
	
	for (uint32_t i = 0; i < vertices; i++) { 
	
		graph_add_vertex(g, vertex_names[i], i);
	
	}


	// Read edges
	uint32_t edges;
	fscanf(infile, "%u", &edges);
	uint32_t start, end, weight;
	for (uint32_t i = 0; i < edges; i++) { 
	
		fscanf(infile, "%u %u %u", &start, &end, &weight);
		graph_add_edge(g, start, end, weight);
	
	}
	
	
	// Perform TSP using DFS
	uint32_t start_vertex = START_VERTEX;
	Path *current = path_create(vertices);
	Path *best = path_create(vertices);
	bool *visited = calloc(vertices, sizeof(bool));
	dfs(g, current, best, start_vertex, visited);
	
	// Print the result
	if (path_vertices(best) == vertices) { 
	
		fprintf(outfile, "Alissa starts at:\n");
		path_print(best, outfile, g);
		fprintf(outfile, "Total Distance: %u\n", path_distance(best));
		
	}
	else { 
	
		fprintf(outfile, "No path found! Alissa is lost!\n");
	
	}
	
	
	// Clean up
	path_free(&best);
	path_free(&current);
	free(visited);
	graph_free(&g);
	if (infile != stdin) { 
	
		fclose(infile);
	
	}
	if (outfile != stdout) { 
	
		fclose(outfile);
	
	}
	
	return 0;
	
}


