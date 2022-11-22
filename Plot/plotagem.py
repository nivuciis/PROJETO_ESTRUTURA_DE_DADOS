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
'''Processamento dos dados para heap'''
fil = open("arq_heap.txt")
lines = fil.readlines()
list_numbers = []
for k in lines:
    list_numbers.append(float(k))
fil.close()

#lista da contagem empilhar
list_enqueue = []
for k in range(0,10000):
    list_enqueue.append(list_numbers[k])
#list_enqueue = bubble_sort(list_enqueue)
#print(list_enqueue)
#lista da contagem desempilhar
list_dequeue = []
for k in range(10001,20000):
    list_dequeue.append(list_numbers[k])
#print(list_dequeue)
list_dequeue = bubble_sort(list_dequeue)

'''Processamento dos dados para fila de prioridade'''
fil_pq = open("arq_pq.txt")
lin_pq = fil_pq.readlines()
list_numbers_pq = []
for k in lin_pq:
    list_numbers_pq.append(float(k))
fil_pq.close()
#lista da contagem empilhar
list_enqueue_pq = []
for k in range(0,10000):
    list_enqueue_pq.append(list_numbers_pq[k])
list_enqueue_pq = bubble_sort(list_enqueue_pq)
#lista da contagem desempilhar
list_dequeue_pq = []
for k in range(10001,20000):
    list_dequeue_pq.append(list_numbers_pq[k])
list_dequeue_pq = bubble_sort(list_dequeue_pq)

'''Plotagem do gráfico '''
#Heap vs Fila de prioridade
#enqueue
plt.plot(list_enqueue, color="blue")
plt.plot(list_enqueue_pq,color="red")
plt.title('Enqueue')
plt.ylabel("Quantidade de iterações")
plt.xlabel("Quantidade de dados")
plt.legend(["Heap-O(Log(n))", "PQueue-O(n)"], bbox_to_anchor=(0.6,0.9))
plt.show()
#dequeue
plt.plot(list_dequeue, color="blue")
plt.plot(list_dequeue_pq, color="red")
plt.title('Dequeue')
plt.ylabel("Quantidade de iterações")
plt.xlabel("Quantidade de dados")
plt.yticks(range(1, 31, 5))
plt.legend(["Heap-O(Log(n))", "PQueue-O(1)"], bbox_to_anchor=(0.6,0.9))
plt.show()
