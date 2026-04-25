#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "entry.h"

int compare_entries(const void *a, const void *b)
{
    Entry *ea = (Entry *)a;
    Entry *eb = (Entry *)b;

    // Directories first
    if (ea->type == DT_DIR && eb->type != DT_DIR)
        return -1;
    if (ea->type != DT_DIR && eb->type == DT_DIR)
        return 1;

    // Alphabetically
    return strcmp(ea->name, eb->name);
}

void sort_entries(Entry *entries, int count)
{
    qsort(entries, count, sizeof(Entry), compare_entries);
}