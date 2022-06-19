#ifndef HASH_DEPOIS_H
#define HASH_DEPOIS_H
#include <stdio.h>
#include <stdlib.h>
#include "Hash_antes.h"


typedef struct comp_hash_table Comp_HT;

typedef struct comp_element
{
	void * byte;
	int number_of_bits;
}Comp_element;

struct comp_hash_table
{
	Comp_element* table[MAX_HASH_SIZE];
};

/*Inicializa hash table para ser usada com novos valores de bytes*/
Comp_HT* inicializar_hash_novo()
{
	int i;
	Comp_HT* new_ht = (Comp_HT*)malloc(sizeof(Comp_HT));
	for(i = 0;i < MAX_HASH_SIZE;i ++)
	{
		new_ht -> table[i] = NULL;
	}
	return new_ht;
}

/*Põe o novo valor na hash*/
void another_put(Comp_HT *ht,void *byte ,int number,void *chave)
{
	int key = (*(unsigned char*)chave) % MAX_HASH_SIZE;
	ht -> table[key] = (Comp_element *)malloc(sizeof(Comp_element));
	ht -> table[key] -> byte = malloc(sizeof(unsigned int));
	*(unsigned int *)ht->table[key]->byte = *(unsigned int *)byte;
	ht -> table[key] -> number_of_bits = number;
}

#endif