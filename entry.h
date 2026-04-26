#ifndef ENTRY_H
#define ENTRY_H
#include <sys/types.h>
#include <time.h>

// Stores each item in a directory
typedef struct
{
    char name[256];
    unsigned char type;
    off_t size;
    time_t mtime;
} Entry;

#endif