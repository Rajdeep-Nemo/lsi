#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int icons;
    int color;
} Config;

Config load_config();

#endif