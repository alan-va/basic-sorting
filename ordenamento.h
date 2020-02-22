/* Esse header declara:
 * 
 * 1. Prototipos das funcoes de ordenamento, e
 * 2. As duas funcoes de comparacao usadas pelas funcoes.
 * 
 * Alem de definir:
 * 
 * 1. Tipo 'Contagem' e 'fcomparacao'.
 * 2. Constante 'erro'.
 * 
 * Exemplo de uso: (programa teste em testeOrdenamento.c)
 * 
 * size_t N = 10;
 * int numeros[N] = {0, 5, 1, 8, 11, 45, 2, 9, 22, 3};
 * fcomparacao modo[2] = {crescente, decrescente};
 * Contagem resultado = {0, 0, 0};
 * 
 * resultado = quickSort(numeros, 0, 9, modo[0]);
 * 
 * A instrucao acima ordena o array numeros por completo em
 * ordem crescente, que eh a funcao apontada por modo[0], e
 * resultado recebe a qtd de comparacoes, acessos ao array
 * numeros e quantas trocas a funcao quickSort realizou.
 * 
 * Funcoes disponiveis:
 * 
 * - Bubble Sort (!),
 * - Insertion Sort,
 * - Selection Sort,
 * - Double Selection Sort,
 * - Cocktail Sort,
 * - Quick Sort,
 * - Counting Sort.
 * 
 * (!) Existem duas: bubbleSort e bubbleSortV2, a segunda
 *     eh melhor pois ela realiza menos acessos ao array.
 * 
 * Caso ocorra algum erro ao chamar alguma das funcoes, por
 * exemplo limInf > limSup ou limInf < 0, as funcoes retornam
 * uma contagem invalida (-1 em cada contador).
 */

#ifndef ORDENAMENTO_H
#define ORDENAMENTO_H

#include <stdbool.h>

/* Tipo Contagem serve para guardar a ... contagem ... de
   comparacoes, acessos ao array e trocas realizadas por
   uma funcao de ordenamento, todas retornam uma variavel
   desse tipo. */
typedef struct resultados
{
  long int qtdComparacoes;
  long int qtdAcessos;
  long int qtdTrocas;
} Contagem; // alias

/* Tipo fcomparacao -> ponteiro para uma funcao 
   booleana com dois argumentos const int. */
typedef bool (*fcomparacao)(const int x, const int y);

/* Funcoes de comparacao/modo de ordenamento. */
bool decrescente(const int x, const int y);
bool crescente(const int x, const int y);

/* Funcoes de ordenamento */
Contagem bubbleSort(int *valores, int limInf, int limSup, fcomparacao modo);
Contagem bubbleSortV2(int *valores, int limInf, int limSup, fcomparacao modo);
Contagem insertionSort(int *valores, int limInf, int limSup, fcomparacao modo);
Contagem selectionSort(int *valores, int limInf, int limSup, fcomparacao modo);
Contagem doubleSelectionSort(int *valores, int limInf, int limSup, fcomparacao modo);
Contagem cocktailSort(int *valores, int limInf, int limSup, fcomparacao modo);
Contagem quickSort(int *valores, int limInf, int limSup, fcomparacao modo);
Contagem countingSort(int *valores, int limInf, int limSup, int modo);
/* CountingSort: modo 0 = crescente, modo 1 = decrescente, a funcao nao
   recebe uma funcao de comparacao pois nao realiza nenhuma comparacao. */

#endif /* ordenamento.h */
