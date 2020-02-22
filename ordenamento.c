#include <stdlib.h>
#include "ordenamento.h"

static const Contagem _erro = {-1, -1, -1};

/* Funcoes (publicas) de comparacao/modo para ordenamento. */
bool decrescente(const int x, const int y) { return (x < y) ? true : false; }
bool crescente(const int x, const int y) { return (x > y) ? true : false; }

/* troca e elementoMax sao funcoes internas (nao publicas). */

static void troca(int * const valor1, int * const valor2)
{
  int tmp;
  if (valor1 != NULL && valor2 != NULL)
  {
    tmp = *valor1;
    *valor1 = *valor2;
    *valor2 = tmp;
  }
} // fim - troca

static int elementoMax(int *valores, int limInf, int limSup)
{
  int i, max;
  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    max = valores[limInf];
    for (i = limInf+1; i <= limSup; i++)
    {
      if (valores[i] > max)
        max = valores[i];
    }
    return max;
  }
  else { return -1; } // erro
} // fim - elementoMax

/* Funcoes de ordenamento - todas publicas. */

Contagem bubbleSort(int *valores, int limInf, int limSup, 
    bool (*compara)(int x, int y))
{
  Contagem total = {0, 0, 0};
  bool trocou;
  int i;

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    while (limInf < limSup)
    {
      trocou = false;
      for (i = limInf+1; i <= limSup; i++)
      {
        total.qtdAcessos += 2; total.qtdComparacoes++;
        if ((*compara)(valores[i-1], valores[i]))
        {
          troca(&valores[i-1], &valores[i]); total.qtdTrocas++;
          trocou = true; total.qtdAcessos += 4;
        }
      }
      if (!trocou) { break; } // ordenado
      limSup--; // menor/maior ja esta na ultima posicao
    }

    return total;
  }
  else { return _erro; }
} // fim - bubbleSort

Contagem bubbleSortV2(int *valores, int limInf, int limSup, 
    bool (*compara)(int x, int y))
{
  Contagem total = {0, 0, 0};
  int i, ultimo;
  bool trocou;

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    while (limSup > 0)
    {
      trocou = false; ultimo = limInf;
      for (i = limInf+1; i <= limSup; i++)
      {
        total.qtdAcessos += 2; total.qtdComparacoes++;
        if ((*compara)(valores[i-1], valores[i]))
        {
          troca(&valores[i-1], &valores[i]); total.qtdTrocas++;
          ultimo = i; trocou = true;
        }
      }
      if (!trocou) { break; } // ordenado
      limSup = ultimo - 1;
    }

    return total;
  }
  else { return _erro; }
} // fim - bubbleSortV2

Contagem insertionSort(int *valores, int limInf, int limSup, 
    bool (*compara)(int x, int y))
{
  Contagem total = {0, 0, 0};
  int i, j, t;

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    for (i = limInf+1; i <= limSup; i++)
    {
      t = valores[i]; total.qtdAcessos++; j = i-1;
      while (j >= limInf && (*compara)(valores[j], t))
      {
        valores[j+1] = valores[j]; j--;
        total.qtdAcessos += 2;
        total.qtdTrocas++;
        total.qtdComparacoes++; // proxima iteracao
      }
      valores[j+1] = t;
      total.qtdAcessos++;
      total.qtdTrocas++; // nesse caso insercao
    }

    return total;
  }
  else { return _erro; }
} // fim - insertionSort

Contagem selectionSort(int *valores, int limInf, int limSup, 
    bool (*compara)(int x, int y))
{
  Contagem total = {0, 0, 0};
  int i, j, indCorreto;

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    for (i = limInf; i <= limSup; i++)
    {
      indCorreto = i;
      for (j = i+1; j <= limSup; j++)
      {
        total.qtdAcessos += 2; total.qtdComparacoes++;
        if ((*compara)(valores[indCorreto], valores[j]))
          indCorreto = j;
      }
      if (i != indCorreto)
      {
        troca(&valores[i], &valores[indCorreto]);
        total.qtdAcessos += 4; // funcao troca
        total.qtdTrocas++;
      }
    }

    return total;
  }
  else { return _erro; }
} // fim - selectionSort

Contagem doubleSelectionSort(int *valores, int limInf, int limSup, 
    bool (*compara)(int x, int y))
{
  int i, j, ind2, ind1, novoInd2;
  Contagem total = {0, 0, 0};

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    for (i = limInf; i <= limSup; i++)
    {
      ind1 = i; ind2 = limSup;
      if (ind1 >= ind2) { break; }
      for (j = ind1+1; j <= ind2; j++)
      {
        total.qtdAcessos += 2; total.qtdComparacoes++;
        if ((*compara)(valores[ind1], valores[j]))
          ind1 = j;
      }
      if (ind1 != i)
      { 
        troca(&valores[i], &valores[ind1]);
        total.qtdAcessos += 4; // funcao troca
        total.qtdTrocas++; 
      }
      novoInd2 = ind2;
      for (j = ind2-1; j > i; j--)
      {
        total.qtdAcessos += 2; total.qtdComparacoes++;
        if ((*compara)(valores[j], valores[novoInd2]))
          novoInd2 = j;
      }
      if (novoInd2 != ind2) 
      {
        troca(&valores[novoInd2], &valores[ind2]);
        total.qtdAcessos += 4; total.qtdTrocas++;
      }
      limSup--;
    }

    return total;
  }
  else { return _erro; }
} // fim - doubleSelectionSort

