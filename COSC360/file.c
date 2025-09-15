#include <stdio.h>

int main() {
  FILE *fl;

  fl = fopen("filename.txt", "r");

  if (fl == NULL) {
    perror("filename.txt");
    return 1;
  }

  fprintf(stderr, "hello World\n");

  fclose(fl);
}
