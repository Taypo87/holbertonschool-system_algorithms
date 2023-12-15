#include "pathfinding.h"
#include <limits.h>
#include "uthash.h"


static void add_city(char *name, int distance, city *cities)
{
    city *s = malloc(sizeof(city));
    strcpy(s->name, name);
    s->distance = distance;
    s->visited = false;
    HASH_ADD_STR(cities, name, s);
}

static city *find_city(char *name, city *cities) 
{
    city *s;
    HASH_FIND_STR(cities, name, s);
    return s;
}
void bubbleUp(min_pq *pq, int index)
{
    while (index > 0 && pq->elements[index].distance < pq->elements[(index - 1) / 2].distance) {
        // Swap with parent
        pq_element temp = pq->elements[index];
        pq->elements[index] = pq->elements[(index - 1) / 2];
        pq->elements[(index - 1) / 2] = temp;

        index = (index - 1) / 2;
    }
}
void insert(min_pq *pq, vertex_t vertex, int distance) {
    if (pq->size == MAX_QUEUE_SIZE) {
        // Handle queue overflow
        return;
    }

    pq->elements[pq->size].vertex = vertex;
    pq->elements[pq->size].distance = distance;
    bubbleUp(pq, pq->size);
    pq->size++;
}
void bubbleDown(min_pq *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->elements[left].distance < pq->elements[smallest].distance)
        smallest = left;

    if (right < pq->size && pq->elements[right].distance < pq->elements[smallest].distance)
        smallest = right;

    if (smallest != index) {
        // Swap with the smallest child
        pq_element temp = pq->elements[index];
        pq->elements[index] = pq->elements[smallest];
        pq->elements[smallest] = temp;

        bubbleDown(pq, smallest);
    }
}

pq_element extractMin(min_pq *pq) {
    if (pq->size == 0) {
        // Handle empty queue
        return (pq_element){-1, -1};
    }

    pq_element result = pq->elements[0];
    pq->elements[0] = pq->elements[pq->size - 1];
    pq->size--;
    bubbleDown(pq, 0);

    return result;
}





queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
    city *cities = NULL, *starting_city;
    min_pq pq;
    vertex_t *temp1, *temp2;
    int i;
    pq_element element;
    edge_t *edge;

    pq.size = 0;
    temp1 = graph->vertices;
    for (i = 0; i < graph->nb_vertices; i++)
    {
        add_city(temp1->content, INT_MAX, cities);
        temp1 = temp1->next;
    }
    starting_city = find_city(start->content, cities);
    starting_city->distance = 0;
    starting_city->visited = true;
    insert(&pq, *start, 0);

    while (pq.size > 0)
    {
        element = extractMin(&pq);
        temp1 = element.vertex;
        edge = temp1->edges;
        while (edge)
        {
            temp2 = edge->dest;
        }
    }
    

}