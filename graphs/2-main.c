#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * graph_display - Utility function to display the adjacency linked list
 *
 * @graph: Pointer to the graph structure to be displayed
 */
static void graph_display(const graph_t *graph)
{
	vertex_t *v;

	if (!graph)
		return;

	printf("Number of vertices: %lu\n", graph->nb_vertices);
	for (v = graph->vertices; v; v = v->next)
	{
		edge_t *e;

		printf("[%lu] %s", v->index, v->content);
		if (v->edges)
			printf(" ->");
		for (e = v->edges; e; e = e->next)
		{
			if (e->dest)
				printf("%lu", e->dest->index);
			else
				printf("nil");

			if (e->next)
				printf("->");
		}
		printf("\n");
	}
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	graph_t *graph;

	graph = graph_create();
	if (!graph)
	{
		fprintf(stderr, "Failed to create graph\n");
		return (EXIT_FAILURE);
	}

	if (!graph_add_vertex(graph, "San Francisco"))
	{
		fprintf(stderr, "Failed to add vertex\n");
		return (EXIT_FAILURE);
	}

	graph_display(graph);

	if (!graph_add_vertex(graph, "Seattle") ||
		!graph_add_vertex(graph, "New York") ||
		!graph_add_vertex(graph, "Miami") ||
		!graph_add_vertex(graph, "Chicago") ||
		!graph_add_vertex(graph, "Houston") ||
		!graph_add_vertex(graph, "Las Vegas") ||
		!graph_add_vertex(graph, "Boston"))
	{
		fprintf(stderr, "Failed to add vertex\n");
		return (EXIT_FAILURE);
	}

	graph_display(graph);

	if (!graph_add_vertex(graph, "San Francisco"))
		fprintf(stderr, "Failed to add \"San Francisco\"\n");

	return (EXIT_SUCCESS);
}
