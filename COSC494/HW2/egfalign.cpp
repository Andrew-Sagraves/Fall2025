// Andrew Sagraves
// sources: chatGPT (manual memory allocation for 2d array), Professor Emrich

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int MATCH = 2;
const int MISMATCH = -1;
const int GAP = -2;

// determines if two chars are the same or different
int compareChars(char a, char b) { return (a == b) ? MATCH : MISMATCH; }

// returns the most optimal number
int returnMax(int a, int b, int c) { return max({a, b, c}); }

// prints board; used for debugging
void print(int **grid, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] >= 0) {
        cout << ' ' << grid[i][j] << ' ';
      } else {
        cout << grid[i][j] << ' ';
      }
    }
    cout << '\n';
  }
}

// initialize first row/column with gap penalties
void initialize(int **grid, int rows, int columns) {
  grid[0][0] = 0;

  for (int i = 1; i < rows; i++) {
    grid[i][0] = 0;
  }
  for (int j = 1; j < columns; j++) {
    grid[0][j] = 0;
  }
}

// fills grid with DP values and traceback info
void fill(int **grid, int rows, int columns, const string &one,
          const string &two) {
  for (int i = 1; i < rows; i++) {
    for (int j = 1; j < columns; j++) {
      int diag = compareChars(one[i - 1], two[j - 1]) + grid[i - 1][j - 1];
      int up = grid[i - 1][j] + GAP;
      int left = grid[i][j - 1] + GAP;

      grid[i][j] = returnMax(diag, up, left);
    }
  }
}

int find_max(int **grid, int rows, int columns) {
  int max = 0;
  int x = 0;
  int y = 0;
  for (int i = 0; i < rows; i++) {
    if (grid[i][columns - 1] >= max) {
      x = i;
      y = columns - 1;
      max = grid[x][y];
    }
  }
  for (int i = 0; i < columns; i++) {
    if (grid[rows - 1][i] >= max) {
      x = rows - 1;
      y = i;
      max = grid[x][y];
    }
  }
  return max;
}
// main() takes in input and runs alignment
int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <seq1.fasta> <seq2.fasta>\n";
    return 1;
  }

  ifstream fin1(argv[1]);
  ifstream fin2(argv[2]);
  if (!fin1 || !fin2) {
    cerr << "Error: could not open input files.\n";
    return 1;
  }

  // take in input, skipping FASTA headers
  string input, header;
  string one, two;

  getline(fin1, header);
  getline(fin2, header);

  while (getline(fin1, input)) {
    one += input;
  }
  while (getline(fin2, input)) {
    two += input;
  }

  // rows correspond to string one, columns to string two
  int rows = one.length() + 1;
  int columns = two.length() + 1;

  // sanity checks
  assert(rows == (int)one.size() + 1);
  assert(columns == (int)two.size() + 1);

  // initialize grid
  int **grid = new int *[rows];
  for (int i = 0; i < rows; i++) {
    grid[i] = new int[columns]();  // zero-initialize
  }

  initialize(grid, rows, columns);

  fill(grid, rows, columns, one, two);
  cout << "Alignment score: " << find_max(grid, rows, columns) << '\n';

  // cleanup
  for (int i = 0; i < rows; i++) {
    delete[] grid[i];
  }
  delete[] grid;

  return 0;
}
