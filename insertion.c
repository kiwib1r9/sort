#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


typedef struct log_info{                                                        // estrutura que armazena quantidades de operações (comparações e trocas)
  int comparacoes;                                                              // e tempo de processamento
  int trocas;
  double tempo;
}log_info;

void insertion_sort(int*, int, log_info*);
void insertion_sortBB(int*, int, log_info*);
void shellsort(int*, int, log_info*);

void insertion_sort(int* array, int array_size, log_info* log){
    log->trocas = 0;
    log->comparacoes = 0;
    for(int i=1;i<array_size;i++){                                              // do segundo ao último
        int chave = array[i];                                                   // chave a inserir no subarray ordenado
        int j = i-1;                                                            // último elemento do subarray ordenado
        log->comparacoes++;
        while(j >= 0 && array[j] > chave){                                      // busca linear da direita para a esquerda no subarray ordenado
            log->comparacoes++;
            array[j+1] = array[j];
            j = j - 1;
            log->trocas++;
        }
        if(j+1 != i){
           array[j+1] = chave;
           log->trocas++;
       }
    }
}

void insertion_sortBB(int* array, int array_size, log_info* log){
    log->trocas = 0;
    log->comparacoes = 0;
    for(int i=1;i<array_size;i++){                                              // do segundo ao último
            int chave = array[i];
            int pos = 0;                                                   // chave a inserir no subarray ordenado
            int inicio = 0;
            int fim = i-1;                                                            // último elemento do subarray ordenado
            if (chave <= array[i-1]){
            // busca posicao de inserção com busca binaria
                while(inicio <= fim){                                      // busca linear da direita para a esquerda no subarray ordenado
                    log->comparacoes++;
                    pos = floor((inicio + fim) / 2);
                    if (chave < array[pos]){
                        fim = pos - 1; 
                                    
                    }
                    else if (chave >= array[pos]){
                        inicio = pos + 1;    
                        
                    }
                }
                    // realiza trocas
                // move os elementos maiores que a chave para a direita
                for (int j = i - 1; j >= pos; j--) {
                    log->trocas++;
                    array[j + 1] = array[j];
                }
            
                // Insere a chave na posição correta
                array[pos] = chave;
                log->trocas++;      
            }     
    }
}

void shellsort(int* array, int array_size, log_info* log){
    log->comparacoes = 0;
    log->trocas = 0;

    // passo inicial 
    int h = 1;       
    while (h < array_size)  {
        h = 3*h + 1;
    }

    while (h >= 1){
        // insertion sort para shellsort
        for(int i=h;i<array_size;i++){                                              
            int chave = array[i];                                                   
            int j = i-h;                                                           
            while(j >= 0 && array[j] > chave){                                      
                log->comparacoes++;
                array[j+h] = array[j];
                j = j - h;
                log->trocas++;
            }
            array[j+h] = chave;
            log->trocas++;

        }
        h/=3;
    }
    
}
