// Reverse Complement Generator written in c++
// Andrew Sagraves

// NOTE: this outputs the sequence without any newlines, so the formatting sucks. if you want newlines, add a 'fout << '\n'; at the end of the while loop

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  // error checking for arguments
  if (argc != 3) {
    cout << "usage: ./reverse-complement lambda.fasta lambda.reverse.fasta";
    return 1;
  }

  // set input and output filestreams
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  // error checking for input and output files
  if (!fin) {
    cout << "Could not open input file";
    return 2;
  }
  if (!fout) {
    cout << "Could not open output file";
    return 3;
  }
  // use this for inputting genome data
  string input;
  string output;
  fout << ">reversed\n";
  // processing
  while (getline(fin, input)) {
    for (int i = 0; i < input.length(); i++) {
      if (input[i] == 'A') {
        output += 'T';
      } else if (input[i] == 'T') {
        output += 'A';
      } else if (input[i] == 'C') {
        output += 'G';
      } else if (input[i] == 'G') {
        output += 'C';
      }
    }
  }
  // reverse stuff
  reverse(output.begin(), output.end());
  fout << output;
}
