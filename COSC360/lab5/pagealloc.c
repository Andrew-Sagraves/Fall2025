#include "pagealloc.h"
#include <stdlib.h>
#include <sys/mman.h>
// global vars

void *start = NULL;
size_t page_count = 0;
size_t used_pages = 0;

// bitwise operations used for testing and setting bits
bool test_bit(char bitset, int index) { return (bitset >> index) & 1; }

void set_bit(char *bitset, int index) { *bitset |= 1 << index; }

void clear_bit(char *bitset, int index) { *bitset &= ~(1 << index); }

// round_up for bookeeping bytes
size_t round_up(size_t num, size_t n) { return ((num + n - 1) / n) * n; }

// NOTES::
//
// bookkeeping placed before pool pages

// this function initializes how many pages we need
bool page_init(size_t pages) {
  if (pages > 262144) {
    return false;
  }
  if (pages < 2) {
    return false;
  }

  // get how many pages total we need to initialize
  size_t book_bytes = round_up(pages / 4, 4096);
  size_t book_pages = (book_bytes / 16384) + 1;
  used_pages = pages + book_pages;
  size_t page_bytes = (used_pages)*4096;
  if (posix_memalign(&start, 4096, page_bytes) == 0) {
    return true;
  }
  return false;
}
void page_deinit(void) {
  munmap(start, used_pages * 4096);
  used_pages = 0;
}

void *page_alloc(size_t pages) {

  // if pages >= any free pages, return NULL
  if (pages <= 0)
    return NULL;

  size_t i = 0;
  char byte = *(char *)start;
  while (!test_bit(byte, i % 4)) {
    i += 1;
    byte = *(char *)(start + (i / 4));
  }
}
void page_free(void *addr) {
  if (addr != NULL)
    return;
  return;
}

size_t pages_taken(void) { return 0; }
size_t pages_free(void) { return 0; }
