#ifndef Descompacta_AHRT
#define Descompacta_AHRT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Huffman.h"
#include "Compacta.h"


/*Retorna o tamanho do lixo em um arquivo*/
int Trash_Size(FILE *file_a)
{
    rewind(file_a);
    int trash_size = fgetc(file_a) >> 5;

    return trash_size;
}
/*Retorna o tamanho da Árvore em um arquivo*/
int Tree_Size(FILE *file_a)
{
    rewind(file_a);
    unsigned short first_byte = fgetc(file_a) << 11;
    first_byte = first_byte>>3;
    unsigned short second_byte = fgetc(file_a);
    first_byte |= second_byte;

    return first_byte;
}

/*Cria a àrvore com o arquivo*/
huffmanTree *Huffman_Tree(FILE *file_a, unsigned char key)
{
    huffmanTree *new_tree_node = createNODE(&key, 0);
    if(key == '\\')
    {
        *(unsigned char*)new_tree_node -> byte = fgetc(file_a);
    }
    if(key == '*')
    {
        new_tree_node -> left = Huffman_Tree(file_a, fgetc(file_a));
        new_tree_node -> right = Huffman_Tree(file_a, fgetc(file_a));
    }

    return new_tree_node;
}

/*Processo de receber a àrvore de Huffman*/
huffmanTree *Extract(FILE *file_a)
{           
    huffmanTree *huff_tree = NULL;
    huff_tree = Huffman_Tree(file_a, fgetc(file_a));

    return huff_tree;
}

/*Tamanho do arquivo depois da àrvore*/
long long unsigned Get_FILE_size(FILE * file)
{
    long long unsigned i;
    for(i = 0; !feof(file); i ++) fgetc(file);
        return i - 1;
}

/*Ele recebe um arquivo compactado e enquanto não chega ao final,
ele procura na árvore seguindo o caminho dado pelo arquivo.
Quando encontra uma folha, coloca seu byte no arquivo descompactado.*/
void Decompress(FILE * enter,FILE * exit,huffmanTree *Tree,int trash,long long unsigned size)
{
    unsigned char byte;
    int actual;
    huffmanTree * H_A = Tree;
    long long unsigned i = 0;

    while(i < size)
    {
        byte = fgetc(enter);
        actual = 7;
        if(i < size - 1)
        {
            while(actual >= 0)
            {
                if(isLeaf(H_A))
                {
                    fputc(*(unsigned char*)getBYTE(H_A), exit);
                    H_A = Tree;
                }
                if(is_bit_i_set(byte,actual)) H_A = go_right(H_A);
                else H_A = go_left(H_A);
                actual --;
            }
        }else
        {
            while(actual >= trash)
            {
                if(isLeaf(H_A))
                {
                    fputc(*(unsigned char*)getBYTE(H_A), exit);
                    H_A = Tree;
                }
                if(is_bit_i_set(byte,actual)) H_A = go_right(H_A);
                else H_A = go_left(H_A);
                actual --;
            }
            if(isLeaf(H_A)) fputc(*(unsigned char *)getBYTE(H_A), exit);
        }
        i ++;
    }
}
void printHT(huffmanTree *ht)
{
    if(ht!=NULL)
    {
        printf("%c",*(unsigned char*)ht->byte);
        printHT(ht->left);
        printHT(ht->right);
    }
}
/*Inicia a descompactação de arquivos criando um novo arquivo de saída que será o arquivo descompactado*/
void Decompress_File(char * nome)
{
 
    FILE *file_a = fopen(nome,"rb");
    getchar();


    char exit[1000];
    long long unsigned i,tam = strlen(nome) - 6;
    for(i = 0;i <= tam;i ++) exit[i] = nome[i];
        exit[i] = '\0';

    FILE *file_e = fopen(exit,"wb");
    if(file_a != NULL)
    {
        int trash_size = Trash_Size(file_a);
        int tree_size = Tree_Size(file_a);
        huffmanTree *huff_tree = Extract(file_a);
        long long unsigned size= Get_FILE_size(file_a);
        tree_size = Tree_Size(file_a);
        Extract(file_a);
        Decompress(file_a,file_e,huff_tree,trash_size,size);
    }
    return;    
}

#endif