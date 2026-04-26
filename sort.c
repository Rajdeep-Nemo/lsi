#define _DEFAULT_SOURCE
#include "sort.h"
#include "entry.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static int sort_by_global = SORT_NAME;

int compare_entries(const void *a, const void *b) {
    Entry *ea = (Entry *)a;
    Entry *eb = (Entry *)b;

    // Directories first
    if (ea->type == DT_DIR && eb->type != DT_DIR)
        return -1;
    if (ea->type != DT_DIR && eb->type == DT_DIR)
        return 1;

    // Sort by size
    if (sort_by_global == SORT_SIZE)
        return ea->size - eb->size;

    // Sort by last midified
    if (sort_by_global == SORT_TIME)
        return ea->mtime - eb->mtime;

    // Alphabetically
    return strcmp(ea->name, eb->name);
}

void sort_entries(Entry *entries, int count, int sort_by, int reverse) {
    sort_by_global = sort_by;
    qsort(entries, count, sizeof(Entry), compare_entries);

    if (reverse) {
        for (int i = 0; i < count / 2; i++) {
            Entry temp = entries[i];
            entries[i] = entries[count - 1 - i];
            entries[count - 1 - i] = temp;
        }
    }
}