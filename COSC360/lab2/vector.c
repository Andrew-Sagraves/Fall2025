#include "vector.h"

#include <search.h>
#include <stdlib.h>
#include <string.h>

// struct definition
typedef struct Vector {
  size_t size;
  size_t capacity;
  int64_t *values;
} Vector;

int comparator(const void *l, const void *r) { return *(int *)l - *(int *)r; }

// Write your vector functions here.
// int main() is written in main.c
// You can navigate files to the left of this window.

// returns a new vector
Vector *vector_new(void) {
  Vector *a = (Vector *)malloc(sizeof(Vector));
  a->size = 0;
  a->capacity = 0;
  a->values = malloc(0);
  return a;
}

// returns a new vector with a specified capacity
Vector *vector_new_with_capacity(size_t capacity) {
  Vector *a = (Vector *)malloc(sizeof(Vector));
  a->values = malloc(capacity * sizeof(int64_t));
  a->capacity = capacity;
  a->size = 0;
  return a;
}

// frees the vector
void vector_free(Vector *vec) {
  free(vec->values);
  free(vec);
}

void vector_shrink(Vector *vec) {
  vec->values = realloc(vec->values, vec->size * sizeof(int64_t));
  vec->capacity = vec->size;
}

// resizes capacity of vector. helper function for vector_resize
void vector_reserve(Vector *vec, size_t new_capacity) {
  vec->values = realloc(vec->values, new_capacity * sizeof(int64_t));
  vec->capacity = new_capacity;
}

// resizes size of vector. helper function for vector_resize
void vector_resize(Vector *vec, size_t new_size) {
  if (new_size <= vec->capacity) {
    vec->size = new_size;
  } else {
    vector_reserve(vec, new_size);
    vec->size = new_size;
  }
}

// pushes a value to a vector. helper function for vector_insert
void vector_push(Vector *vec, int64_t value) {
  vector_resize(vec, vec->size + 1);
  vec->values[vec->size - 1] = value;
}
bool vector_remove(Vector *vec, size_t index) {
  if (index < vec->size) {
    memmove(&vec->values[index], &vec->values[index + 1],
            (vec->size - index - 1) * sizeof(int64_t));
    vector_resize(vec, vec->size - 1);
    return true;
  }
  return false;
}
// inserts value into a vector
void vector_insert(Vector *vec, size_t index, int64_t value) {
  // we push no matter what. if insert is inside vector, do the for loop
  if (vec->size >= vec->capacity) {
    vector_reserve(vec, vec->size + 1);
  }
  if (index >= vec->size) {
    vector_push(vec, value);
  } else {
    memmove(&vec->values[index + 1], &vec->values[index], (vec->size - index) * sizeof(int64_t));
    vec->values[index] = value;
    vec->size += 1;
  }
}
// returns the size of the vector
size_t vector_size(const Vector *vec) { return vec->size; }

bool vector_get(const Vector *vec, size_t index, int64_t *value) {
  if (index < vec->size) {
    *value = vector_get_unchecked(vec, index);
    return true;
  }
  return false;
}
int64_t vector_get_unchecked(const Vector *vec, size_t index) { return vec->values[index]; }
bool vector_set(Vector *vec, size_t index, int64_t value) {
  if (index < vec->size) {
    vec->values[index] = value;
    return true;
  }
  return false;
}

// calls vector_sort_by
void vector_sort(Vector *vec) { vector_sort_by(vec, comparator); }

void vector_sort_by(Vector *vec, SortFunc comp) {
  qsort(vec->values, vec->size, sizeof(int64_t), comp);
}
ssize_t vector_find(const Vector *vec, int64_t value) {
  size_t size = (size_t)vec->size;
  ssize_t *i = lfind(&value, vec->values, &size, sizeof(int64_t), comparator);
  if (i == NULL) {
    return -1;
  }
  return (i - vec->values);
}
ssize_t vector_bsearch(const Vector *vec, int64_t value) {
  size_t size = (size_t)vec->size;
  ssize_t *i = bsearch(&value, vec->values, size, sizeof(int64_t), comparator);
  if (i == NULL) {
    return -1;
  }
  return (i - vec->values);
}

void vector_clear(Vector *vec) {
 vec->size = 0;
}
size_t vector_capacity(const Vector *vec) { return vec->capacity; }

