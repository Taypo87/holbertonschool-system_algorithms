#include "graphs.h"


static vertex_t *get_vertex(graph_t  *graph, const char * str)
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

static void set_edge(vertex_t *src, vertex_t *dest)
{

    edge_t *new = malloc(sizeof(edge_t));
    if (!src->edges)
        src->edges = new;
    else
    {
        while (src->edges)
        {
            src->edges = src->edges->next;
        }
        src->edges = new;
    }
    new->dest = dest;
    new->next = NULL;

}


int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
    vertex_t *source, *destination;

    if (!graph)
        return (0);

    source = get_vertex(graph, src);
    destination = get_vertex(graph, dest);
    if (!source || !destination)
        return (0);
    set_edge(source, destination);
    if (type == BIDIRECTIONAL)
        set_edge(destination, source);
    return (1);
}
