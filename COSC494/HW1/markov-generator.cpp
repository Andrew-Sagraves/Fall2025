#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

struct results {
  double a = 0.01;
  double t = 0.01;
  double c = 0.01;
  double g = 0.01;
  double sum = 0.04;
};

map<string, results> train_model(ifstream &fin) {
  string line;
  string file = "";

  map<string, results> markov;
  while (getline(fin, line)) {
    file += line;
  }

  for (int i = 3; i < file.size(); i++) {
    if (file[i] == 'A') {
      string chars = string() + file[i - 3] + file[i - 2] + file[i - 1];
      markov[chars].a += 1;
      markov[chars].sum += 1;

    } else if (file[i] == 'T') {
      string chars = string() + file[i - 3] + file[i - 2] + file[i - 1];
      markov[chars].t += 1;
      markov[chars].sum += 1;

    } else if (file[i] == 'C') {
      string chars = string() + file[i - 3] + file[i - 2] + file[i - 1];
      markov[chars].c += 1;
      markov[chars].sum += 1;

    } else if (file[i] == 'G') {
      string chars = string() + file[i - 3] + file[i - 2] + file[i - 1];
      markov[chars].g += 1;
      markov[chars].sum += 1;
    }
  }
  return markov;
}

double get_probability(ifstream &fin, map<string, results> training_data) {
  string line;
  string file = "";

  double prob = 0;
  while (getline(fin, line)) {
    file += line;
  }

  for (int i = 3; i < file.size(); i++) {
    string mark = string() + file[i - 3] + file[i - 2] + file[i - 1];
    if (file[i] == 'A') {
      if (training_data.find(mark) != training_data.end()) {
        prob += log(training_data[mark].a / training_data[mark].sum);
      }
    }
    if (file[i] == 'T') {
      if (training_data.find(mark) != training_data.end()) {
        prob += log(training_data[mark].t / training_data[mark].sum);
      }
    }
    if (file[i] == 'C') {
      if (training_data.find(mark) != training_data.end()) {
        prob += log(training_data[mark].c / training_data[mark].sum);
      }
    }
    if (file[i] == 'G') {
      if (training_data.find(mark) != training_data.end()) {
        prob += log(training_data[mark].g / training_data[mark].sum);
      }
    }
  }
  return prob;
}

int main(int argc, char *argv[]) {
  // error checking for arguments
  if (argc != 3) {
    cout << "usage: ./markov-probability human-sample.fasta neanderthal-sample.fasta";
    return 1;
  }

  // set inputfilestream
  ifstream fin;
  fin.open(argv[1]);

  // train model
  map<string, results> p = train_model(fin);

  // close filestream for current file
  fin.close();

  // open for new file
  fin.open(argv[2]);

  // calculate probabilities
  double result = get_probability(fin, p);

  // output result
  cout << "result: " << result << endl;
}
