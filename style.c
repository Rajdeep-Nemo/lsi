#define _DEFAULT_SOURCE
#include "style.h"
#include "colors.h"
#include <dirent.h>
#include <string.h>

// Selects the appropriate icon
char *getIcon(char *name, unsigned char type) {
    // Dierctory
    if (type == DT_DIR)
        return "";

    // Compound extensions first (Done)
    if (strstr(name, ".tar."))
        return "";

    // Get extension for rest (Done)
    char *ext = strrchr(name, '.');
    if (ext == NULL)
        return "";

    // Code / Programming languages (Done)
    if (!strcmp(ext, ".c"))
        return "";
    if (!strcmp(ext, ".h"))
        return "";
    if (!strcmp(ext, ".cpp"))
        return "";
    if (!strcmp(ext, ".hpp"))
        return "";
    if (!strcmp(ext, ".py"))
        return "";
    if (!strcmp(ext, ".js"))
        return "";
    if (!strcmp(ext, ".ts"))
        return "";
    if (!strcmp(ext, ".html"))
        return "";
    if (!strcmp(ext, ".css"))
        return "";
    if (!strcmp(ext, ".java"))
        return "";
    if (!strcmp(ext, ".rs"))
        return "";
    if (!strcmp(ext, ".go"))
        return "";
    if (!strcmp(ext, ".rb"))
        return "";
    if (!strcmp(ext, ".php"))
        return "";

    // Shell / Config (Done)
    if (!strcmp(ext, ".sh"))
        return "";
    if (!strcmp(ext, ".bash"))
        return "";
    if (!strcmp(ext, ".zsh"))
        return "";

    // Documents (Done)
    if (!strcmp(ext, ".txt"))
        return "";
    if (!strcmp(ext, ".md"))
        return "";
    if (!strcmp(ext, ".docx"))
        return "󰧮";
    if (!strcmp(ext, ".doc"))
        return "󰧮";
    if (!strcmp(ext, ".xlsx"))
        return "󰧷";
    if (!strcmp(ext, ".xls"))
        return "󰧷";
    if (!strcmp(ext, ".pptx"))
        return "󰐩";
    if (!strcmp(ext, ".ppt"))
        return "󰐩";

    // Images (Done)
    if (!strcmp(ext, ".png"))
        return "";
    if (!strcmp(ext, ".jpg"))
        return "";
    if (!strcmp(ext, ".jpeg"))
        return "";
    if (!strcmp(ext, ".gif"))
        return "";
    if (!strcmp(ext, ".svg"))
        return "";
    if (!strcmp(ext, ".webp"))
        return "";

    // Video (Done)
    if (!strcmp(ext, ".mp4"))
        return "";
    if (!strcmp(ext, ".mkv"))
        return "";
    if (!strcmp(ext, ".avi"))
        return "";
    if (!strcmp(ext, ".mov"))
        return "";

    // Audio (Done)
    if (!strcmp(ext, ".mp3"))
        return "";
    if (!strcmp(ext, ".wav"))
        return "";
    if (!strcmp(ext, ".flac"))
        return "";
    if (!strcmp(ext, ".ogg"))
        return "";

    // Archives (Done)
    if (!strcmp(ext, ".zip"))
        return "";
    if (!strcmp(ext, ".rar"))
        return "";
    if (!strcmp(ext, ".7z"))
        return "";
    if (!strcmp(ext, ".gz"))
        return "";
    if (!strcmp(ext, ".tar"))
        return "";

    // Binaries (Done)
    if (!strcmp(ext, ".exe"))
        return "";
    if (!strcmp(ext, ".bin"))
        return "";
    if (!strcmp(ext, ".out"))
        return "";
    if (!strcmp(ext, ".so"))
        return "";
    if (!strcmp(ext, ".dll"))
        return "";
    if (!strcmp(ext, ".a"))
        return "";

    // Extra (Done)
    if (!strcmp(ext, ".desktop"))
        return "";
    if (!strcmp(ext, ".ttf"))
        return "󰛖";
    if (!strcmp(ext, ".otf"))
        return "󰛖";

    // Unknown
    return "";
}

