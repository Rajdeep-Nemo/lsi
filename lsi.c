#include <stdio.h>
#include <dirent.h>
#include <string.h>

char *getIcon(char *name) {

    // Special filenames (no extension)
    if (!strcmp(name, "Makefile"))    return "";
    if (!strcmp(name, "Dockerfile"))  return "";
    if (!strcmp(name, ".git"))  return "";
    if (!strcmp(name, ".gitignore"))  return "";

    // Compound extensions first
    if (strstr(name, ".tar."))        return "";

    // Get extension for rest
    char *ext = strrchr(name, '.');
    if (ext == NULL) return "";

    // Code / Programming languages
    if (!strcmp(ext, ".c"))           return "󰙱";
    if (!strcmp(ext, ".h"))           return "󰰀";
    if (!strcmp(ext, ".cpp"))         return "󰙲";
    if (!strcmp(ext, ".hpp"))         return "󰰀󰰘󰰘";
    if (!strcmp(ext, ".py"))          return "󰌠";
    if (!strcmp(ext, ".js"))          return "";
    if (!strcmp(ext, ".ts"))          return "";
    if (!strcmp(ext, ".html"))        return "";
    if (!strcmp(ext, ".css"))         return "";
    if (!strcmp(ext, ".java"))        return "";
    if (!strcmp(ext, ".rs"))          return "";
    if (!strcmp(ext, ".go"))          return "󰟓";
    if (!strcmp(ext, ".rb"))          return "";
    if (!strcmp(ext, ".php"))         return "";

    // Shell / Config
    if (!strcmp(ext, ".sh"))          return "";
    if (!strcmp(ext, ".bash"))        return "";
    if (!strcmp(ext, ".zsh"))         return "";
    if (!strcmp(ext, ".json"))        return "";
    if (!strcmp(ext, ".yaml"))        return "";
    if (!strcmp(ext, ".yml"))         return "";
    if (!strcmp(ext, ".toml"))        return "";
    if (!strcmp(ext, ".env"))         return "";
    if (!strcmp(ext, ".ini"))         return "";
    if (!strcmp(ext, ".cfg"))         return "";

    // Documents
    if (!strcmp(ext, ".txt"))         return "";
    if (!strcmp(ext, ".md"))          return "";
    if (!strcmp(ext, ".pdf"))         return "";
    if (!strcmp(ext, ".docx"))        return "";
    if (!strcmp(ext, ".doc"))         return "";
    if (!strcmp(ext, ".xlsx"))        return "";
    if (!strcmp(ext, ".xls"))         return "";
    if (!strcmp(ext, ".pptx"))        return "";
    if (!strcmp(ext, ".ppt"))         return "";
    if (!strcmp(ext, ".csv"))         return "";

    // Images
    if (!strcmp(ext, ".png"))         return "";
    if (!strcmp(ext, ".jpg"))         return "";
    if (!strcmp(ext, ".jpeg"))        return "";
    if (!strcmp(ext, ".gif"))         return "";
    if (!strcmp(ext, ".svg"))         return "";
    if (!strcmp(ext, ".webp"))        return "";

    // Video
    if (!strcmp(ext, ".mp4"))         return "";
    if (!strcmp(ext, ".mkv"))         return "";
    if (!strcmp(ext, ".avi"))         return "";
    if (!strcmp(ext, ".mov"))         return "";

    // Audio
    if (!strcmp(ext, ".mp3"))         return "";
    if (!strcmp(ext, ".wav"))         return "";
    if (!strcmp(ext, ".flac"))        return "";
    if (!strcmp(ext, ".ogg"))         return "";

    // Archives
    if (!strcmp(ext, ".zip"))         return "";
    if (!strcmp(ext, ".rar"))         return "";
    if (!strcmp(ext, ".7z"))          return "";
    if (!strcmp(ext, ".gz"))          return "";
    if (!strcmp(ext, ".tar"))         return "";

    // Binaries
    if (!strcmp(ext, ".exe"))         return "";
    if (!strcmp(ext, ".bin"))         return "";
    if (!strcmp(ext, ".out"))         return "";
    if (!strcmp(ext, ".so"))          return "";
    if (!strcmp(ext, ".dll"))         return "";
    if (!strcmp(ext, ".a"))           return "";

    // Unknown
    return "";
}

int main(void){
    DIR * currentDir = opendir(".");

    struct dirent *entry;

    while((entry = readdir(currentDir)) != NULL){
        if (!strcmp(entry->d_name,".") || !strcmp(entry->d_name,".."))
        {
            continue;
        }

        if (entry->d_type == 8) // Regular file
        {
            printf(" %s %s\n",getIcon(entry->d_name),entry->d_name);
        }
        else if (entry->d_type == 4) // Dierctory
        {
            printf("  %s\n",entry->d_name);
        }
        else
        {
            printf(" ? %s\n",entry->d_name);
        }
    }

    closedir(currentDir);
}