#ifndef _PATHFINDING_
#define _PATHFINDING_

#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"
#include "queues.h"
#include <string.h>
#include <stdbool.h>

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

/**
 * struct params_s - stores the start and target paramters
 * @start: the starting vertex
 * @target: the target vertex
*/
typedef struct params_s
{
	vertex_t *start;
	vertex_t *target;
} params_t;

typedef struct
{
    char name[100];
    int distance;
	bool visited;
    UT_hash_handle hh;
} city;

#define MAX_QUEUE_SIZE 64

typedef struct {
    vertex_t *vertex;
    int distance;
} pq_element;

typedef struct {
    pq_element elements[MAX_QUEUE_SIZE];
    int size;
} min_pq;

queue_t *backtracking_array(char **map, int rows, int cols,
					 point_t const *start, point_t const *target);
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
											 vertex_t const *target);
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
											 vertex_t const *target);

#endif
