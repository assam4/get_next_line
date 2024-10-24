#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"  // Убедись, что у тебя есть этот заголовочный файл

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Не забудь освобождать память
    }

    close(fd);
    return 0;
}

