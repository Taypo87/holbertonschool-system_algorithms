#include "graphs.h"

/**
 * pop - pops a vertice off the stack
 * @stack: pointer to the top of the stack;
 * @visited: an boolian array to keep track of visted nodes
*/
static void pop(stack_t **stack)
{	
	*stack = (*stack)->next;	
}

/**
 * push - pushes a vertice onto the stack
 * @stack: pointer to the top of the stack
 * @vertex: the vertex to add to the stack
*/
static void push(stack_t **stack, vertex_t *vertex, size_t depth_count, int *visited)
{
	stack_t *new = malloc(sizeof(stack_t));

	new->vertice = vertex;
	new->next = *stack;
	new->depth = depth_count;
	*stack = new;
	visited[vertex->index] = 1;
}

/**
 * visit_edges - visits all the edges and pushes them onto the stack
 * @vertex: pointer to the vertex we will check for edges
 * @stack: pointer too the stack
 * @visited:boolian array to check if the vertex has been visited
 * @depth_counter: counter to keep track of the depth
*/
static size_t visit_edges(vertex_t *vertex, stack_t **stack, int *visited, void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *edge;
	size_t depth_counter = 0, new_depth = 0;

	edge = vertex->edges;

	while (edge && !visited[edge->dest->index])
	{
		if (!visited[edge->dest->index])
		{
			action(edge->dest, depth_counter);
			push(stack, edge->dest, depth_counter, visited);
			new_depth = visit_edges(edge->dest, stack, visited, action);
			if (depth_counter < new_depth)
				depth_counter = new_depth;
		}
		edge = edge->next;
	}
	return (depth_counter + 1);
}

/**
 * cleanup_stack - frees the stack after use
 * @head: pointer to the begining of the popped AND pushed nodes 
 * 		all nodes should be popped before using for proper implementation
*/

/**
 * depth_first_traverse - traverse a graph using depth first algorithm
 * @graph: pointer to the graph to traverse
 * @action: the action performed on the traversed node;
 * Return: the depth
*/
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t branch_depth = 0, check_depth = 0;
	stack_t *stack = NULL, *temp_stack = NULL;;
	vertex_t *temp;

	visited = calloc(graph->nb_vertices, sizeof(int));

	temp = graph->vertices;
	while (temp)
	{
		if (!visited[temp->index])
		{
			push(&stack, temp, branch_depth, visited);
		
			while (stack)
			{
				temp_stack = stack;
				pop(&stack);
				check_depth = visit_edges(temp_stack->vertice, &stack, visited, action);
				free(temp_stack);
				if (check_depth > branch_depth)
					branch_depth = check_depth;

			}
		}
		temp = temp->next;
		}
	free(visited);
	return(branch_depth);
}
