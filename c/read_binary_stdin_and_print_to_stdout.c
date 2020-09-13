#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char* entire_stdin = 0;
  int entire_stdin_length = 0;
  int this_read;
  char buffer[1024];

  while(this_read = fread(buffer, sizeof(char), sizeof(buffer), stdin)) {

    entire_stdin = realloc(entire_stdin, entire_stdin_length + this_read);
    if(!entire_stdin) {
      fprintf(stderr, "Failed to malloc %d bytes for stdin\n", entire_stdin_length + this_read);
      exit(1);
    }

    memcpy(&(entire_stdin[entire_stdin_length]), buffer, this_read);
    entire_stdin_length += this_read;

  }

  if(!entire_stdin_length) {
    fprintf(stderr, "Stdin did not deliver a single byte\n");
    exit(1);
  }
  entire_stdin[entire_stdin_length] = '\0'; // Should be the case anyway

  if(!feof(stdin)) {
    fprintf(stderr, "fread(stdin) resulted in a non-EOF error\n");
    exit(1);
  }
  
  fprintf(stderr, "Length of input is %d \n", entire_stdin_length);

  // Write the stdin to stdout

  fwrite(entire_stdin, 1, entire_stdin_length, stdout);

  // This just makes it print out before the end of the program
  fflush(stdout);

  }
