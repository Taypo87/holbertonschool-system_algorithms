#include "graphs.h"
/**
 * graph_create - allocates and initializes a new vertice
 * Return: pointer to the new node
*/
graph_t *graph_create(void)
{
	graph_t *new;

	new = malloc(sizeof(graph_t));
	new->nb_vertices = 0;
	new->vertices = 0;

	return (new);
}
