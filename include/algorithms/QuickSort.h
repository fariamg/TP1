#pragma once

#include "Statistics.h"
#include "Vector.h"

void quickSort(Vector& V, int partitionSize, int l, int r, Statistics& stats);

void partition(Vector& V, int l, int r, int& i, int& j, Statistics& stats);

int median(int a, int b, int c);
