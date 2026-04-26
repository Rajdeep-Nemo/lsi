#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
        char line[128];
        while (fgets(line, sizeof(line), config)) {
            if (!strncmp(line, "icons=false", 11))
                cfg.icons = 0;
            if (!strncmp(line, "color=false", 11))
                cfg.color = 0;
        }
        fclose(config);
    }
    return cfg;
}
