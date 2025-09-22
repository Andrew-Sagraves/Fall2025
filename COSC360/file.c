#include <stdio.h>

int main() {
  FILE *fl;
  char buf[256];
  int val = 255;
  fl = fopen("filename.bin", "wb");

  size_t a = fwrite(&val, 1, sizeof(int), fl);

  if (a != sizeof(int)) {
    printf("error");
  }
}
