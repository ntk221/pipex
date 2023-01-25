#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    for(char **ep = envp; *ep != NULL; ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);
}