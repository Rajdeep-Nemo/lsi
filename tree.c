#define _DEFAULT_SOURCE
#include "config.h"
#include "entry.h"
#include "colors.h"
#include "style.h"
#include "sort.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

// Recursive function for tree view
void print_tree(char *path, int depth, int max_depth, Config config, char *prefix, int show_hidden) {
    DIR *currentDir = opendir(path);

    if (currentDir == NULL) {
        printf("lsi: cannot open '%s': Not a directory\n", path);
        return;
    }

    struct dirent *entry;
    Entry entries[1024];
    int count = 0;

    // Loops through all the items and stores them in a struct
    while ((entry = readdir(currentDir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        if (entry->d_name[0] == '.' && !show_hidden) {
            continue;
        }

        strcpy(entries[count].name, entry->d_name);
        entries[count].type = entry->d_type;
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        struct stat s;
        stat(full_path, &s);
        entries[count].size = s.st_size;
        entries[count].mtime = s.st_mtime;
        entries[count].mode = s.st_mode;
        count += 1;
    }
    closedir(currentDir);

    sort_entries(entries, count, SORT_NAME, 0);

    for (int i = 0; i < count; i++) {
        int is_last = (i == count - 1);

        // print prefix + connector
        printf("%s%s ", prefix, is_last ? "└──" : "├──");

        // print icon + name with color
        char *icon = config.icons ? getIcon(entries[i].name, entries[i].type) : "";
        char *color = config.color ? getColor(entries[i].name, entries[i].type) : "";

        char *display_name;
        char quoted[258];
        if (strchr(entries[i].name, ' ') != NULL) {
            snprintf(quoted, sizeof(quoted), "'%s'", entries[i].name);
            display_name = quoted;
        } else {
            display_name = entries[i].name;
        }
        printf("%s%s %s%s\n", color, icon, display_name, RESET);

        // recurse into directories
        if (entries[i].type == DT_DIR && depth < max_depth) {
            char new_path[1024];
            char new_prefix[512];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entries[i].name);
            snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");
            print_tree(new_path, depth + 1, max_depth, config, new_prefix, show_hidden);
        }
    }
}