#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>
#include <io.h>

size_t read_from_file(const char *const file_name, char *buffer) {
  int fd=open(file_name, O_RDONLY);
  if(fd == -1) exit(80);
  off_t raw_bytes=lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  ssize_t bytes_read=read(fd, buffer, raw_bytes);
  if (bytes_read != raw_bytes) {
    perror("File not read\n");
  }
  buffer[bytes_read]='\0';
  close(fd);
  return bytes_read;
}
