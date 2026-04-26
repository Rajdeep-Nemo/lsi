#define _DEFAULT_SOURCE
#include "detailed.h"
#include "colors.h"
#include "entry.h"
#include "style.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

// Formats file size from raw bytes to a more readable format
static char *format_size(off_t size) {
    static char formatted_size[128];
    if (size < 1024) {
        snprintf(formatted_size, sizeof(formatted_size), "%ldB", size);
    } else if (size < 1024 * 1024) {
        snprintf(formatted_size, sizeof(formatted_size), "%.1fK", size / 1024.0);
    } else if (size < 1024 * 1024 * 1024) {
        snprintf(formatted_size, sizeof(formatted_size), "%.1fM", size / 1024.0 / 1024.0);
    } else {
        snprintf(formatted_size, sizeof(formatted_size), "%.1fG", size / 1024.0 / 1024.0 / 1024.0);
    }
    return formatted_size;
}

// Formats seconds to more detailed format
static char *format_date(time_t mtime) {
    static char formatted_date_time[128];
    struct tm *t = localtime(&mtime);
    strftime(formatted_date_time, sizeof(formatted_date_time), "%b %-d %Y %H:%M", t);
    return formatted_date_time;
}

// Format file permission
static char *format_permissions(mode_t mode) {
    static char perms[11];

    perms[0] = S_ISDIR(mode) ? 'd' : '-';
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';

    return perms;
}

// Prints a detailed view
void print_detailed(Entry *entries, int count, int max_len) {
    int max_size_len = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(format_size(entries[i].size));
        if (len > max_size_len) {
            max_size_len = len;
        }
    }
    for (int i = 0; i < count; i++) {
        char *icon = getIcon(entries[i].name, entries[i].type);
        char *color = getColor(entries[i].name, entries[i].type);
        char *size = entries[i].type == DT_DIR ? "-" : format_size(entries[i].size);
        char *date = format_date(entries[i].mtime);
        char *mode = format_permissions(entries[i].mode);

        int name_len = strlen(entries[i].name);
        int padding = max_len - name_len;

        printf(" %s%s %s%s", color, icon, entries[i].name, RESET);
        for (int j = 0; j < padding; j++) {
            printf(" ");
        }
        printf("    %s    %*s    %s\n", mode, max_size_len, size, date);
    }
}
