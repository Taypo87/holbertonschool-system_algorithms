#include "graphs.h"

/**
 * graph_delete - frees all the nodes in a graph
 * @graph: pointer to the graph to be freed
*/

void graph_delete(graph_t *graph)
{
	vertex_t *temp = NULL, *temp2 = NULL;
	edge_t *edges = NULL, *edge_temp = NULL;

	if (!graph)
		return;

	temp = graph->vertices;
	while (temp)
	{
		temp2 = temp;
		edges = temp->edges;

		while (edges)
		{
			edge_temp = edges;
			edges = edges->next;
			free(edge_temp);
		}

		temp = temp->next;
		free(temp2->content);
		free(temp2);
	}

	free(graph);
}
