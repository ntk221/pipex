#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int     infile;

    infile = open("test.txt", O_RDONLY);
    dup2(infile, 0);
    // close(0);

    execl("/bin/cat", "cat", NULL);
}