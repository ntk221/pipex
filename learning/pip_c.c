#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char word[256];
    int n, rfd, wfd;

    rfd = atoi(argv[1]);
    wfd = atoi(argv[2]);

    read(rfd, word, sizeof(word));

    n = strlen(word);
    sleep(10);
    write(wfd, &n, sizeof(n));

    close(rfd);
    close(wfd);
    return 0;
}