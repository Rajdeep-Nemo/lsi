#ifndef ENTRY_H
#define ENTRY_H

// Stores each item in a directory
typedef struct
{
    char name[256];
    unsigned char type;
} Entry;

#endif