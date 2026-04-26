#include "config.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Loads config file
Config load_config() {
    Config cfg = {1, 1};
    char config_path[512];
    snprintf(config_path, sizeof(config_path), "%s/.config/lsi/lsi.conf", getenv("HOME"));

    FILE *config = fopen(config_path, "r");
    if (config == NULL) {
        char dir_path[512];
        snprintf(dir_path, sizeof(dir_path), "%s/.config/lsi", getenv("HOME"));
        mkdir(dir_path, 0755);
        FILE *new_config = fopen(config_path, "w");
        if (new_config != NULL) {
            fprintf(new_config, "icons=true\n");
            fprintf(new_config, "color=true\n");
            fclose(new_config);
        }
    } else {
        int icons_set = 0;
        int color_set = 0;

        char line[128];
        while (fgets(line, sizeof(line), config)) {
            if (!strncmp(line, "icons=true", 10)) {
                cfg.icons = 1;
                icons_set = 1;
            }
            if (!strncmp(line, "icons=false", 11)) {
                cfg.icons = 0;
                icons_set = 1;
            }
            if (!strncmp(line, "color=true", 10)) {
                cfg.color = 1;
                color_set = 1;
            }
            if (!strncmp(line, "color=false", 11)) {
                cfg.color = 0;
                color_set = 1;
            }
        }
        fclose(config);

        if (!icons_set || !color_set) {
            printf(CORAL "lsi: bad config, regenerating..." RESET "\n");
            save_config(cfg);
        }
    }
    return cfg;
}

// Saves a config
void save_config(Config config) {
    char config_path[512];
    snprintf(config_path, sizeof(config_path), "%s/.config/lsi/lsi.conf", getenv("HOME"));

    FILE *f = fopen(config_path, "w");
    if (f != NULL) {
        fprintf(f, "icons=%s\n", config.icons ? "true" : "false");
        fprintf(f, "color=%s\n", config.color ? "true" : "false");
        fclose(f);
    }
}