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
	if (!graph->vertices)
	{
		free(graph);
		return;
	}
	temp = graph->vertices;
	if (temp->edges)
		edges = temp->edges;
	while (temp)
	{
		temp2 = temp;
		temp = temp->next;
		while (edges)
		{
			edge_temp = edges;
			edges = edges->next;
			free(edge_temp->dest);
			free(edge_temp);
		}
		free(temp2);
	}
	free(graph);

}
