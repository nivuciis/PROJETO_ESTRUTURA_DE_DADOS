#ifndef HUFFMAN_H_
#define HUFFMAN_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct _HUFFMANTREE huffmanTree;

struct _HUFFMANTREE
{
	void *byte;
	long long int frequency;
	int size;
	huffmanTree *left;
	huffmanTree *right;
};

/*Checa se é folha*/
bool isLeaf(huffmanTree *ht)
{
	return (ht -> left == NULL && ht -> right == NULL);
}
/*Cria no, recebe byte e frequência de byte e retorna no --- Esse nó será elaborado a partir do conteúdo
da hash table e implementado em uma heap para então ser contruída a àrvore de Huffman -- usado na função compress*/
huffmanTree* createNODE(void *byte, long long int frequency)
{
	huffmanTree *aux = (huffmanTree*) malloc(sizeof(huffmanTree));
	aux->byte = malloc(sizeof(unsigned char));
    *(unsigned char * )aux -> byte = *(unsigned char *) byte;
	aux -> frequency = frequency;
	aux -> left= NULL;
	aux -> right= NULL;
	return(aux);
}

/*percorre àrvore e informa tamanho*/
void Tree_size(huffmanTree *ht,int *size)
{
	if(ht!=NULL)
	{
		(*size) ++;
		if(isLeaf(ht)&&(*(unsigned char *)ht->byte=='*')||*(unsigned char *)ht->byte=='\\') (*size)++;
		Tree_size(ht -> left, size);
		Tree_size(ht -> right, size);
	}
}

/*Cria uma árvore com as frequências, os bytes e os filhos*/
huffmanTree* createTREE(void * byte, long long int frequency, huffmanTree *left, huffmanTree *right)
{
	huffmanTree *aux = (huffmanTree*) malloc(sizeof(huffmanTree));
	aux -> byte = malloc(sizeof(unsigned char));
	*(unsigned char*)aux -> byte = *(unsigned char*)byte;
	aux -> frequency = frequency;
	aux -> left = left;
	aux -> right = right;
	return(aux);
}

/*Checa se àrvore está vazia*/
bool isHTempty(huffmanTree *ht)
{
	return (ht == NULL);
}

/*Vá a esquerda e retorna filho esquerdo*/
huffmanTree* go_left(huffmanTree *ht)
{
	if (isHTempty(ht)) return NULL;
	
	return ht -> left;
}

/*Vá a direita e retorna filho direito*/
huffmanTree* go_right(huffmanTree *ht)
{
	if (isHTempty(ht)) return NULL;
	
	return ht -> right;
}

/*Retorna bytes nodes*/
void* getBYTE(huffmanTree *ht)
{
	if (isHTempty(ht)) return NULL;
	return ht -> byte;
}

/*Imprime àrvore no arquivo*/
void printHTinFile (huffmanTree *ht,FILE *newfile)
{
	if (!isHTempty(ht))
	{	if(isLeaf(ht)&&(*(unsigned char *)ht->byte=='*'||*(unsigned char *)ht->byte=='\\'))fputc('\\',newfile);
		fputc(*(unsigned char*)getBYTE(ht),newfile);
		printHTinFile(ht -> left, newfile);
		printHTinFile(ht -> right, newfile);
	}
}
/*Verifica se o bit está definido em uma determinada posição e retorna o resultado*/
int is_bit_i_set(unsigned int c, int i)
{
	unsigned int mask = 1 << i;

	return mask & c;
}

/*Coloca um bit em uma determinada posição de um byte*/
unsigned short set_bit(unsigned short c, int i)
{
	unsigned short mask = 1 << i;

	return c | mask;
}

#endif