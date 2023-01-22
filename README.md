# pipex

# 使用可能関数
- open, close, read, write, malloc, free, perror, stderror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid

- ft_peintf

実行例
  ./pipex file1 cmd1 cmd2 file2
以下のコマンドラインと同じように動く
  `$> < file1 cmd1 | cmd2 > file2`
  
# 要件
適切なエラーハンドリングを行う。セグフォ，バスエラーなどを起こさないこと
メモリリークしてはならない
