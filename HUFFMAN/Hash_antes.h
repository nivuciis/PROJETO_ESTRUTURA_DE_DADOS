#ifndef HASH_ANTES_H
#define HASH_ANTES_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HASH_SIZE 256

// Será definida hash table para guardar bytes (originais) e frequências
typedef struct dados dados;
typedef struct hash_table hash_table;

struct dados
{
	void * byte;
	long long int frequency;
};

 struct hash_table
{
	dados *table[256];
};

//Cria Hash table
hash_table* inicializar_hash()
{
	int i;
	hash_table *novo_hash = (hash_table*) malloc(sizeof(hash_table));
	for(i = 0;i < MAX_HASH_SIZE;i ++)
	{
		novo_hash -> table[i]= NULL;
	}
	return novo_hash;
}

/*Guarda bytes e frequências*/
dados* criar_elemento(void *data, size_t data_size)
{
	dados *novo_elemento = (dados*)malloc(sizeof(dados));
	novo_elemento -> byte = malloc(data_size);
	*(unsigned char*)(novo_elemento->byte) = *(unsigned char*)data; // unsigned char - byte
	novo_elemento -> frequency = 1;
	return novo_elemento;
}

/*Inserção na Hash, levando em consideração as frequências*/
void Inserir(hash_table *ht,void *data)
{
	int key;
	key = (*(unsigned char *)data % MAX_HASH_SIZE);
	if(ht -> table[key] != NULL)
	{
		ht -> table[key] -> frequency ++;
	}else
	{
		ht -> table[key] = criar_elemento(data, sizeof(unsigned char));
	}
}

#endif