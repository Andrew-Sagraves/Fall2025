#include <math.h>
#include <stdio.h>

struct Point {
  int x;
  int y;
};
double distance(const struct Point *p1, const struct Point *p2) {
  return sqrt(pow(p1->x + p2->x, 2) + pow(p1->y + p2->y, 2));
}

int main(int argc, char **argv) {
  if (argc != 5) {
    printf("NONONONO\n");
    return 1;
  }
  int num;
  double strength, atten;
  int x, y;

  // take in input from argv
  num = sscanf(argv[1], "%lf", &strength);
  if (num != 1) {
    return 1;
  }
  num = sscanf(argv[2], "%lf", &atten);
  if (num != 1) {
    return 1;
  }
  num = sscanf(argv[3], "%d", &x);
  if (num != 1) {
    return 1;
  }
  num = sscanf(argv[4], "%d", &y);

  int x2, y2;
  char name[33];

  // take in input from cin
  while (scanf("%d %d %32s", &x2, &y2, name) == 3) {
    struct Point one = {x, y};
    struct Point two = {x2, y2};
  printf("%8s: %lf Sv\n", name, strength * pow(distance(&one, &two), atten));  

  }
  return 0;
}
