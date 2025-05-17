#pragma once

#include "measurement/Statistics.h"
#include "datastructures/Vector.h"

void quickSort(Vector& v, int l, int r);

void partition3(Vector& v, int l, int r, int& i, int& j);

int median(int a, int b, int c);