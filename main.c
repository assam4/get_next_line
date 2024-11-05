#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"  // Убедись, что у тебя есть этот заголовочный файл

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("MAIN Line: %s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}

