#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define PATH_SIZE 4096
#define CHUNK_SIZE 1024
 
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
  char buffer[CHUNK_SIZE];
  size_t bytes_read;

  while (--argc > 0) {    
    snprintf(pathname, PATH_SIZE, "%s", *(++argv));
    FILE *fptr = fopen(pathname, "r");  
    if (fptr == NULL) {
      fprintf(stderr, "Failed to open file '%s'\n", pathname);
      continue;
    }
    
    printf(ANSI_COLOR_BLUE "\n\n%s\n" ANSI_COLOR_RESET "\n", pathname);
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, fptr)) > 0) {
      // Print the buffer we just read
      print_buffer(buffer, bytes_read);
    }

    // Close file after reading
    fclose(fptr);
  }
  
  return 0;
}

void print_buffer(const char *buffer, size_t bytes)
{
  // Write the binary data directly to stdout
  fwrite(buffer, 1, bytes, stdout);
};