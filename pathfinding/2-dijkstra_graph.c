#include "pathfinding.h"
#include <limits.h>


static void add_city(char *name, vertex_t *vertex, int distance, city *cities)
{
    city *s = malloc(sizeof(city));
    strcpy(s->name, name);
    s->node = vertex;
    s->distance = distance;
    s->in_queue = false;
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
void insert(min_pq *pq, vertex_t *vertex, int distance) {
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
    if (pq->size == 0) 
    {
        
        // Handle empty queue
        return (pq_element){NULL, -1};
    }

    pq_element result = pq->elements[0];
    pq->elements[0] = pq->elements[pq->size - 1];
    pq->size--;
    bubbleDown(pq, 0);

    return result;
}






static bool dextr(city *cities, min_pq *pq, vertex_t *start, vertex_t *dest)
{   
    city *current_city, *destination_city;
    pq_element element;
    vertex_t *temp1, *temp2;
    edge_t *edge;

    current_city = find_city(start->content, cities);
    current_city->distance = 0;
    current_city->in_queue = true;
    insert(pq, *start, 0);

    while (pq->size > 0)
    {
        
        element = extractMin(pq);
        temp1 = element.vertex;
        if (element.vertex == dest)
            return (true);
        edge = temp1->edges;
        for (;edge; edge = edge->next)
        {
            temp2 = edge->dest;
            destination_city = find_city(temp2->content, cities);

            if (destination_city->in_queue == true)
                continue;
            if ((edge->weight + current_city->distance) < destination_city->distance)
            {
                destination_city->distance = edge->weight + current_city->distance;
                destination_city->previous = current_city;
                if (destination_city->in_queue == false)
                {
                    insert(pq, *destination_city->node, destination_city->distance);
                    destination_city->in_queue = true;
                }
            }
        }
        return (false);
        
    }
}

static queue_t *create_path(city *cities, vertex_t * target, vertex_t *start, queue_t *queue)
{
    city *temp;

    temp = find_city(target->content, cities);

    while (true)
    {
        if (temp->node == start)
            break;
        queue_push_front(queue, strdup(temp->name));
        temp = temp->previous;
    }
    return (queue);
}


queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start, vertex_t const *target)
{
    city *cities = NULL;
    vertex_t *start_copy = malloc(sizeof(vertex_t));
    vertex_t *target_copy = malloc(sizeof(vertex_t));
    min_pq pq;
    vertex_t *temp1;
    int i;
    queue_t *queue = malloc(sizeof(queue_t));

    *start_copy = *start;
    *target_copy = *target;
    pq.size = 0;
    temp1 = graph->vertices;
    for (i = 0; i < graph->nb_vertices; i++)
    {
        add_city(temp1->content, temp1, INT_MAX, cities);
        temp1 = temp1->next;
    }
    
    if (dextr(cities, &pq, start_copy, target_copy))
        queue =  create_path(cities, target_copy, start_copy, queue);
    else
    {
        free(queue);
        queue = NULL;
    }
    return(queue);

}
