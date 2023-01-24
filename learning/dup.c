#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* https://www.geeksforgeeks.org/dup-dup2-linux-system-call/ */

int main()
{
  int fd = open("dup.txt", O_WRONLY | O_APPEND);
  if (fd < 0)
    fprintf(stderr, "Error\n");

  int copy_desc = dup(fd);

  write(copy_desc, "This will be output to the file named dup.txt\n", 46);
  write(fd, "This will also be output to the file named dup.txt\n", 51);
}
