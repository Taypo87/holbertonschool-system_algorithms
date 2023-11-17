#include "graphs.h"
/**
 * graph_add_vertex - adds a new node to a graph
 * @graph: the graph to add a new node to
 * @str: string to be stored in the node
 * Return: pointer to the updated graph
*/
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new, *temp;

	new = malloc(sizeof(vertex_t));
	new->content = strdup(str);
	if (!graph->vertices)
		graph->vertices = new;
	else
	{
		temp = graph->vertices;
		if (strcmp(temp->content, str) == 0)
		{
			free (new);
			return (NULL);
		}
		while (temp->next)
		{
			temp = temp->next;
			if (strcmp(temp->content, str) == 0)
			{
				free (new);
				return (NULL);
			}
		}
		temp->next = new;
	}
	graph->nb_vertices++;
	return (graph);
}