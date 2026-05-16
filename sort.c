#include "sort.h"
#include "entry.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static int sort_by_global = SORT_NAME;

int compare_entries(const void *a, const void *b) {
    const Entry *ea = (Entry *)a;
    const Entry *eb = (Entry *)b;

    // Directories first
    if (ea->type == DT_DIR && eb->type != DT_DIR)
        return -1;
    if (ea->type != DT_DIR && eb->type == DT_DIR)
        return 1;

    // Sort by size
    if (sort_by_global == SORT_SIZE)
        return (int)ea->size - (int)eb->size;

    // Sort by last modified
    if (sort_by_global == SORT_TIME)
        return (int)ea->time - (int)eb->time;

    // Alphabetically
    return strcmp(ea->name, eb->name);
}

void sort_entries(Entry *entries, const int count, const int sort_by, const int reverse) {
    sort_by_global = sort_by;
    qsort(entries, count, sizeof(Entry), compare_entries);

    if (reverse) {
        for (int i = 0; i < count / 2; i++) {
            const Entry temp = entries[i];
            entries[i] = entries[count - 1 - i];
            entries[count - 1 - i] = temp;
        }
    }
}