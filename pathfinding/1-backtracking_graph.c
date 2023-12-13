#include "pathfinding.h"

/**
 * been_there - checks if we been there yet or not
 * @destination: the location to check
 * visited_graph: graph containing all the visited locations
 * Return: 1 if we been there, else 0
*/
static int been_there(vertex_t *destination, graph_t *visitid_graph)
{
	size_t i;
	vertex_t *vertex;

	vertex = visitid_graph->vertices;
	for (i = 0; i < visitid_graph->nb_vertices; i++)
	{
		if (strcmp(destination->content, vertex->content) == 0)
			return (1);
		vertex = vertex->next;
	}
	return (0);
	
}

/**
 * find_route - finds a path from start to target using backtracking
 * @graph: the graph containing vertexes
 * @params: the start and target vertex
 * @q: the queue containing the path to target
 * @current_node:the node currently being checked
 * @visited: a graph containing all the visited nodes
 * Return: 1 if on path, else 0
*/
static int find_route(graph_t *graph, params_t *params, queue_t *q, vertex_t *current_node, graph_t *visited)
{
	edge_t *edge;

	printf("Checking %s\n", current_node->content);
	graph_add_vertex(visited, current_node->content, current_node->x, current_node->y);
	if (strcmp(params->target->content, current_node->content) == 0)
	{
		queue_push_front(q, (void *)current_node->content);
		return (1);
	}

	edge = current_node->edges;
	while (edge)
	{
		if (!been_there(edge->dest, visited))
		{
			if (find_route(graph, params, q, edge->dest, visited))
			{
				queue_push_front(q, (void *)edge->dest->content);
				return (1);
			}
		}
		edge = edge->next;
	}
	return (0);
}
/**
 * backtracking_graph - wrapper function
 * @graph: the graph to traverse
 * @start: the starting vertex
 * @target: the target vertex
 * Return: a queue containing the path found
*/
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
	queue_t *q;
	graph_t *visited_graph;
	params_t *params = malloc(sizeof(params_t));

	params->start = malloc(sizeof(vertex_t));
	params->target = malloc(sizeof(vertex_t));

	visited_graph = graph_create();
	q = queue_create();
	*params->start = *start;
	*params->target = *target;
	find_route(graph, params, q, params->start, visited_graph);
	free(params->start);
	free(params->target);
	free(params);
	graph_delete(visited_graph);
	return(q);
}
