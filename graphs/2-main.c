#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"
#include "names.h"
#include "edges.h"

void graph_delete(graph_t *graph);
void graph_display(const graph_t *graph);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	graph_t *graph;
	size_t i;

	graph = graph_create();
	if (!graph)
	{
		printf("Failed to create graph\n");
		return (EXIT_FAILURE);
	}

	for (i = 0; i < NB_NAMES; i++)
	{
		if (!graph_add_vertex(graph, _names[i]))
		{
			printf("Failed to add [%s]\n", _names[i]);
			return (EXIT_FAILURE);
		}
	}

	if (!graph_add_edge(graph, _names[0], _names[1], UNIDIRECTIONAL))
	{
		printf("Failed to add edge between ");
		printf("%s and %s\n", _names[0], _names[1]);
		return (EXIT_FAILURE);
	}

	graph_display(graph);
	//graph_delete(graph);

	return (EXIT_SUCCESS);
}