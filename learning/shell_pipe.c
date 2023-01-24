#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int get_arg2(char *c, char *arg[], char *sym);

int main()
{
    pid_t pid;
    char line[256], command[256], *divcom[32], *arg_c1[32], *arg_c2[32];
    int st, i = 0, ret1, ret2, ret3, ret4, fd[2];

    while(1)
    {
        fprintf(stderr, "-->");
        fgets(line, sizeof(line), stdin);
        // printf("%s\n", line);
        ret1 = sscanf(line, "%[^\n]", command);
        // printf("%s\n", command);
        if(ret1 > 0)
        {
            // puts("hoge");
            ret2 = get_arg2(command, divcom, "|");
            if (ret2 == 1)
            {
                // puts("huga");
                get_arg2(divcom[0], arg_c1, " ");
                pid = fork();
                if (pid == 0)
                {
                    // printf("%s\n", arg_c1[0]);
                    ret3 = execv(arg_c1[0], arg_c1);
                    if (ret3 < 0)
                        exit(0);
                }
                else
                    wait(&st);
            }
            else if (ret2 == 2)
            {
                get_arg2(divcom[0], arg_c1, " ");
                get_arg2(divcom[1], arg_c2, " ");

                ret3 = pipe(fd);
                if (ret3 < 0)
                {
                    perror("pipe");
                    exit(1);
                }
                pid = fork();
                if (pid == 0) // 一つ目のコマンド実行用のプロセス
                {
                    close(fd[0]); 
                    dup2(fd[1], STDOUT_FILENO); // 書き込み用バッファに書き込む
                    ret4 =  execv(arg_c1[0], arg_c1);
                    if (ret4 < 0)
                        exit(0);
                }
                pid = fork(); // 2つ目のコマンド実行用のプロセス
                if (pid == 0)
                {
                    close(fd[1]); // 書き込みようのバッファは要らないのでclose
                    dup2(fd[0], STDIN_FILENO); // バッファから読み込む
                    ret4 = execv(arg_c2[0], arg_c2);
                    if (ret4 < 0)
                        exit(0);
                }
                close(fd[0]);
                close(fd[1]);
                wait(&st);
                wait(&st);
            }
        }
    }
    return 0;
}

int get_arg2(char *c, char *arg[], char *sym)
{
    int i = 0;
    arg[i] = strtok(c, sym);
    while(arg[i] != NULL)
    {
        i++;
        arg[i] = strtok(NULL, sym);
    }
    return i;
}