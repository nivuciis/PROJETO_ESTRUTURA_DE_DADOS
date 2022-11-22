#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 

double counter = 0.0;
typedef struct heap {
    int size;
    int data[10000];
}heap;
heap *inicializar_heap ()
{
	int i; 
	heap *hp = (heap*) malloc(sizeof(heap));
	for(i = 0;i < 10000;i ++) hp -> data[i] = NULL;
	hp -> size = 0;
	return hp;
}
int get_parent_index(heap *heap, int i)
{
    counter += (double)(0.1);
    return i/2;
}
int get_left_index(heap *heap, int i)
{
    counter += (double)(0.1);
    return 2*i;
}
int get_right_index(heap *heap, int i)
{
    counter += (double)(0.1);
    return 2*i + 1;
}
int item_of(heap *heap, int i)
{
    counter += (double)(0.1);
    return heap->data[i];
}
bool is_empty(heap *h)
{
    counter += (double)(0.1);
    return (h->size == 0);
}
void swap(int *a, int *b)
{
    counter += (double)(0.1);
	int  *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}
void max_heapify(heap *heap, int i)
{
    int largest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);
    if (left_index <= heap->size && heap->data[left_index] > heap->data[i]) largest = left_index;
    else largest = i;
    if (right_index <= heap->size && heap->data[right_index] > heap->data[largest]) largest = right_index;
    counter += (double)(0.1);
    if (heap->data[i] != heap->data[largest]) 
    {
        swap(&heap->data[i], &heap->data[largest]);
        counter += (double)(0.1);
        max_heapify(heap, largest);
    }
}
void enqueue(heap *heap, int item)
{
    if (heap->size >= 10000)
    {
        printf("Heap overflow");
        counter += (double)(1.0);
    }
    else
    {
        heap->data[++heap->size] = item;
        int key_index = heap->size;
        int parent_index = get_parent_index(heap, heap->size);
        counter += (double)(1.0);
        while (parent_index >= 1 && heap->data[key_index] > heap->data[parent_index])
        {
            swap(&heap->data[key_index], &heap->data[parent_index]);
            key_index = parent_index;
            counter += (double)(1.0);
            parent_index = get_parent_index(heap, key_index);
        }
    }
}
void dequeue(heap *heap)
{
    if (is_empty(heap)) 
    {
        printf("Heap underflow");
        return;
        counter += (double)(0.1);
    } 
    else 
    {
        int item = heap->data[1];
        heap->data[1] = heap->data[heap->size];
        heap->size--;
        counter += (double)(0.1);
        max_heapify(heap, 1);
        return;
    }
}
// fila de prioridade sem heap:
typedef struct node {
    int item;
    int priority;
    struct node *next;
}node;
typedef struct priority_queue {
    node *head;
}priority_queue;
bool is_empty_queue(priority_queue *pq)
{
    return (pq->head == NULL);
}
priority_queue *create_q()
{
    priority_queue *newpq = (priority_queue*) malloc(sizeof(priority_queue));
    newpq->head = NULL;
    return newpq;
}
void enqueue_pq(priority_queue *pq, int i, int p)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = i;
    new_node->priority = p;
    if ((is_empty_queue(pq)) || (p > pq->head->priority))
    {
        new_node->next = pq->head;
        pq->head = new_node;
        counter += (double)(0.01);
    } 
    else 
    {
        counter += (double)(0.01);
        node *current = pq->head;
        while ((current->next != NULL) && (current->next->priority > p))
        {
            counter += (double)(0.01);
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
void dequeue_pq(priority_queue *pq)
{
    if (is_empty_queue(pq))
    {
        counter += (double)(0.1);
        printf("Priority Queue underflow");
        return;
    } 
    else 
    {
        counter += (double)(0.1);
        node *node = pq->head;
        pq->head = pq->head->next;
        node->next = NULL;
        return;
    }
}

//
int main()
{
    heap *hp = inicializar_heap();
    //Contagem da fila de prioridade com heap
    FILE *comp;
    comp = fopen("arq_heap.txt", "a");
    // Contagem para a empilhar big(O) = 1;
    for(int i=0;i < 10000; i++)
    {
        counter = 0.0;
        enqueue(hp, i);
        fprintf(comp, "%f\n", counter);
    } 
    //Contagem para desempilhar
    
    for(int i=0;i < 10000; i++)
    {
        counter = 0.0;
        dequeue(hp);
        fprintf(comp, "%f\n", counter);
    }
    fclose(comp);
     
    //Contagem de fila de prioridade sem heap
    FILE *pqcomp;
    priority_queue *head = create_q();
    pqcomp = fopen("arq_pq.txt", "a");
    //Contagem para empilhar 
    for(int i=0;i < 10000; i++)
    {
        counter = 0.0;
        enqueue_pq(head, i, rand()%20);
        fprintf(pqcomp,"%f\n", counter);
        //printf("%d\n", head->head->item);
    }
    //Contagem para desempilhar
    for(int i=0;i < 10000; i++)
    {
        counter = 0.0;
        dequeue_pq(head);
        fprintf(pqcomp,"%f\n", counter);
    }
    fclose(pqcomp);
    
    return 0;
}