#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
                                                            // potências de 10 a serem testadas como tamanhos de arrays

struct log_info{
  int comparacoes;
  int trocas;
  double tempo;
  int tamanho;
  char sigla[5];
  char tipo;
};


void bubblesort(int*, int, struct log_info*);
void quicksort(int*, int, struct log_info*);
void quicksort_aux(int*, int, int, struct log_info*);
int particiona(int*, int, int, struct log_info*);
void swap(int *, int *);
void shakesort(int* array, int array_size, struct log_info* log);
void combsort(int* array, int array_size, struct log_info* log);

void bubblesort(int* array, int array_size, struct log_info* log){
    int trocas = 0;
    int comparacoes = 0;
    int pos_troca = 0;
    bool troca = true;
    int qtd_elementos = array_size-1;

    while(troca){
        troca = false;
        for(int i=0; i<qtd_elementos;i++){
            comparacoes = comparacoes + 1;
            if(array[i] > array[i+1]){
              swap(&array[i], &array[i+1]);
              troca = true;
              pos_troca = i;
              trocas = trocas + 1;
            }
        }
        qtd_elementos = pos_troca;
    }

    log->trocas = trocas;
    log->comparacoes = comparacoes;
}

void quicksort(int* array, int array_size, struct log_info* log){
  log->trocas = 0;
  log->comparacoes = 0;
  quicksort_aux(array, 0, array_size-1, log);
}

void quicksort_aux(int* array, int i, int f, struct log_info* log){
    int p;
    if(f>i){
		  p = particiona(array, i, f, log);
		  quicksort_aux(array, i, p-1, log);
		  quicksort_aux(array, p+1, f, log);
	}
}

int particiona(int* array, int esq, int dir, struct log_info* log){
  int i=esq+1, j=dir, pivo=esq;
  while(j>i){
    while(array[i]<array[pivo] && i<dir) {
      i++;
      log->comparacoes++;
    }
    while(array[j]>=array[pivo] && j>esq){
      j--;
      log->comparacoes++;
    }

    if(i<j && array[i]>array[j]){
      swap(&array[i], &array[j]);
      log->comparacoes++;
      log->trocas++;
    }
  }

  if(array[j]<array[pivo]){
	  swap(&array[pivo], &array[j]);
    log->comparacoes++;
    log->trocas++;
  }
  return j;
}

void swap(int *n1, int *n2){
	int troca = *n1;
	*n1 = *n2;
	*n2 = troca;
}

void shakesort(int* array, int array_size, struct log_info* log){
    int trocas = 0;
    int comparacoes = 0;

    bool troca = true;

    int bot = 0;
    int top = array_size-1;

    while(troca && (bot<top)){

        troca = false;

        for(int i=bot; i<top;i++){
            comparacoes = comparacoes + 1;
            if(array[i] > array[i+1]){
              swap(&array[i], &array[i+1]);
              troca = true;
              trocas++;
            }
        }

        top--;

        for(int i=top; i>bot;i--){
            comparacoes = comparacoes + 1;
            if(array[i] < array[i-1]){
              swap(&array[i], &array[i-1]);
              troca = true;
              trocas++;
            }
        }

        bot++;

    }

  log->trocas = trocas;
  log->comparacoes = comparacoes;
}

void combsort(int* array, int array_size, struct log_info* log){
  int trocas = 0;
  int comparacoes = 0;

  bool troca = true;

  int passo = array_size;

  while (troca || passo > 1){
    passo = (int)(passo/1.3);
    if (passo < 1){
        passo = 1;
    }
    troca = false;
    for (int i = 0; i < array_size - passo; i++){
        comparacoes++;
        if (array[i] > array[i+passo]){
            swap(&array[i], &array[i+passo]);
            trocas++;
            troca = true;
        }
    }
  }


  log->trocas = trocas;
  log->comparacoes = comparacoes;
}

