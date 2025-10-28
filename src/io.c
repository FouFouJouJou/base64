#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>
#include <io.h>

size_t read_from_file(const char *const file_name, uint8_t *buffer) {
  int fd=open(file_name, O_RDONLY);
  if(fd == -1) {
    exit(80);
  }
  off_t raw_bytes=lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  ssize_t bytes_read=read(fd, buffer, raw_bytes);
  buffer[bytes_read]='\0';
  printf("%s\n", (char*) buffer);
  close(fd);
  return bytes_read;
}
