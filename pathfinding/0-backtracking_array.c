#include "pathfinding.h"

/**
 * was_visited - checks if a cell has been visited
 * @visited: the visited array
 * @cols: number of cols
 * @x: the x coordinate
 * @y: the y coordinate
 * Return: 1 if has been visited, else 0
*/
static int was_visited(int *visited, int cols, int x, int y)
{
	return (visited[(y * cols) + x]);
}
/**
 * point_dup - allcoate a point struct onto the heap
 * @point: the point to be copied
 * Return: the copied point
*/
static point_t *point_dup(point_t *point)
{
	point_t *copy = malloc(sizeof(point_t));

	copy->x = point->x;
	copy->y = point->y;
	return (copy);
}
/**
 * is_valid_move - checks if the next move is valid
 * @map: the map being navigated
 * @rows: number of rows
 * @cols: number of cols
 * @next_move: coordinates of the next attempted move
 * Return: 1 if valid move, else 0
*/
static int is_valid_move(char **map, int rows, int cols, point_t *next_move)
{
	int x, y;

	x = next_move->x;
	y = next_move->y;
	if (x < rows && x >= 0 && y < cols && y >= 0 && map[y][x] == '0')
		return (1);
	else
		return (0);
}

/**
 * solve_maze - solves a maze using backtracking
 * @map: the map to navigate
 * @rows: number of rows
 * @cols: number of cols
 * @current: coordinates of the current position
 * @target: coordinates of the target position
 * @queue: the queue that holds the final path
 * @visited: array to keep track of visited cells
 * Return: 1 if found path, else 0
*/
static int solve_maze(char **map, int rows, int cols, point_t *current,
							 point_t *target, queue_t *queue, int *visited)
{
	point_t next_move, *next_move_dup;

	int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, x, y;
	int on_target_path = 0, i;

	printf("Checking coordinates [%d, %d]\n", current->x, current->y);
	visited[(current->y * cols) + current->x] = 1;
	if (current->x == target->x && current->y == target->y)
	{
		next_move_dup = point_dup(current);
		queue_push_front(queue, (void *)next_move_dup);
		return (1);
	}
	for (i = 0; i < 4; ++i)
	{
		next_move.x = current->x + directions[i][0];
		x = next_move.x;
		next_move.y = current->y + directions[i][1];
		y = next_move.y;

		if (is_valid_move(map, rows, cols, &next_move) && !was_visited(visited,
																	 cols, x, y))
		{
			on_target_path += solve_maze(map, rows, cols, &next_move,
												 target, queue, visited);
		}
		if (on_target_path)
			break;
	}
	if (on_target_path)
	{
		queue_push_front(queue, (void *)point_dup(current));
		return (1);
	}
	return (0);
}
/**
 * backtracking_array - finds a path using backtracking
 * @map: the map to navigate
 * @rows: number of rows
 * @cols: number of cols
 * @start: the starting coordinates
 * @target: the target coordinates
 * Return: queue with the path to target
*/
queue_t *backtracking_array(char **map, int rows, int cols,
					 point_t const *start, point_t const *target)
{
	queue_t *queue;
	point_t *current = malloc(sizeof(point_t));
	point_t *finish = malloc(sizeof(point_t));
	int *visited = calloc(sizeof(int), (rows * cols));

	queue = queue_create();
	*current = *start;
	*finish = *target;
	solve_maze(map, rows, cols, current, finish, queue, visited);
	if (!queue->front)
	{
		free(queue);
		queue = NULL;
	}
	free(visited);
	free(current);
	free(finish);
	return (queue);
}
