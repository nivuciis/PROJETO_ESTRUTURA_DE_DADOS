#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>   
int counter = 1;
typedef struct node
{
    int item;
    struct node *next;
}node;
typedef struct bin_tree
{
    int item;
    struct bin_tree *left;
    struct bin_tree *right;
}bin_tree;
bin_tree *create(int item, bin_tree *left, bin_tree *right)
{
    bin_tree *new_bt = (bin_tree*) malloc(sizeof(bin_tree));
    new_bt->item = item;
    new_bt->left = left;
    new_bt->right = right;
    return new_bt;
}
bin_tree *add_bt(bin_tree *bt, int item)
{
    counter ++;
    if(bt == NULL)
    {
        bt = create(item, NULL, NULL);
    }else if(bt->item > item)
    {
        bt->left = add_bt(bt->left, item);
    }else
    {
        bt->right = add_bt(bt->right, item);
    }
    return bt;
}
bin_tree *search_bt(bin_tree *bt, int item)
{
    counter ++;
    if((bt == NULL) || (bt->item == item)) return bt;
    else if(bt->item > item) return search_bt(bt->left, item);
    else return search_bt(bt->right, item);
}
bin_tree *remove_bt(bin_tree *bt, int item)
{
    counter ++;
    if(bt == NULL) return bt;
    else
    {
        if(bt->item == item)
        {
            if(bt->left == NULL && bt->right == NULL)
            {
                free(bt);
                return NULL;
            }
            else if(bt->left != NULL && bt->right != NULL)
            {
                bin_tree *aux = bt->right;
                while (bt->right != NULL)
                {
                    aux = aux->right;
                    counter ++;
                }
                bt->item = aux->item;
                aux->item = item;
                bt->left = remove_bt(bt->left, item);
                return bt;
            }
            else
            {
                bin_tree *aux;
                if(bt->right != NULL) aux = bt->left;
                else aux = bt->right;
                free(bt);
                return aux;
            }
        }
        else if(item < bt->item) bt->left = remove_bt(bt->left, item);
        else bt->right = remove_bt(bt->right, item);
        return bt;
    }
}
node *add(node *head, int item)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = item;
    new_node->next = head;
    head  = new_node;
    counter ++;
    return head;
}
node *search(node *head, int item)
{
    while(head != NULL)
    {
        if(head->item  == item)
        {
            return head;
        }
        head = head->next;
        counter ++;
    }   
    return NULL;
    //Big O(N)
}
node *remotion(node *head, int item)
{
    counter ++;
    node *previous = NULL;
    node *current = head;
    while(current != NULL && current->item != item)
    {
        counter ++;
        previous = current;
        current = current->next;
    }
    if(current == NULL)
    {        
        return head;
    }
    if(previous == NULL)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    free(current);
    return head;    
}
int main()
{
    //Contagem de lista encadeada
    for(int k = 0; k < 100; k++)
    {
        FILE *comp;
        node *a = NULL;
        comp = fopen("arq_lista.txt", "a");
        // Contagem para a inserção big(O) = 1;
        for(int i=0;i < rand()%10000; i++)
        {
            counter = 0;
            a = add(a, rand()%500);
            //printf("->| %d |<-", rand());
        }
        fprintf(comp,"%d\n", counter);
        counter = 0;
        //Contagem para a busca
        a = search(a, rand()%500);
        fprintf(comp,"%d\n", counter);
        counter = 0;
        //Contagem para a remoção
        a = remotion(a, rand()%500);
        fprintf(comp,"%d\n", counter);
        fclose(comp);
    }
    //Contagem de árvores
    for(int k = 0; k < 100; k++)
    {
        FILE *comp;
        bin_tree *bt = NULL;
        comp = fopen("arq_arvore.txt", "a");
        //Contagem para inserção 
        for(int i=0;i < rand()%10000; i++)
        {
            counter = 0;
            bt = add_bt(bt, rand()%500);
        }
        fprintf(comp,"%d\n", counter);
        counter = 0;
        //Contagem para a busca
        bt = search_bt(bt, rand()%500);
        fprintf(comp,"%d\n", counter);
        counter = 0;
        //Contagem para a remoção
        bt = remove_bt(bt, rand()%500);
        fprintf(comp,"%d\n", counter);
        fclose(comp);
    }
    return 0;
}