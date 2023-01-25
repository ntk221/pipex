#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int get_path(char *dir[]);

int main()
{
    pid_t pid;
    int ret, st, i=0;
    char line[256], command[256], path[512], *dir[64];

    get_path(dir);

    while(1)
    {
        fprintf(stderr, "-->");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%s", command);
        pid = fork();
        if (pid == 0)
        {
            ret = execl(command, command, NULL);
            if (ret < 0) // command は 絶対パスが付いてなかったから実行できなかったと考える
            {
                for (i = 0; dir[i] != NULL; i++)
                {
                    sprintf(path, "%s/%s", dir[i], command); // dir[i] に "/" と command を連結して path に代入して，path を execlで実行する
                    execl(path, path, NULL);
                }
                exit(0);
            }
        }
        else
            wait(&st);
    }
    return 0;
}

int get_path(char *dir[])
{
    char *env;
    int i = 0;
    env = getenv("PATH");
    dir[i] = strtok(env, ":");
    while(dir[i] != NULL)
    {
        i++;
        dir[i] = strtok(NULL, ":");
    }
    return i;
}