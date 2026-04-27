#define VERSION "1.1"
#define _DEFAULT_SOURCE
#include "colors.h"
#include "config.h"
#include "detailed.h"
#include "entry.h"
#include "sort.h"
#include "style.h"
#include "tree.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>

// Visual length for each icon is fixed 2
int visual_len(char *icon) {
    return 2;
}

int main(int argc, char *argv[]) {
    // Config (~/.config/lsi/lsi.conf)
    Config config = load_config();
    // Default path is the same directory the command is being called from
    char *path = ".";
    // Flag variables
    int show_hidden = 0;
    int sort_by = SORT_NAME;
    int reverse = 0;
    int show_detailed = 0;
    int one_per_line = 0;
    int tree = 0;
    int tree_depth = 1;
    // Flag validation loop
    for (int i = 1; i < argc; i++) {
        // Help menu
        if (!strcmp(argv[i], "-help") || !strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            printf("Usage: lsi [FLAG]... [FILE]...\n");
            printf("Flags:\n");
            printf("  -a                Show hidden files\n");
            printf("  -r                Reverse sort order\n");
            printf("  -s                Sort by file size\n");
            printf("  -t                Sort by date modified\n");
            printf("  -l                Detailed view\n");
            printf("  -1                One entry per line\n");
            printf("  -h                Show this help menu\n");
            printf("  --tree            Tree view with default depth 1\n");
            printf("  --tree=N          Tree view with depth N\n");
            printf("  --no-icons        Temporarily disable icons\n");
            printf("  --no-color        Temporarily disable colors\n");
            printf("  --version         Shows version informations\n");
            printf("\n");
            return 0;
        } else if (!strcmp(argv[i], "--no-icons")) {
            config.icons = 0;
        } else if (!strcmp(argv[i], "--no-color")) {
            config.color = 0;
        } else if (!strcmp(argv[i], "--tree")) {
            tree = 1;
        } else if (!strncmp(argv[i], "--tree=", 7)) {
            tree = 1;
            tree_depth = atoi(argv[i] + 7);
            if (tree_depth <= 0) {
                printf("lsi: tree depth must be greater than 0\n");
                return 1;
            }
        } else if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-v")) {

            printf(CYAN "lsi " YELLOW "%s\n" RESET, VERSION);
            printf("Because plain ls was not enough\n");
            printf("Copyright(c) 2026 RAJDEEP NEMO\n");
            printf(CYAN "Author: " RESET "Rajdeep Nemo\n");
            printf(CYAN "License: " RESET "MIT\n");
            printf(CYAN "GitHub: " RESET "https://github.com/Rajdeep-Nemo/lsi\n");

            return 0;
        }
        // Configuration flag for icons
        else if (!strncmp(argv[i], "--set-icons=", 12)) {
            char *value = argv[i] + 12;
            if (!strcmp(value, "true") || !strcmp(value, "false")) {
                config.icons = !strcmp(value, "true") ? 1 : 0;
                save_config(config);
                return 0;
            } else {
                printf("lsi: invalid value '%s' for --set-icons, use true or false\n", value);
                return 1;
            }
        }
        // Configuration flag for icons
        else if (!strncmp(argv[i], "--set-color=", 12)) {
            char *value = argv[i] + 12;
            if (!strcmp(value, "true") || !strcmp(value, "false")) {
                config.color = !strcmp(value, "true") ? 1 : 0;
                save_config(config);
                return 0;
            } else {
                printf("lsi: invalid value '%s' for --set-color, use true or false\n", value);
                return 1;
            }
        }
        // Checks if argument is a path
        else if (argv[i][0] != '-') {
            path = argv[i];
        } else if (argv[i][0] == '-') {
            char *flag = argv[i] + 1; // skip the '-'
            for (int j = 0; flag[j] != '\0'; j++) {
                // Hidden files and folder
                if (flag[j] == 'a')
                    show_hidden = 1;
                // reverse sort
                else if (flag[j] == 'r')
                    reverse = 1;
                // By size
                else if (flag[j] == 's')
                    sort_by = SORT_SIZE;
                // By date modified
                else if (flag[j] == 't')
                    sort_by = SORT_TIME;
                // Detailed view
                else if (flag[j] == 'l')
                    show_detailed = 1;
                // One entry per line
                else if (flag[j] == '1')
                    one_per_line = 1;
                // Invalid
                else {
                    printf("lsi: unknown flag '-%c'\n", flag[j]);
                    printf("Try 'lsi -help' for more information.\n");
                    return 1;
                }
            }
        }
    }

    struct stat s;
    if (stat(path, &s) == -1) {
        printf("lsi: cannot access '%s': No such file or directory\n", path);
        return 1;
    } else if (S_ISREG(s.st_mode)) {
        if (tree) {
            printf("lsi: '%s' is not a directory\n", path);
            return 1;
        }
        if (show_detailed) {
            Entry e;
            strcpy(e.name, path);
            e.type = DT_REG;
            e.size = s.st_size;
            e.mtime = s.st_mtime;
            e.mode = s.st_mode;
            print_detailed(&e, 1, strlen(path), config);
        } else {
            char *icon = config.icons ? getIcon(path, DT_REG) : "";
            char *color = config.color ? getColor(path, DT_REG) : "";
            if (config.icons)
                printf("%s%s %s%s", color, icon, path, RESET);
            else
                printf("%s%s%s", color, path, RESET);
        }
        return 0;
    }

    DIR *currentDir = opendir(path);

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

    sort_entries(entries, count, sort_by, reverse);

    // Find the element with the longest name
    int max_len = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(entries[i].name);
        if (len > max_len) {
            max_len = len;
        }
    }

    if (tree) {
        char *dir_name = basename(path);
        char *color = config.color ? getColor(dir_name, DT_DIR) : "";
        char *icon = config.icons ? getIcon(dir_name, DT_DIR) : "";
        char *display_name;
        char quoted[258];
        if (strchr(dir_name, ' ') != NULL) {
            snprintf(quoted, sizeof(quoted), "'%s'", dir_name);
            display_name = quoted;
        } else {
            display_name = dir_name;
        }
        printf("%s%s %s%s\n", color, icon, display_name, RESET);
        print_tree(path, 0, tree_depth, config, "", show_hidden);
    } else if (show_detailed) {
        print_detailed(entries, count, max_len, config);
    } else if (one_per_line) {
        for (int i = 0; i < count; i++) {
            char *name = entries[i].name;
            char *display_name;
            char quoted[258];
            if (strchr(name, ' ') != NULL) {
                snprintf(quoted, sizeof(quoted), "'%s'", name);
                display_name = quoted;
            } else {
                display_name = name;
            }
            char *icon = config.icons ? getIcon(entries[i].name, entries[i].type) : "";
            char *color = config.color ? getColor(entries[i].name, entries[i].type) : "";
            if (config.icons)
                printf("%s%s %s%s\n", color, icon, display_name, RESET);
            else
                printf("%s%s%s\n", color, display_name, RESET);
        }
    } else {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int term_width = w.ws_col;

        int col_width = max_len + 6; // 2 icon + 2 padding + 2 extra
        int num_cols = term_width / col_width;
        if (num_cols == 0)
            num_cols = 1;

        for (int i = 0; i < count; i++) {
            char *icon = config.icons ? getIcon(entries[i].name, entries[i].type) : "";
            char *color = config.color ? getColor(entries[i].name, entries[i].type) : "";
            char *name = entries[i].name;

            char *display_name;
            char quoted[258];
            if (strchr(name, ' ') != NULL) {
                snprintf(quoted, sizeof(quoted), "'%s'", name);
                display_name = quoted;
            } else {
                display_name = name;
            }

            int name_len = strlen(display_name);
            int icon_len = visual_len(icon);
            int padding = col_width - name_len - icon_len - 1; // 1 for space between icon and name

            if (config.icons)
                printf("%s%s %s%s", color, icon, display_name, RESET);
            else
                printf("%s%s%s", color, display_name, RESET);
            for (int p = 0; p < padding; p++) {
                printf(" ");
            }

            if ((i + 1) % num_cols == 0) {
                printf("\n");
            }
        }
        if (count % num_cols != 0) {
            printf("\n");
        }
    }

    closedir(currentDir);
}