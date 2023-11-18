#include "graphs.h"

/**
 * graph_delete - frees all the nodes in a graph
 * @graph: pointer to the graph to be freed
*/

void graph_delete(graph_t *graph)
{
	vertex_t *temp, *temp2;
	edge_t *edges, *edge_temp;

	temp = graph->vertices;
	edges = temp->edges;
	while (temp)
	{
		temp2 = temp;
		temp = temp->next;
		while (edges)
		{
			edge_temp = edges;
			edges = edges->next;
			free(edge_temp);
		}
		free(temp2);
	}
	free(graph);

}
