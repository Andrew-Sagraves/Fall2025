// du.h has been written for you, and it's read only.
#include "du.h"
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct List *build_tree(const char starting_directory[], size_t max_depth) {
  if (max_depth == 0) {
    return NULL;
  }

  DIR *d = opendir(starting_directory);
  if (!d) {
    perror("opendir");
    return NULL;
  }

  struct dirent *dent;
  struct List dummy = {0};    // set 'dummy' to all zeroes
  struct List *prev = &dummy; // tail pointer

  while ((dent = readdir(d)) != NULL) {
    // skip "." and ".."
    if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0) {
      continue;
    }

    // allocate a new node
    struct List *node = malloc(sizeof(struct List));
    if (!node) {
      perror("malloc");
      closedir(d);
      return dummy.next;
    }
    node->next = NULL;
    node->contents = NULL;

    // copy name safely
    node->name = malloc(strlen(dent->d_name) + 1);
    strcpy(node->name, dent->d_name);

    // build full path
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", starting_directory, dent->d_name);

    if (dent->d_type == DT_REG) {
      // regular file
      node->type = File;

      struct stat fileStat;
      if (stat(path, &fileStat) == 0) {
        node->size = fileStat.st_size;
      } else {
        node->size = 0;
      }
    } else if (dent->d_type == DT_DIR) {
      // directory
      node->type = Directory;
      node->size = 0; // will be filled from contents if needed

      // recurse
      node->contents = build_tree(path, max_depth - 1);
    } else {
      // unknown type, skip
      free(node->name);
      free(node);
      continue;
    }

    // link node into list
    prev->next = node;
    prev = node;
  }

  closedir(d);
  return dummy.next;
}

void free_tree(struct List *tree) {
  while (tree != NULL) {
    struct List *next = tree->next;

    if (tree->type == Directory && tree->contents != NULL) {
      free_tree(tree->contents);
    }

    // actually free struct
    free(tree->name);
    free(tree);
    tree = next;
  }
}

size_t disk_usage(const struct List *tree) {
  size_t sum = 0;
  while (tree != NULL) {
    struct List *next = tree->next;

    if (tree->type == Directory && tree->contents != NULL) {
      sum += disk_usage(tree->contents);
    }
    if (tree->type == File) {
      sum += tree->size;
    }
    tree = next;
  }
  return sum;
}
size_t file_size(const struct List *item) {
  size_t sum = 0;
  while (item != NULL) {
    struct List *next = item->next;

    if (item->type == File) {
      sum += item->size;
    }
    item = next;
  }
  return sum;
}