Contagem cocktailSort(int *valores, int limInf, int limSup,
    bool (*compara)(int x, int y))
{
  Contagem total = {0, 0, 0};
  int ultimo1, ultimo2, i, j;
  bool trocou;

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    while(limInf < limSup)
    {
      trocou = false;
      for (i = limInf+1; i <= limSup; i++)
      {
        total.qtdAcessos += 2; total.qtdComparacoes++;
        if ((*compara)(valores[i-1], valores[i]))
        {
          troca(&valores[i], &valores[i-1]);
          total.qtdTrocas++; total.qtdAcessos += 4;
          ultimo1 = i; trocou = true;
        }
      }

      if (!trocou) { break; } // ja ordenado
      else { trocou = false; }

      for (j = limSup-1; j > limInf; j--)
      {
        total.qtdAcessos += 2; total.qtdComparacoes++;
        if ((*compara)(valores[j-1], valores[j]))
        {
          troca(&valores[j-1], &valores[j]);
          total.qtdTrocas++; total.qtdAcessos += 4;
          ultimo2 = j; trocou = true;
        }
      }

      if (!trocou) { break; } // ja ordenado
      else { limInf = ultimo2; limSup = ultimo1-1; }
    }

    return total;
  }
  else { return _erro; }
} // fim - cokctailSort

Contagem quickSort(int *valores, int limInf, int limSup, 
    bool (*compara)(int x, int y))
{
  Contagem total = {0, 0, 0}, total1 = {0, 0, 0}, total2 = {0, 0, 0};
  int i, j, pivo, meio;
  bool continua;

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    i = limInf; j = limSup;
    meio = (int)(limSup+1-limInf)/2;
    pivo = valores[limInf + meio]; total.qtdAcessos++;
    continua = true;

    while (continua)
    {
      total.qtdAcessos += 2; total.qtdComparacoes += 2;
      while ((*compara)(pivo, valores[i])) { i++; }
      while ((*compara)(valores[j], pivo)) { j--; }
      if (i <= j) 
      {
        troca(&valores[i], &valores[j]); i++; j--; 
        total.qtdTrocas++; total.qtdAcessos += 4;
      }
      if (i > j) { continua = false; }
    }

    if (j > limInf) { total1 = quickSort(valores, limInf, j, (*compara)); }
    if (i < limSup) { total2 = quickSort(valores, i, limSup, (*compara)); }

    /* atualiza o total com as contagens feitas nas chamadas recursivas */
    total.qtdComparacoes += total1.qtdComparacoes + total2.qtdComparacoes;
    total.qtdAcessos += total1.qtdAcessos + total2.qtdAcessos;
    total.qtdTrocas += total1.qtdTrocas + total2.qtdTrocas;

    return total;
  }
  else { return _erro; }
} // fim - quickSort

Contagem countingSort(int *valores, int limInf, int limSup, int modo)
{
  Contagem total = {0, 0, 0};
  int i, k, *c, *b;

  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    k = elementoMax(valores, limInf, limSup) + 1;
    total.qtdAcessos += (limSup+1-limInf); // funcao elementoMax
    c = (int *) calloc(k, sizeof(int));
    b = (int *) calloc(limSup-limInf+1, sizeof(int));

    total.qtdAcessos += 2*(limSup+1-limInf); // laco abaixo
    for (i = limInf; i <= limSup; i++) { c[valores[i]]++; }
    for (i = limInf+1; i < k; i++) { c[i] = c[i] + c[i-1]; }
    for (i = limSup; i >= limInf; i--)
    {
      c[valores[i]] = c[valores[i]] - 1;
      b[c[valores[i]]] = valores[i];
      total.qtdAcessos += 4;
    }

    /* copia array b em valores e desaloca b & c */
    if (modo == 0)
      for (i = limInf; i <= limSup; i++) { valores[i] = b[i-limInf]; }
    if (modo == 1)
      for (i = limInf; i <= limSup; i++) { valores[i] = b[limSup-i]; }

    free(b); free(c); b = NULL; c = NULL;

    return total;
  }
  else { return _erro; }
} // fim - countingSort

/* SlowSort eh um algoritmo relutante, caracteristico do paradigma
 * 'multiplicar e se render' ao inves de 'dividir e conquistar',
 * ideal se voce nao esta com muita pressa... */
Contagem slowSort(int *valores, int limInf, int limSup,
    bool (*compara)(const int, const int))
{
  Contagem total = {0, 0, 0}, rec1, rec2, rec3;
  int mid = 0;
  
  if (valores != NULL && limInf < limSup && limInf >= 0)
  {
    mid = (int)((limInf+limSup)/2);
    rec1 = slowSort(valores, limInf, mid, (*compara));
    rec2 = slowSort(valores, mid+1, limSup, (*compara));
    total.qtdAcessos += 2; total.qtdComparacoes++;
    if ((*compara)(valores[mid], valores[limSup]))
    {
      troca(&valores[mid], &valores[limSup]);
      total.qtdTrocas++;
    }
    rec3 = slowSort(valores, limInf, limSup-1, (*compara));
    
    total.qtdTrocas += rec1.qtdTrocas + rec2.qtdTrocas + rec3.qtdTrocas;
    total.qtdComparacoes += rec1.qtdComparacoes + rec2.qtdComparacoes + \
      rec3.qtdComparacoes;
    total.qtdAcessos += rec1.qtdAcessos + rec2.qtdAcessos + rec3.qtdAcessos;
    
    return total;
  }
  else { return _erro; }
} // fim - slowSort
