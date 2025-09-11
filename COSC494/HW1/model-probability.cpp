// probability calculator in c++
// Andrew Sagraves

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// this is used to stransfer data from one func to another
struct probabilities {
  double A;
  double T;
  double C;
  double G;
};

// this takes the individual probabilities from the human genome and gets the probability of the neanderthal sequence
double get_probabilities(probabilities p, ifstream &fin) {
  double result = 0;
  string input;
  while (getline(fin, input)) {
    for (int i = 0; i < input.length(); i++) {
      if (input[i] == 'A') {
        result += log(p.A);
      } else if (input[i] == 'T') {
        result += log(p.T);
      } else if (input[i] == 'C') {
        result += log(p.C);
      } else if (input[i] == 'G') {
        result += log(p.G);
      }
    }
  }
  return result;
}

// this trains the model used to calculate the probability of the neanderthal sequence
probabilities train_model(ifstream &fin) {
  probabilities p;
  string input;
  double a = 0;
  double t = 0;
  double c = 0;
  double g = 0;
  // processing
  while (getline(fin, input)) {
    for (int i = 0; i < input.length(); i++) {
      if (input[i] == 'A') {
        a += 1;
      } else if (input[i] == 'T') {
        t += 1;
      } else if (input[i] == 'C') {
        c += 1;
      } else if (input[i] == 'G') {
        g += 1;
      }
    }
  }
  double sum = a + t + c + g;
  p.A = a / sum;
  p.T = t / sum;
  p.C = c / sum;
  p.G = g / sum;

  return p;
}

int main(int argc, char *argv[]) {
  // error checking for arguments
  if (argc != 3) {
    cout << "usage: ./model-probability human-sample.fasta neanderthal-sample.fasta";
    return 1;
  }

  // set inputfilestream
  ifstream fin;
  fin.open(argv[1]);

  // train model
  probabilities p = train_model(fin);

  // close filestream for current file
  fin.close();

  // open for new file
  fin.open(argv[2]);

  // calculate probabilities
  double result = get_probabilities(p, fin);
  
  // output result
  cout << "result: " << result << endl;
}
