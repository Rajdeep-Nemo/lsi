#ifndef CONFIG_H
#define CONFIG_H

// Struct to hold config values
typedef struct {
    int icons;
    int color;
} Config;

// Loads config file
Config load_config();

// Saves a config
void save_config(Config config);

#endif