#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define PATH_SIZE 4096
#define BUFF_SIZE 1024
 
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_buffer(const char *buffer, size_t bytes);

int main(int argc, char *argv[]) {
  char pathname[PATH_SIZE];
  char buff[BUFF_SIZE];
  size_t bytes_read;

  while (--argc > 0) {    
    snprintf(pathname, PATH_SIZE, "%s", *(++argv));
    int fd = open(pathname, O_RDONLY);  
    if (fd == -1) {
      fprintf(stderr, "\nFailed to open file '%s'\n", pathname);
      continue;
    }
    
    printf(ANSI_COLOR_BLUE "\n\n%s\n" ANSI_COLOR_RESET "\n", pathname);
    while ((bytes_read = read(fd, buff, BUFF_SIZE)) > 0) {
      // Print the buffer we just read
      print_buffer(buff, bytes_read);
    }

    // Close file after reading
    close(fd);
  }
  
  return 0;
}

void print_buffer(const char *buffer, size_t bytes)
{
  // Write the binary data directly to stdout
  fwrite(buffer, 1, bytes, stdout);
};
