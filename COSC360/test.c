#include <stdio.h>
#include <unistd.h>

int main() {
  char buffer[256];
  getcwd(buffer, 255);
  printf("CWD = %s\n", buffer);
  return 0;
}
