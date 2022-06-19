#ifndef Heap_H
#define Heap_H
#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"

#define MAX_HEAP_SIZE 257

typedef struct Heap Heap;

struct Heap
{
	huffmanTree *data[MAX_HEAP_SIZE];
	long long int size;
};

/*Checa se Heap está vazio*/
int vazia_heap(Heap *heap)
{
	return (heap -> size == 0);
}

/*índice pai*/
int parent(Heap *heap, int i)
{
	return i/2;
}

/*índice filho esquerdo*/
int left(Heap *heap, int i)
{
	return 2*i;
}

/*índice filho direito*/
int right(Heap *heap, int i)
{
	return 2*i + 1;
}

/*Inicializa heap*/
Heap* inicializar_heap ()
{
	int i; 
	Heap * hp = (Heap *) malloc(sizeof(Heap ));
	for(i = 0;i < MAX_HEAP_SIZE;i ++) hp -> data[i] = NULL;
	hp -> size = 0;
	return hp;
}

/*Swap dois nós*/
void swap(huffmanTree **a, huffmanTree **b)
{
	huffmanTree  *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

/*Enqueue nó na Heap*/
void enqueue(Heap *heap, huffmanTree *ht)
{
	if (heap -> size >= MAX_HEAP_SIZE)
	{
		printf("Heap Overflow\n");
	}else
	{
		heap -> data[++heap -> size] = ht;
		int key_index = heap -> size;
		int parent_index = parent(heap, heap -> size);

		while (parent_index >= 1 && (heap -> data[key_index] -> frequency) < (heap -> data[parent_index] -> frequency))
		{
			swap(&heap -> data[key_index], &heap -> data[parent_index]);
			key_index = parent_index;
			parent_index =  parent(heap, key_index);
		}
	}
}

/*Mantém a propriedade de min heap, onde todos os pais devem ser menores que os filhos.
A minheap é o meio a partir da qual a fila de prioridade será organizada*/
void min_heapify(Heap *heap, int i)
{
	int lowest;
	int left_index = left(heap, i);
	int right_index = right(heap, i);

	if (left_index <= heap -> size && heap -> data[left_index] -> frequency < heap -> data[i] -> frequency)
	{
		lowest = left_index;
	}else
	{
		lowest = i;
	}

	if (right_index <= (heap -> size) && (heap -> data[right_index] -> frequency) < (heap -> data[lowest] -> frequency))
	{
		lowest = right_index;
	}

	if (i != lowest)
	{
		swap(&(heap -> data[i]), &(heap -> data[lowest]));
		min_heapify(heap, lowest);
	}
}

/*Deleta heap node*/
void* dequeue(Heap *heap)
{
	if (vazia_heap(heap))
	{
		printf("Heap Underflow\n");
		return NULL;
	}else
	{
		huffmanTree *item = heap -> data[1];

		heap -> data[1] = heap -> data[(heap -> size)];
		(heap -> size) --;
		min_heapify(heap, 1);

		return item;
	}
}

/*Cria àrvore com Heap -- Nó pai com frequência igual a soma das frequências de dois nós retirados da heap
que, sendo implementada em minheap, por definição serão os de menor frequência*/
huffmanTree* createHTfromHEAP(Heap *heap)
{
	huffmanTree *a,*b,*aux;
	while(heap -> size > 1) 
	{
		a = dequeue(heap);
		b = dequeue(heap);
		unsigned char x = '*';
		aux = createTREE(&x, a -> frequency + b -> frequency, a, b);
		enqueue(heap,aux);
	}
	return dequeue(heap);
}

#endif