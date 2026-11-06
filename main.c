#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;

    fd = open("text.txt", O_RDWR);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
}
