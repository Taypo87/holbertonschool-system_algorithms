#include "graphs.h"
/**
 * graph_add_vertex - adds a new node to a graph
 * @graph: the graph to add a new node to
 * @str: string to be stored in the node
 * Return: pointer to the new node
*/
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new, *temp;


	if(!str)
		return (NULL);
	new = malloc(sizeof(vertex_t));
	new->content = strdup(str);
	new->edges = NULL;
	new->index = 0;
	new->nb_edges = 0;
	new->next = NULL;
	if (!graph->vertices)
		graph->vertices = new;
	else
	{
		new->index++;
		temp = graph->vertices;
		if (strcmp(temp->content, str) == 0)
		{
			free(new);
			return (NULL);
		}
		while (temp->next)
		{
			temp = temp->next;
			new->index++;
			if (strcmp(temp->content, str) == 0)
			{
				free(new);
				return (NULL);
			}
		}
		temp->next = new;
	}
	graph->nb_vertices += 1;
	return (new);
}
