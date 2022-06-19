#ifndef COMPACTA_H
#define COMPACTA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Heap.h"
#include "Hash_antes.h"
#include "Huffman.h"
#include "Hash_depois.h"
/*Cria header pra arquivo comprimido*/
unsigned char* Create_header(int trash_size,int tree_size)
{
	unsigned char *bytes = (unsigned char*) malloc(sizeof(3*sizeof(unsigned char)));
	bytes[0] =  trash_size << 5 | tree_size >> 8;
	bytes[1] =  tree_size;
	return (bytes);
}

/*Define um novo valor para um byte e o coloca no Hash*/
void set(huffmanTree * bt,Comp_HT* ht,int height,unsigned int byte)
{
	if(bt!=NULL)
	{
		if(isLeaf(bt))
		{
			another_put(ht,&byte,height-1,bt->byte);
		}
		set(bt -> left, ht, height+1, byte<<1);
		set(bt -> right, ht, height+1,(byte<<1)+1) ;
	}
}
/*Ele recebe o arquivo a ser compactado, coleta as frequências de cada byte e as coloca em um Hash,
então cria um Heap com os valores das frequências e bytes.
A partir do Heap é formada uma árvore, desta árvore é criado outro Hash, com os novos valores de byte.
Lê o arquivo a ser compactado e cria um arquivo compactado a partir do original e do segundo Hash.*/
void compress(char *name)
{
	hash_table *hash = inicializar_hash();
	unsigned char byte;
	char exit[10000];
	int i;
	short tam = strlen(name);
	FILE *entrada,*saida;
	entrada = fopen(name, "rb");
	getchar();


	strcat(name,".huff"); // escreve como .huff

	saida = fopen(name, "wb");
	fputc(0, saida);
	fputc(0, saida);
	int file_size = 0;
	rewind(entrada);

	while(!feof(entrada)) // Leitura do arquivo e assimilação dos dados em uma hash table - bytes originais
	{
		byte = fgetc(entrada);
		if(!feof(entrada))
		{
			file_size ++;
			Inserir(hash, &byte);
		}
	}

	Heap *heap = inicializar_heap();
	huffmanTree * new_node = NULL;
	/* Nós serão criados a partir da hash table e implementados em uma heap que servirá para organizar
    a fila de prioridade de menores frequências (minheap) */
	for(i = 0;i < 256;i ++)
	{
    	if(hash->table[i]!=NULL)
    	{
    		new_node = createNODE(hash->table[i]->byte,hash->table[i]->frequency);
    		enqueue(heap,new_node);
		}
	}

	huffmanTree * arvore = createHTfromHEAP(heap);

	Comp_HT* nometemp = inicializar_hash_novo();
	printHTinFile(arvore,saida);

	rewind(entrada); // posição no início do arquivo para leitura

	set(arvore, nometemp, 0, 0);
	unsigned char Final_Byte = 0;
	unsigned int bits;
	unsigned char temp;
	short bits_not_shifted = 7;
	short bits_number;

	while(!feof(entrada))   
	{
		byte = fgetc(entrada);
		if(!feof(entrada))
		{
			bits_number = nometemp -> table[byte % MAX_HASH_SIZE] -> number_of_bits;
			bits = *(unsigned int *)nometemp->table[byte% MAX_HASH_SIZE]->byte;
			while(bits_number>=0)
			{
				if(is_bit_i_set(bits,bits_number)) Final_Byte = set_bit(Final_Byte,bits_not_shifted);
				if(bits_not_shifted==0) {
					fputc(Final_Byte,saida);
					Final_Byte =0;
					bits_not_shifted =7;
				}
				else{
				bits_not_shifted--;}
				bits_number--;
			}
		}
	}

	int trash = (bits_not_shifted+1)%8;
	if(trash!=0){
	fputc(Final_Byte,saida);
	}
	printf("%d\n",trash);
	rewind(saida);

	unsigned char *cabecalho;
	int tree_size = 0;
	Tree_size(arvore, &tree_size);
	cabecalho = Create_header(trash, tree_size);
	fputc(cabecalho[0], saida);
	fputc(cabecalho[1], saida);

	fclose(entrada);
	fclose(saida);
}

#endif