#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include "ordenamento.h"

/* prototipos - inicializa e mostra array */
void inicializaAleatorio(int *array, int qtd, int limiteSup);
void inicializaPiorCaso(int *valores, int tamanho);
void mostraArray(int *array, int tamanho);

int main(void)
{
  const Fcomparacao f[2] = {crescente, decrescente};
  int *numeros, N, algoritmo, ordem;
  double tempoExec;
  time_t tic, tac;
  Contagem res1;
  char esc;

  printf("Teste de algoritmos de ordenação em um array aleatorio de N elementos\n\n");
  printf("Algoritmos disponiveis: [1] Bubble Sort\n");
  printf("                        [2] Insertion Sort\n");
  printf("                        [3] Selection Sort\n");
  printf("                        [4] Double-Selection Sort\n");
  printf("                        [5] Cocktail Shaker Sort\n");
  printf("                        [6] Counting Sort\n");
  printf("                        [7] Quick Sort\n\n");

  printf("Algoritmo de escolha: "); scanf("%d", &algoritmo);
  if (algoritmo < 1 || algoritmo > 7) { printf("\nEscolha invalida.\n"); return 1; }

  printf("Ordem crescente (1) ou decrescente (2)? "); scanf("%d", &ordem);
  if (ordem < 1 || ordem > 2) { printf("\nEscolha invalida.\n"); return 1; }

  printf("Insira N: "); scanf("%d", &N);
  
  // int_max/1.5 - 3 = 1431655761
  if (N > INT_MAX/1.5 - 3) { printf("\nValor muito alto.\n"); return 1; }

  numeros = (int *) calloc(N, sizeof(int));
  //inicializaAleatorio(numeros, N, 1.5*N);
  inicializaPiorCaso(numeros, N);

  printf("\nMostrar array gerado? (s/n) "); scanf(" %c", &esc);
  if (esc == 's') { printf("\nDesordenado:\n"); mostraArray(numeros, N); }

  switch(algoritmo)
  {
    case 1:
      tic = clock();
      res1 = bubbleSortV2(numeros, 0, N-1, (*f[ordem-1]));
      tac = clock(); break;
    case 2:
      tic = clock();
      res1 = insertionSort(numeros, 0, N-1, (*f[ordem-1]));
      tac = clock(); break;
    case 3:
      tic = clock();
      res1 = selectionSort(numeros, 0, N-1, (*f[ordem-1]));
      tac = clock(); break;
    case 4:
      tic = clock();
      res1 = doubleSelectionSort(numeros, 0, N-1, (*f[ordem-1]));
      tac = clock(); break;
    case 5:
      tic = clock();
      res1 = cocktailSort(numeros, 0, N-1, (*f[ordem-1]));
      tac = clock(); break;
    case 6:
      tic = clock();
      res1 = countingSort(numeros, 0, N-1, ordem-1);
      tac = clock(); break;
    case 7:
      tic = clock();
      res1 = quickSort(numeros, 0, N-1, (*f[ordem-1]));
      tac = clock(); break;
    default:
      printf("\nEscolha invalida.\n");
      break;
  }

  tempoExec = (double)(tac-tic) / CLOCKS_PER_SEC;

  printf("\nMostrar array ordenado? (s/n) "); scanf(" %c", &esc);
  if (esc == 's') { printf("\nOrdenado: \n"); mostraArray(numeros, N); }

  printf("\nTempo da ordenação: %.4fs\n", tempoExec);
  printf("\nResultados -> Acessos ao array: %ld.\n", res1.qtdAcessos);
  printf("           -> Quantidade de trocas: %ld.\n", res1.qtdTrocas);
  printf("           -> Quantidade de comparações: %ld.\n", res1.qtdComparacoes);

  free(numeros); numeros = NULL;

  return 0;
} // fim - main

void mostraArray(int *array, int tamanho)
{
  int i;
  if (array != NULL)
  {
    for (i = 0; i < tamanho; i++)
    { 
      if (i % 20 == 0) printf("\n");
      printf("%.2d ", array[i]);
    }
    printf("\n");
  }
  else { printf("\nErro. (01)\n"); return; }
} // fim - mostraArray

void inicializaAleatorio(int *array, int tamanho, int limiteSup)
{
  int i; srand(time(0));
  if (array != NULL)
  { 
    for (i = 0; i < tamanho; i++) 
    { 
      array[i] = rand() % limiteSup;
    }
  }
  else { printf("\nErro. (02)\n"); return; }
} // fim - inicializaAleatorio

void inicializaPiorCaso(int *array, int tamanho)
{
  int i;
  if (array != NULL)
  {
    for (i = 0; i < tamanho; i++)
    {
      array[i] = tamanho-i;
    }
  }
} // fim - inicializaPiorCaso
