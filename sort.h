#ifndef SORT_H
#define SORT_H

#include "entry.h"

#define SORT_NAME 0
#define SORT_SIZE 1
#define SORT_TIME 2

void sort_entries(Entry *entries, int count, int sort_by, int reverse);

#endif