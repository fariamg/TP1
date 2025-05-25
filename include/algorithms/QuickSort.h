#pragma once

#include "measurement/Statistics.h"
#include "datastructures/Vector.h"

//@ Função de ordenação rápida (QuickSort) 
void quickSort(Vector& V, int partitionSize, int l, int r, Statistics& stats);

//@ Função de partição para o QuickSort
void partition(Vector& V, int l, int r, int& i, int& j, Statistics& stats);

//@ Função para calcular o valor mediano entre três inteiros
int median(int a, int b, int c);
