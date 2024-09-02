#include "path.h"
#include "stack.h"
#include "graph.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>


typedef struct path { 

	Stack *vertices;
	uint32_t total_weight;

} Path;

Path *path_create(uint32_t capacity) { 

	Path *p = malloc(sizeof(Path));
	p -> total_weight = 0;
	p -> vertices = stack_create(capacity);
	return p;

}

void path_free(Path **pp) { 

	if (pp != NULL && *pp != NULL) { 
	
		stack_free(&((*pp) -> vertices));
		free(*pp);
		*pp = NULL;
	
	}
	
}

uint32_t path_vertices(const Path *p) { 

	return stack_size(p -> vertices);

}

uint32_t path_distance(const Path *p) { 

	return p -> total_weight;

}

void path_add(Path *p, uint32_t val, const Graph *g) { 
	
	if (!stack_empty(p -> vertices)) { 
	
		uint32_t last_vertex;
		stack_peek(p -> vertices, &last_vertex);
		p -> total_weight += graph_get_weight(g, last_vertex, val);
	
	}
	
	stack_push(p -> vertices, val);

}

uint32_t path_remove(Path *p, const Graph *g) { 

	uint32_t removed_vertex;
	stack_pop(p -> vertices, &removed_vertex);
	
	if (!stack_empty(p -> vertices)) { 
		
		uint32_t last_vertex;
		stack_peek(p -> vertices, &last_vertex);
		p -> total_weight -= graph_get_weight(g, last_vertex, removed_vertex);
	
	}
	else { 
	
		p -> total_weight = 0;
	
	}
	
	return removed_vertex;

}

void path_copy(Path *dst, const Path *src) { 

	dst -> total_weight = src -> total_weight;
	stack_copy(dst -> vertices, src -> vertices);

}

void path_print(const Path *p, FILE *f, const Graph *g) { 

	char **vertex_names = graph_get_names(g);
	Stack *temp_stack = stack_create(stack_size(p -> vertices));
	
	uint32_t vertex;
	while (stack_pop(p -> vertices, &vertex)) { 
	
		stack_push(temp_stack, vertex);
	
	}
	
	while (!stack_empty(temp_stack)) { 
	
		stack_pop(temp_stack, &vertex);
		fprintf(f, "%s\n", vertex_names[vertex]);
		stack_push(p -> vertices, vertex);
	
	}
	
	fprintf(f, "%s\n", vertex_names[0]);
	stack_free(&temp_stack);

}




