#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>

int   pipe_fd[2];

void  do_child(void)
{
  char *p = "Hello, dad\n";

  printf("This is child.\n");
  // パイプの出口を閉じる
  // 子プロセスにはパイプの入口だけが残る
  close(pipe_fd[0]);

  // パイプに文字列を書き込む
  while (*p)
  {
    if (write(pipe_fd[1], p, 1) < 0)
    {
      perror("rite");
      exit(1);
    }
    p++;
  }
}

void do_parent(void)
{
  char c;
  int count, status;

  printf("This is parent.\n");

  // パイプの入口を閉じる
  // 親プロセスにはパイプの出口だけが残る
  close(pipe_fd[1]);

  // パイプの出口から文字を1バイトずつ読み込んで表示する
  while ((count = read(pipe_fd[0], &c, 1)) > 0)
  {
    putchar(c);
  }

  // readに失敗した時の処理
  if (count < 0)
  {
    perror("read");
    exit(1);
  }

  // 子プロセスが以上終了した時の処理
  if (wait(&status) < 0)
  {
    perror("wait");
    exit(1);
  }
}

int main(void)
{
  int child;

  // パイプを生成
  // この段階ではパイプの入口も出口も同一プロセスにある
  if (pipe(pipe_fd) < 0)
  {
    perror("pipe");
    exit(1);
  }

  // プロセスを複製する
  // この時にパイプも一緒に複製される
  if ((child = fork()) < 0)
  {
    perror("fork");
    exit(1);
  }

  // 親プロセスと子プロセスの判定
  if (child)
  {
    do_parent();
  }
  else
  {
    do_child();
  }

  return 0;
}
