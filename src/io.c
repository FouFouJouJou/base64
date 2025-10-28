#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <io.h>


size_t read_from_file(char *file_name, char **buff) {
  FILE *fd=fopen(file_name, "rb");
  if (!fd) {
    exit(2);
  }
  fseek(fd, 0L, SEEK_END);
  size_t size=ftell(fd);
  *buff=malloc(sizeof(char)*size);
  rewind(fd);
  fread(*buff, size, 1, fd);
  fclose(fd);
  return size;
}
