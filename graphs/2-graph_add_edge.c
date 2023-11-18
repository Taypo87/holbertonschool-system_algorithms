#include "graphs.h"

/**
 * get_vertex - finds the vertex for a given string
 * @graph: the graph to check for the vertex
 * @str: the key for the vertex
 * Return: pointer to the vertex or NULL if not found
*/
static vertex_t *get_vertex(graph_t  *graph, const char *str)
{
	vertex_t *temp;

	temp = graph->vertices;
	while (temp)
	{
		if (strcmp(str, temp->content) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}


/**
 * set_edge - creates a new edge and assigns it to the edge list
 * @src: the source vertex
 * @dest: the destination vertex
 * Return: VOID
*/
static void set_edge(vertex_t *src, vertex_t *dest)
{

	edge_t *new = malloc(sizeof(edge_t)), *temp;

	new->dest = dest;
	new->next = NULL;
	if (!src->edges)
		src->edges = new;
	else
	{  
		temp = src->edges;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

/**
 * graph_add_edge - adds a new edge to a given vertex in a graph
 * @graph: the graph to operate on
 * @src: key of the source vertex
 * @dest: key of the destination vertex
 * @type: the type of connection
 * Return: 1 on success else 0
*/
int graph_add_edge(graph_t *graph, const char *src,
					const char *dest, edge_type_t type)
{
	vertex_t *source = NULL, *destination = NULL;

	if (!graph || !src || !dest)
		return (0);
	source = get_vertex(graph, src);
	destination = get_vertex(graph, dest);
	set_edge(source, destination);
	if (type == BIDIRECTIONAL)
		set_edge(destination, source);
	return (1);
}
