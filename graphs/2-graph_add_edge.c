#include "graphs.h"


static graph_p *initialize_ptrs(graph_p *ptrs, const char *src, const char* dest)
{
    vertex_t *temp;

    temp = ptrs->node;
    while (temp)
    {
        if (strcmp(temp->content, src) == 0)
        {
            ptrs->source = temp;
        }
        if (strcmp(temp->content, dest) == 0)
        {
            ptrs->destination = temp;
        }
        temp = temp->next;
    }
    if (!ptrs->source || !ptrs->destination)
        return (NULL);
    return (ptrs);
}

static int set_edge(graph_p *ptrs, edge_type_t type)
{
    edge_t *edge = malloc(sizeof(edge_t)), *temp;
    edge_t *edge2 = malloc(sizeof(edge_t));
        
    if (!ptrs->source->edges)
    {
        edge->dest = ptrs->destination;
        edge->next = NULL;
        ptrs->source->edges = edge;
        ptrs->source->nb_edges++;
    }
    else
    {
        temp = ptrs->source->edges;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = malloc(sizeof(edge_t));
        temp = temp->next;
        temp->dest = ptrs->destination;
        temp->next = NULL;

        ptrs->source->nb_edges++;
    }

    if (type == BIDIRECTIONAL)
    {
        if (!ptrs->destination->edges)
        {
            edge2->dest = ptrs->source;
            edge2->next = NULL;
            ptrs->destination->edges = edge2;
            ptrs->destination->nb_edges++;
        }
        else
        {
            if (temp && temp != ptrs->destination->edges)
                free(temp);
            temp = ptrs->destination->edges;
            edge2 = temp;
            while (temp->next)
            {   
                edge2 = temp;
                temp = temp->next;
            }
            temp = malloc(sizeof(edge_t));
            temp->dest = ptrs->source;
            temp->next = NULL;
            edge2->next = temp;
            ptrs->destination->edges = edge2;
            ptrs->destination->nb_edges++;
        }
    }
    else {
        free(edge2);
        edge2 = NULL;
    }
    free(edge);
    return (1);
}

int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
    graph_p *ptrs = NULL;

    if (!graph || !src || !dest)
        return (0);
    
    ptrs = malloc(sizeof(graph_p));
    ptrs->node = graph->vertices; 
    if (!initialize_ptrs(ptrs, src, dest))
        return (0);
    if (!set_edge(ptrs, type))
        {
            free(ptrs);
            return (0);
        }
    free(ptrs);
    return (1);

}