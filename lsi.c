#define _DEFAULT_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "colors.h"

char *getIcon (char *name , unsigned char type) {
    // Dierctory
    if (type == DT_DIR) return "";

    // Compound extensions first (Done)
    if (strstr(name, ".tar."))        return "";

    // Get extension for rest (Done)
    char *ext = strrchr(name, '.');
    if (ext == NULL) return "";

    // Code / Programming languages (Done)
    if (!strcmp(ext, ".c"))           return "";
    if (!strcmp(ext, ".h"))           return "";
    if (!strcmp(ext, ".cpp"))         return "";
    if (!strcmp(ext, ".hpp"))         return "";
    if (!strcmp(ext, ".py"))          return "";
    if (!strcmp(ext, ".js"))          return "";
    if (!strcmp(ext, ".ts"))          return "";
    if (!strcmp(ext, ".html"))        return "";
    if (!strcmp(ext, ".css"))         return "";
    if (!strcmp(ext, ".java"))        return "";
    if (!strcmp(ext, ".rs"))          return "";
    if (!strcmp(ext, ".go"))          return "";
    if (!strcmp(ext, ".rb"))          return "";
    if (!strcmp(ext, ".php"))         return "";

    // Shell / Config (Done)
    if (!strcmp(ext, ".sh"))          return "";
    if (!strcmp(ext, ".bash"))        return "";
    if (!strcmp(ext, ".zsh"))         return "";

    // Documents (Done)
    if (!strcmp(ext, ".txt"))         return "";
    if (!strcmp(ext, ".md"))          return "";
    if (!strcmp(ext, ".docx"))        return "󰧮";
    if (!strcmp(ext, ".doc"))         return "󰧮";
    if (!strcmp(ext, ".xlsx"))        return "󰧷";
    if (!strcmp(ext, ".xls"))         return "󰧷";
    if (!strcmp(ext, ".pptx"))        return "󰐩";
    if (!strcmp(ext, ".ppt"))         return "󰐩";

    // Images (Done)
    if (!strcmp(ext, ".png"))         return "";
    if (!strcmp(ext, ".jpg"))         return "";
    if (!strcmp(ext, ".jpeg"))        return "";
    if (!strcmp(ext, ".gif"))         return "";
    if (!strcmp(ext, ".svg"))         return "";
    if (!strcmp(ext, ".webp"))        return "";

    // Video (Done)
    if (!strcmp(ext, ".mp4"))         return "";
    if (!strcmp(ext, ".mkv"))         return "";
    if (!strcmp(ext, ".avi"))         return "";
    if (!strcmp(ext, ".mov"))         return "";

    // Audio (Done)
    if (!strcmp(ext, ".mp3"))         return "";
    if (!strcmp(ext, ".wav"))         return "";
    if (!strcmp(ext, ".flac"))        return "";
    if (!strcmp(ext, ".ogg"))         return "";

    // Archives (Done)
    if (!strcmp(ext, ".zip"))         return "";
    if (!strcmp(ext, ".rar"))         return "";
    if (!strcmp(ext, ".7z"))          return "";
    if (!strcmp(ext, ".gz"))          return "";
    if (!strcmp(ext, ".tar"))         return "";

    // Binaries (Done)
    if (!strcmp(ext, ".exe"))         return "";
    if (!strcmp(ext, ".bin"))         return "";
    if (!strcmp(ext, ".out"))         return "";
    if (!strcmp(ext, ".so"))          return "";
    if (!strcmp(ext, ".dll"))         return "";
    if (!strcmp(ext, ".a"))           return "";

    // Extra (Done)
    if (!strcmp(ext, ".desktop"))     return "";

    // Unknown
    return "";
}
char *getColor (char *name , unsigned char type) {
    // Dierctory
    if (type == DT_DIR) return BRIGHT_BLUE;

    // Compound extensions first (Done)
    if (strstr(name, ".tar."))        return RED;

    // Get extension for rest (Done)
    char *ext = strrchr(name, '.');
    if (ext == NULL) return RESET;

    // Code / Programming languages (Done)
    if (!strcmp(ext, ".c"))           return BRIGHT_GREEN;
    if (!strcmp(ext, ".h"))           return BRIGHT_GREEN;
    if (!strcmp(ext, ".cpp"))         return BRIGHT_GREEN;
    if (!strcmp(ext, ".hpp"))         return BRIGHT_GREEN;
    if (!strcmp(ext, ".py"))          return BRIGHT_GREEN;
    if (!strcmp(ext, ".js"))          return BRIGHT_GREEN;
    if (!strcmp(ext, ".ts"))          return BRIGHT_GREEN;
    if (!strcmp(ext, ".html"))        return BRIGHT_GREEN;
    if (!strcmp(ext, ".css"))         return BRIGHT_GREEN;
    if (!strcmp(ext, ".java"))        return BRIGHT_GREEN;
    if (!strcmp(ext, ".rs"))          return BRIGHT_GREEN;
    if (!strcmp(ext, ".go"))          return BRIGHT_GREEN;
    if (!strcmp(ext, ".rb"))          return BRIGHT_GREEN;
    if (!strcmp(ext, ".php"))         return BRIGHT_GREEN;

    // Shell / Config (Done)
    if (!strcmp(ext, ".sh"))          return BRIGHT_YELLOW;
    if (!strcmp(ext, ".bash"))        return BRIGHT_YELLOW;
    if (!strcmp(ext, ".zsh"))         return BRIGHT_YELLOW;

    // Documents (Done)
    if (!strcmp(ext, ".txt"))         return BRIGHT_WHITE;
    if (!strcmp(ext, ".md"))          return BRIGHT_WHITE;
    if (!strcmp(ext, ".docx"))        return BRIGHT_WHITE;
    if (!strcmp(ext, ".doc"))         return BRIGHT_WHITE;
    if (!strcmp(ext, ".xlsx"))        return BRIGHT_WHITE;
    if (!strcmp(ext, ".xls"))         return BRIGHT_WHITE;
    if (!strcmp(ext, ".pptx"))        return BRIGHT_WHITE;
    if (!strcmp(ext, ".ppt"))         return BRIGHT_WHITE;

    // Images (Done)
    if (!strcmp(ext, ".png"))         return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".jpg"))         return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".jpeg"))        return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".gif"))         return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".svg"))         return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".webp"))        return BRIGHT_MAGENTA;

    // Video (Done)
    if (!strcmp(ext, ".mp4"))         return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".mkv"))         return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".avi"))         return BRIGHT_MAGENTA;
    if (!strcmp(ext, ".mov"))         return BRIGHT_MAGENTA;

    // Audio (Done)
    if (!strcmp(ext, ".mp3"))         return BRIGHT_CYAN;
    if (!strcmp(ext, ".wav"))         return BRIGHT_CYAN;
    if (!strcmp(ext, ".flac"))        return BRIGHT_CYAN;
    if (!strcmp(ext, ".ogg"))         return BRIGHT_CYAN;

    // Archives (Done)
    if (!strcmp(ext, ".zip"))         return RED;
    if (!strcmp(ext, ".rar"))         return RED;
    if (!strcmp(ext, ".7z"))          return RED;
    if (!strcmp(ext, ".gz"))          return RED;
    if (!strcmp(ext, ".tar"))         return RED;

    // Binaries (Done)
    if (!strcmp(ext, ".exe"))         return BRIGHT_RED;
    if (!strcmp(ext, ".bin"))         return BRIGHT_RED;
    if (!strcmp(ext, ".out"))         return BRIGHT_RED;
    if (!strcmp(ext, ".so"))          return BRIGHT_RED;
    if (!strcmp(ext, ".dll"))         return BRIGHT_RED;
    if (!strcmp(ext, ".a"))           return BRIGHT_RED;

    // Extra (Done)
    if (!strcmp(ext, ".desktop"))     return WHITE;

    // Unknown
    return RESET;
}
int main(void){
    DIR * currentDir = opendir(".");

    struct dirent *entry;

    while((entry = readdir(currentDir)) != NULL){

        if (!strcmp(entry->d_name,".") || !strcmp(entry->d_name,".."))
        {
            continue;
        }

        printf("%s%s  %s%s\n",
                getColor(entry->d_name, entry->d_type),  // color
                getIcon(entry->d_name, entry->d_type),   // icon
                entry->d_name,                           // name
                RESET                                    // reset
        );
    }

    closedir(currentDir);
}