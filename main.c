#define _DEFAULT_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "colors.h"
#include "style.h"
#include "entry.h"
#include "sort.h"

// Visual length for each icon is fixed 2
int visual_len(char *icon)
{
    return 2;
}

int main(int argc, char *argv[]){
    char *path = ".";
    // Flag variables
    int show_hidden = 0;
    // Flag validation loop
    for (int i = 1; i < argc; i++)
    {
        // Help menu
        if (!strcmp(argv[i], "-help") || !strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
        {
            printf("\n");
            printf("Usage: lsi [flags]\n");
            printf("\n");
            printf("Flags:\n");
            printf("  -a        Show hidden files\n");
            printf("  -l        Detailed view\n");
            printf("  -h        Show this help menu\n");
            printf("\n");
            return 0;
        }

        // Flag to show hidden files and folders
        if (!strcmp(argv[i], "-a") || !strcmp(argv[i], "-A"))
        {
            show_hidden = 1;
        }
        // Checks if argument is a path
        else if (argv[i][0] != '-')
        {
            path = argv[i];
        }
        // Invalid flag
        else
        {
            printf("lsi: unknown flag '%s'\n", argv[i]);
            printf("Try 'lsi -h' for more information.\n");
            return 1;
        }
    }

    struct stat s;
    if (stat(path, &s) == -1)
    {
        printf("lsi: cannot access '%s': No such file or directory\n", path);
        return 1;
    }
    else if (S_ISREG(s.st_mode))
    {
        printf("%s%s %s%s\n", getColor(path, DT_REG), getIcon(path, DT_REG), path, RESET);
        return 0;
    }

    DIR *currentDir = opendir(path);

    struct dirent *entry;
    Entry entries[1024];
    int count = 0;

    // Loops through all the items and stores them in a struct
    while ((entry = readdir(currentDir)) != NULL)
    {
        if (!strcmp(entry->d_name,".") || !strcmp(entry->d_name,".."))
        {
            continue;
        }
        if (entry->d_name[0] == '.' && !show_hidden)
        {
            continue;
        }
        
        strcpy(entries[count].name , entry->d_name);
        entries[count].type = entry->d_type;
        count += 1;
    }

    sort_entries(entries, count);

    // Find the element with the longest name
    int max_len = 0;
    for (int i = 0; i < count; i++)
    {
        int len = strlen(entries[i].name);
        if (len > max_len)
        {
            max_len = len;
        }
    }
    
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int term_width = w.ws_col;

    int col_width = max_len + 6; // 2 icon + 2 padding + 2 extra
    int num_cols = term_width / col_width;
    if (num_cols == 0) num_cols = 1;

    for (int i = 0; i < count; i++)
    {
        char *icon = getIcon(entries[i].name, entries[i].type);
        char *name = entries[i].name;

        char *display_name;
        char quoted[258];
        if (strchr(name, ' ') != NULL)
        {
            snprintf(quoted, sizeof(quoted), "'%s'", name);
            display_name = quoted;
        }
        else
        {
            display_name = name;
        }

        int name_len = strlen(display_name);
        int icon_len = visual_len(icon);
        int padding = col_width - name_len - icon_len - 1; // 1 for space between icon and name

        printf("%s%s %s%s", getColor(entries[i].name, entries[i].type), icon, display_name, RESET);
        for (int p = 0; p < padding; p++)
        {
            printf(" ");
        }

        if ((i + 1) % num_cols == 0) printf("\n");
    }
    if (count % num_cols != 0)
    {
       printf("\n");
    }
    closedir(currentDir);
}