#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "include/get_next_line.h"

// int open(const char *path, int oflag, ...);
// ssize_t read(int fildes, void *buf, size_t nbyte);

#include <string.h>
#include <stdio.h>
int main()
{
  char  *buf;
  char  *file = malloc(sizeof(char) * 1);
  int   fd;
  size_t    size;

  fd = open("./file1", O_RDONLY);
  while (1)
  {
    if (!(buf = get_next_line(fd)))
      break;

    size = strlen(file) * strlen(buf);
    file = realloc(file, size); 
    strcat(file, buf);
    memset(buf, 0x00, BUFFER_SIZE);
  }
  printf("%s\n", file);
  return 0;
}
