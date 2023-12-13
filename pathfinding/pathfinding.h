#ifndef _PATHFINDING_
#define _PATHFINDING_

#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"
#include "queues.h"
#include <string.h>

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

typedef struct params_s
{
	vertex_t *start;
	vertex_t *target;
} params_t;

queue_t *backtracking_array(char **map, int rows, int cols,
					 point_t const *start, point_t const *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
											 vertex_t const *target);

#endif
