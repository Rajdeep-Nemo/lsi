#ifndef STYLE_H
#define STYLE_H
#include "entry.h"

char *getIcon(const char *name, unsigned char type, mode_t mode);
char *getColor(const char *name, unsigned char type, mode_t mode);

#endif