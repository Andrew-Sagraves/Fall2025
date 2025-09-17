#include "ring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP 20

int main() {
  struct RingBuffer *rb = rb_new(CAP);
  char bytes[CAP];
  size_t n;
  char c;

  rb_push(rb, 'A');
  rb_push(rb, 'l');
  rb_push(rb, 'p');
  rb_push(rb, 'h');
  rb_push(rb, 'a');
  rb_push(rb, 'D');
  rb_push(rb, 'o');
  rb_push(rb, 'g');
  char *buf = malloc(100 * sizeof(char));
  rb_read(rb, buf, 100);
  printf("%s", buf);
  printf("\n");
  rb_ignore(rb, 2);
  char *buf2 = malloc(100 * sizeof(char));
  rb_read(rb, buf2, 100);
  printf("%s", buf2);
  printf("\n");
  /// printf("rb_pop: popped '%c'\n", c);

  /// n = rb_read(rb, bytes, CAP + 5);

  /// printf("rb_read: returned %lu bytes '%.*s'\n", n, n, bytes);

  /// n = rb_write(rb, "Hello World", strlen("Hello World"));

  /// printf("rb_write: wrote %lu bytes.\n", n);

  /// n = rb_read(rb, bytes, CAP);

  /// printf("rb_read: returned %lu bytes '%.*s'\n", n, n, bytes);

  /// rb_free(rb);

  /// return 0;
}
