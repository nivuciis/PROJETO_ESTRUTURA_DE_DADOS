import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
def bubble_sort(lista):
    elementos = len(lista)-1
    ordenado = False
    while not ordenado:
        ordenado = True
        for i in range(elementos):
            if lista[i] > lista[i+1]:
                lista[i], lista[i+1] = lista[i+1],lista[i]
                ordenado = False        
    return lista
'''Processamento dos dados para lista encadeada'''
fil = open("arq_lista.txt")
lines = fil.readlines()
list_numbers = []
for k in lines:
    list_numbers.append(int(k))
fil.close()
#lista da contagem da inserção
list_insertion = []
for k in range(0,300,3):
    list_insertion.append(list_numbers[k])
#print(list_insertion)
#lista da contagem da busca
list_search = []
for k in range(1,300,3):
    list_search.append(list_numbers[k])
list_search = bubble_sort(list_search)
#print(list_search)
#lista da contagem da remoção
list_remotion = []
for k in range(2,300,3):
    list_remotion.append(list_numbers[k])
list_remotion = bubble_sort(list_remotion)
#print(list_remotion)
'''Processamento dos dados para árvore binária'''
fil_bt = open("arq_arvore.txt")
lin_bt = fil_bt.readlines()
list_numbers_bt = []
for k in lin_bt:
    list_numbers_bt.append(int(k))
fil_bt.close()
#lista da contagem da inserção
list_insertion_bt = []
for k in range(0,300,3):
    list_insertion_bt.append(list_numbers_bt[k])
list_insertion_bt = bubble_sort(list_insertion_bt)
#lista da contagem da busca
list_search_bt = []
for k in range(1,300,3):
    list_search_bt.append(list_numbers_bt[k])
list_search_bt = bubble_sort(list_search_bt)
#lista da contagem da remoção
list_remotion_bt = []
for k in range(2,300,3):
    list_remotion_bt.append(list_numbers_bt[k])
list_remotion_bt = bubble_sort(list_remotion_bt)
'''Plotagem do gráfico '''
#Listas vs Árvores
#Inserção
plt.plot(list_insertion, marker=".", color="blue")
plt.plot(list_insertion_bt, marker="*", color="red")
plt.title('Inserção')
plt.ylabel("Quantidade de iterações")
plt.xlabel("Quantidade de dados")
plt.legend(["Lista", "Árvore"], bbox_to_anchor=(0.6,0.9))
plt.show()
#Remoção
plt.plot(list_remotion, marker=".",color="blue")
plt.plot(list_remotion_bt, marker="*", color="red")
plt.title('Remoção')
plt.ylabel("Quantidade de iterações")
plt.xlabel("Quantidade de dados")
plt.legend(["Lista", "Árvore"], bbox_to_anchor=(0.6,0.9))
plt.show()
#Busca
plt.plot(list_search, marker=".", color="blue")
plt.plot(list_search_bt, marker="*", color="red")
plt.title('Busca')
plt.ylabel("Quantidade de iterações")
plt.xlabel("Quantidade de dados")
plt.legend(["Lista", "Árvore"], bbox_to_anchor=(0.6,0.9))
plt.show()
