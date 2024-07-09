#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
 
struct log_info{
  int comparacoes;
  int trocas;
};

void selectionsort(int*, int, struct log_info*);
void heapsort(int*, int, struct log_info*);
void buildheap(int*, int, struct log_info*);
void heapify(int*, int, int, struct log_info*);
int extract_max(int* array, int* heap_size, struct log_info* loginfo);
void insert_heap(int elemento, int* array, int* heap_size, struct log_info* loginfo);
int heap_max(int* array, int heap_size);
int pai(const int* array, const int elemento);
int filho_d(const int* array, const int elemento);
int filho_e(const int* array, const int elemento);



// Seleção direta
void selectionsort(int* array, int qtd_elementos, struct log_info* loginfo){
   int tmp;
   int menorchave;

   loginfo->trocas = 0;
   loginfo->comparacoes = 0;

   for(int i=0; i<qtd_elementos;i++){
      menorchave = i;
      for(int j=i; j<qtd_elementos; j++){
         loginfo->comparacoes++;
         if(array[j] < array[menorchave]){
            menorchave = j;
         }
      }
      if(menorchave != i){
         int tmp = array[i];
         array[i] = array[menorchave];
         array[menorchave] = tmp;
         loginfo->trocas++;
      }
   }
}
// Heapsort e funções auxiliares
void heapsort(int* array, int heap_size, struct log_info* loginfo){
   int qtd_elementos = heap_size-1;
   int tmp;

   loginfo->trocas = 0;
   loginfo->comparacoes = 0;

   buildheap(array, heap_size, loginfo);

   for(int i = qtd_elementos; i>0; i--){
      loginfo->trocas++;
      tmp = array[i];
      array[i] = array[0];
      array[0] = tmp;
      heap_size--;
      heapify(array, 0, heap_size, loginfo);
   }
}

// usada no heapsort
void buildheap(int* array, int array_size, struct log_info* loginfo){
   int ultimo_pai = (array_size/2)-1;
   for(int i=ultimo_pai; i>=0; i--)
      heapify(array, i, array_size, loginfo);
}

int filho_e(const int* array, const int elemento){
   return elemento*2+1;
}

int filho_d(const int* array, const int elemento){
   return elemento*2+2;
}

int pai(const int* array, const int elemento){
   return (elemento-1)/2;
}
 // heapify: verifica se o elemento na posição passada é um heap e se não for transforma-o em um
void heapify(int* array, int elemento, int heap_size, struct log_info* loginfo){
    int maior = elemento;
    int tmp;

    int esquerdo = filho_e(array, elemento);
    int direito = filho_d(array, elemento);

    loginfo->comparacoes+=2;
    if(esquerdo < heap_size && array[esquerdo]>array[maior])
       maior = esquerdo;

    if(direito < heap_size && array[direito]>array[maior])
       maior = direito;

    if(maior!=elemento){
      tmp = array[maior];
      array[maior] = array[elemento];
      array[elemento] = tmp;
      loginfo->trocas++;
      heapify(array, maior, heap_size, loginfo);
    }
}
// devolve o primeiro elemento do heap (sem removê-lo do heap), operando em O(1). 
int heap_max(int* array, int heap_size){
    // verificar se tamanho do array >= 1
    if (heap_size < 1){
        printf("Heap Underflow!\n");
        return -1;
    }
    return array[0];
}
// devolve e extrai o primeiro elemento do heap, reajustando-o de maneira a garantir que o array continue sendo um heap em O(log n)
int extract_max(int* array, int* heap_size, struct log_info* loginfo){
    // verificar se tamanho do array >= 1
    if (*heap_size < 1){
        printf("Heap Underflow!\n");
        return -1;
    }
    int max = heap[0];
    array[0] = array[*heap_size-1];
    (*heap_size)--;
    heapify(array, 0, *heap_size, loginfo);
    return max;
}

// insere um elemento no heap em O(log n), mantendo as propriedades de heap do array
void insert_heap(int elemento, int* array, int* heap_size, struct log_info* loginfo){
    array[*heap_size] = elemento;
    (*heap_size)++;
    heapify(array, *heap_size - 1, *heap_size, loginfo);

}