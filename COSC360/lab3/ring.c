#include "ring.h"
#include <string.h>
typedef struct RingBuffer {
  size_t at;       // index of next byte
  size_t size;     // total number of unread bytes
  size_t capacity; // total number of bytes in this buffer
  char *buffer;    // data storage, use calloc() with capacity

} RingBuffer;

RingBuffer *rb_new(size_t capacity) {
  struct RingBuffer *rb = malloc(sizeof(RingBuffer));
  rb->at = 0;
  rb->size = 0;
  rb->capacity = capacity;
  rb->buffer = calloc(capacity, sizeof(size_t));
  return rb;
}
void rb_free(RingBuffer *rb) {
  free(rb->buffer);
  free(rb);
}

// Ring buffer components
size_t rb_at(const RingBuffer *rb) { return rb->at; }

size_t rb_size(const RingBuffer *rb) { return rb->size; }

size_t rb_capacity(const RingBuffer *rb) { return rb->capacity; }

bool rb_push(RingBuffer *rb, char data) {
  if (rb_size(rb) >= rb_capacity(rb)) {
    return false;
  }
  int slot = (rb_at(rb) + rb_size(rb)) % rb_capacity(rb);
  rb->buffer[slot] = data;
  rb->size += 1;
  return true;
}
bool rb_pop(RingBuffer *rb, char *data) {
  if (rb->size <= 0) {
    return false;
  }
  *data = rb->buffer[rb_at(rb)];
  rb->at += 1;
  rb->size -= 1;
  return true;
}
char rb_peek(const RingBuffer *rb) { return rb->buffer[rb_at(rb)]; }

void rb_ignore(RingBuffer *rb, size_t num) {
  if (num > rb->size) {
    num = rb->size;
  }
  rb->at = (rb->at + num) % rb->capacity;
  rb->size -= num;
}
void rb_clear(RingBuffer *rb) {
  rb->at = 0;
  rb->size = 0;
}

size_t rb_read(RingBuffer *rb, char *buf, size_t max_bytes) {
  if (max_bytes >= rb->size) {
    max_bytes = rb->size;
  }

  if (rb->at + max_bytes > rb->capacity) {
    int rest = rb->at + max_bytes - rb->capacity;
    int init = rb->capacity - rb->at;

    memcpy(buf, rb->buffer + rb->at, init * sizeof(char));
    memcpy(buf + init, rb->buffer, rest * sizeof(char));
    return max_bytes;
  }

  memcpy(buf, rb->buffer + rb->at, max_bytes * sizeof(char));
  return max_bytes;
}
size_t rb_write(struct RingBuffer *rb, const char *buf, size_t max_bytes) {

  if (max_bytes + rb->size >= rb->capacity) {
    max_bytes = rb->capacity - rb->size;
  }

  int start = rb->at + rb->size % rb->capacity;

  if (start + max_bytes > rb->capacity) {
    int rest = start + max_bytes - rb->capacity;
    int init = rb->capacity - start;

    memcpy(rb->buffer + start, buf, init * sizeof(char));
    memcpy(rb->buffer, buf + init, rest * sizeof(char));
    return max_bytes;
  }

  memcpy(rb->buffer + start, buf, max_bytes * sizeof(char));
  return max_bytes;
}
