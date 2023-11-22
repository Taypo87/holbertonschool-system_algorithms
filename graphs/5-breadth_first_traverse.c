#include "graphs.h"

static void push(queue_t **head, queue_t **tail, vertex_t *vertex, int *visited)
{
    queue_t *new = malloc((sizeof(queue_t))), *temp;

    new->vertice = vertex;
    new->next = NULL;
    new->prev = NULL;
    visited[vertex->index] = 1;
    if (!*tail && !*head)
    {
        tail = &new;
        head = &new;
    }
    else
    {
     temp = *head;
     new->next = temp;
     temp->prev = new;
     head = &new;   
    } 
    if (!(*tail))
        puts("push error");
}

static void pop(queue_t **tail)
{
    queue_t *temp = NULL;
    if(!tail || !*tail)
        puts("no tail node, error");
    temp = *tail;
    if ((*tail)->prev)
        *tail = (*tail)->prev;
    else
    {
        *tail = NULL;
    }
    free(temp);
}

static size_t add_edges(edge_t *edges, queue_t **head, queue_t **tail, int *visited)
{

    vertex_t *vertex = edges->dest;
    size_t depth_counter = 0;

    while (vertex && !visited[vertex->index])
    {
        push(head, tail, vertex, visited);
        (*head)->depth = depth_counter;
        vertex = edges->next->dest;
        edges = edges->next;
        depth_counter++;
    }
    return (depth_counter);
}

static int all_visited(int *visited, size_t nb_vertices)
{
    size_t i = 0;

    while (i < nb_vertices)
    {
        if (!visited[i])
            return (0);
        i++;
    }
    return (1);
}

size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
    queue_t *q_head = NULL, *q_tail = NULL;
    size_t depth_counter = 0, depth_compare = 0;
    vertex_t *temp;
    int *visited = calloc(graph->nb_vertices, sizeof(int));

    push(&q_head, &q_tail, graph->vertices, visited);
    action(graph->vertices, depth_counter);
    pop(&q_tail);
    add_edges(graph->vertices->edges, &q_head, &q_tail, visited);
    action((q_tail)->vertice, (q_tail)->depth);
    temp = graph->vertices;
    while(q_tail)
    {
        if (!all_visited(visited, graph->nb_vertices))
            depth_compare = add_edges(temp->edges->dest->edges, &q_head, &q_tail, visited);
        if (depth_compare > depth_counter)
            depth_counter = depth_compare;
        temp = temp->edges->next->dest;
        action((q_tail)->vertice, (q_tail)->depth);
        pop(&q_tail);

    }
    free(visited);
    return (depth_counter);
}
