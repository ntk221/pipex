#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int     infile;
    pid_t   pid;
    int     pipefd[2];
 
    pid = fork();
    if (pid == 0) //子プロセス
    {
        infile = open("test.txt", O_RDONLY);
        dup2(infile, 0);
        execl("/bin/cat", "cat", NULL);
        perror("/bin/cat");
        exit(1);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("exit status=%d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("signal sig=%d\n", WTERMSIG(status));
        else
            printf("abnormal exit\n");
        exit(0);
    }
}