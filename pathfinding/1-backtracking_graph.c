#include "pathfinding.h"

static int is_valid_move(char **map, int rows, int cols, point_t *next_move)
{
    int x, y;
    x = next_move->x;
    y = next_move->y;
    if (x < rows && x > 0 && y < cols && y > 0 && map[x][y] == "0")
        return (1);
    else
        return (0);
}


static void solve_maze(char **map, int rows, int cols, point_t *current, point_t *target, queue_t *queue)
{
    point_t *next_move = malloc(sizeof(point_t));
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    if (current->x == target->x && current->y == target->y)
    {
        queue_push_back(queue, (void*)current);
        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        next_move->x = current->x + directions[i][0];
        next_move->y = current->y + directions[i][1];

        if (is_valid_move(map, rows, cols, next_move))
        {
            queue_push_back(queue, (void*)next_move);
            solve_maze_(map, rows, cols, next_move, target, queue);
        }
    }
}


queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target)
{
    queue_t *queue;
    point_t *current = malloc(sizeof(point_t));

    queue = queue_create();
    *current = *start;
    solve_maze(map, rows, cols, current, target, queue);
}