// Selects the appropriate color
char *getColor(char *name, unsigned char type) {
    // Dierctory
    if (type == DT_DIR)
        return BLUE;

    // Compound extensions first (Done)
    if (strstr(name, ".tar."))
        return CORAL;

    // Get extension for rest (Done)
    char *ext = strrchr(name, '.');
    if (ext == NULL)
        return RESET;

    // Code / Programming languages (Done)
    if (!strcmp(ext, ".c"))
        return MINT;
    if (!strcmp(ext, ".h"))
        return MINT;
    if (!strcmp(ext, ".cpp"))
        return MINT;
    if (!strcmp(ext, ".hpp"))
        return MINT;
    if (!strcmp(ext, ".py"))
        return MINT;
    if (!strcmp(ext, ".js"))
        return MINT;
    if (!strcmp(ext, ".ts"))
        return MINT;
    if (!strcmp(ext, ".html"))
        return MINT;
    if (!strcmp(ext, ".css"))
        return MINT;
    if (!strcmp(ext, ".java"))
        return MINT;
    if (!strcmp(ext, ".rs"))
        return MINT;
    if (!strcmp(ext, ".go"))
        return MINT;
    if (!strcmp(ext, ".rb"))
        return MINT;
    if (!strcmp(ext, ".php"))
        return MINT;

    // Shell / Config (Done)
    if (!strcmp(ext, ".sh"))
        return ORANGE;
    if (!strcmp(ext, ".bash"))
        return ORANGE;
    if (!strcmp(ext, ".zsh"))
        return ORANGE;

    // Documents (Done)
    if (!strcmp(ext, ".txt"))
        return ICE;
    if (!strcmp(ext, ".md"))
        return ICE;
    if (!strcmp(ext, ".docx"))
        return ICE;
    if (!strcmp(ext, ".doc"))
        return ICE;
    if (!strcmp(ext, ".xlsx"))
        return ICE;
    if (!strcmp(ext, ".xls"))
        return ICE;
    if (!strcmp(ext, ".pptx"))
        return ICE;
    if (!strcmp(ext, ".ppt"))
        return ICE;
    if (!strcmp(ext, ".pdf"))
        return ICE;

    // Images (Done)
    if (!strcmp(ext, ".png"))
        return MAGENTA;
    if (!strcmp(ext, ".jpg"))
        return MAGENTA;
    if (!strcmp(ext, ".jpeg"))
        return MAGENTA;
    if (!strcmp(ext, ".gif"))
        return MAGENTA;
    if (!strcmp(ext, ".svg"))
        return MAGENTA;
    if (!strcmp(ext, ".webp"))
        return MAGENTA;

    // Video (Done)
    if (!strcmp(ext, ".mp4"))
        return PURPLE;
    if (!strcmp(ext, ".mkv"))
        return PURPLE;
    if (!strcmp(ext, ".avi"))
        return PURPLE;
    if (!strcmp(ext, ".mov"))
        return PURPLE;

    // Audio (Done)
    if (!strcmp(ext, ".mp3"))
        return PINK;
    if (!strcmp(ext, ".wav"))
        return PINK;
    if (!strcmp(ext, ".flac"))
        return PINK;
    if (!strcmp(ext, ".ogg"))
        return PINK;

    // Archives (Done)
    if (!strcmp(ext, ".zip"))
        return CORAL;
    if (!strcmp(ext, ".rar"))
        return CORAL;
    if (!strcmp(ext, ".7z"))
        return CORAL;
    if (!strcmp(ext, ".gz"))
        return CORAL;
    if (!strcmp(ext, ".tar"))
        return CORAL;

    // Binaries (Done)
    if (!strcmp(ext, ".exe"))
        return CRIMSON;
    if (!strcmp(ext, ".bin"))
        return CRIMSON;
    if (!strcmp(ext, ".out"))
        return CRIMSON;
    if (!strcmp(ext, ".so"))
        return CRIMSON;
    if (!strcmp(ext, ".dll"))
        return CRIMSON;
    if (!strcmp(ext, ".a"))
        return CRIMSON;
    if (!strcmp(ext, ".rpm"))
        return CRIMSON;

    // Extra (Done)
    if (!strcmp(ext, ".desktop"))
        return WHITE;
    if (!strcmp(ext, ".ttf"))
        return WHITE;
    if (!strcmp(ext, ".otf"))
        return WHITE;

    // Unknown
    return RESET;
}