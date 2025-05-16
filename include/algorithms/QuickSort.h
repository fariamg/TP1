#pragma once

#include <Statistics.h>
#include <Vector.h>

void quickSort(Vector& v, int l, int r, Statistics& stats);

void partition3(Vector& v, int l, int r, int& i, int& j, Statistics& stats);

int median(int a, int b, int c);