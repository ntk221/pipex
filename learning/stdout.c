#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "include/libft.h"

// int open(const char *path, int oflag, ...);
// ssize_t read(int fildes, void *buf, size_t nbyte);

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int     fd[2];

    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    write(STDOUT_FILENO, "hoge", 5);
}