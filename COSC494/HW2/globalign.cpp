// Andrew Sagraves
// globalign - gets gobal alignment of two .fasta files

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
    grid[i][0] = grid[i - 1][0] + GAP;
  }
  for (int j = 1; j < columns; j++) {
    grid[0][j] = grid[0][j - 1] + GAP;
  }
}

// fills grid with DP values and traceback info
void fill(int **grid, char **tb, int rows, int columns, const string &one,
          const string &two) {
  for (int i = 1; i < rows; i++) {
    for (int j = 1; j < columns; j++) {
      int diag = compareChars(one[i - 1], two[j - 1]) + grid[i - 1][j - 1];
      int up = grid[i - 1][j] + GAP;
      int left = grid[i][j - 1] + GAP;

      grid[i][j] = returnMax(diag, up, left);

      if (grid[i][j] == diag) {
        tb[i][j] = 'D';
      } else if (grid[i][j] == up) {
        tb[i][j] = 'U';
      } else {
        tb[i][j] = 'L';
      }
    }
  }
}

// traceback alignment
void traceback(char **tb, int rows, int columns, const string &one,
               const string &two, string &out1, string &out2) {
  int x = rows - 1;
  int y = columns - 1;

  while (x > 0 || y > 0) {
    if (x > 0 && y > 0 && tb[x][y] == 'D') {
      out1.push_back(one[x - 1]);
      out2.push_back(two[y - 1]);
      x--;
      y--;
    } else if (x > 0 && tb[x][y] == 'U') {
      out1.push_back(one[x - 1]);
      out2.push_back('-');
      x--;
    } else if (y > 0 && tb[x][y] == 'L') {
      out1.push_back('-');
      out2.push_back(two[y - 1]);
      y--;
    } else {
      break;
    }
  }

  reverse(out1.begin(), out1.end());
  reverse(out2.begin(), out2.end());
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

  char **tb = new char *[rows];
  for (int i = 0; i < rows; i++) {
    tb[i] = new char[columns]();
  }

  fill(grid, tb, rows, columns, one, two);

  cout << "Alignment score: " << grid[rows - 1][columns - 1] << '\n';

  string aln1, aln2;
  traceback(tb, rows, columns, one, two, aln1, aln2);

  cout << aln1 << '\n';
  cout << aln2 << '\n';

  // cleanup
  for (int i = 0; i < rows; i++) {
    delete[] grid[i];
    delete[] tb[i];
  }
  delete[] grid;
  delete[] tb;

  return 0;
}
