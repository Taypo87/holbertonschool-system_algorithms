#include "pathfinding.h"


static int was_visited(unsigned char *visited, int cols, int x, int y)
{
    return (visited[(y * cols) + x]);
}

static point_t *point_dup(point_t *point)
{
    point_t *copy = malloc(sizeof(point_t));
    copy->x = point->x;
    copy->y = point->y;
    return (copy);
}

static int is_valid_move(char **map, int rows, int cols, point_t *next_move)
{
    int x, y;
    x = next_move->x;
    y = next_move->y;
    if (x < rows && x >= 0 && y < cols && y >= 0 && map[x][y] == '0')
        return (1);
    else
        return (0);
}


static int solve_maze(char **map, int rows, int cols, point_t *current, point_t *target, queue_t *queue, unsigned char *visited)
{
    point_t next_move, *next_move_dup;
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}, x, y;
    int on_target_path = 0;
    
    if (current->x == target->x && current->y == target->y)
    {
        next_move_dup = point_dup(current);
        queue_push_front(queue, (void*)next_move_dup);
        return (1);
    }
    visited[(current->y * cols) + current->x] = 1;
    for (int i = 0; i < 4; ++i)
    {
        next_move.x = current->x + directions[i][0];
        x = next_move.x;
        next_move.y = current->y + directions[i][1];
        y = next_move.y;


        if (is_valid_move(map, rows, cols, &next_move) && !was_visited(visited, cols, x, y))
        {
            printf("Checking coordinates [%d, %d]\n", current->x, current->y);
            on_target_path += solve_maze(map, rows, cols, &next_move, target, queue, visited);
        }
    }
    if (on_target_path)
    {
        puts("adding to queue");
        queue_push_front(queue, (void*)point_dup(current));
        return (1);
    }
    return (0);
}


queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target)
{
    queue_t *queue;
    point_t *current = malloc(sizeof(point_t));
    point_t *finish = malloc(sizeof(point_t));
    unsigned char *visited = calloc(sizeof(unsigned char), (rows * cols));

    queue = queue_create();
    *current = *start;
    *finish = *target;
    solve_maze(map, rows, cols, current, finish, queue, visited);
    free(visited);
    return (queue);
}
