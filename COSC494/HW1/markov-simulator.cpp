#include <cmath>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

struct results {
  int a = 0;
  int t = 0;
  int c = 0;
  int g = 0;
  int sum = 0;
};

void create_string(ofstream &fout, map<string, results> model) {
  const char bases[] = {'A', 'T', 'C', 'G'};
  string start = string() + bases[random() % 4] + bases[random() % 4] + bases[random() % 4];
  string output = start;
  for (int i = 3; i < 20000; i++) {
    char next;
    string previous = string() + output[i - 3] + output[i - 2] + output[i - 1];
    if (model.find(previous) != model.end()) {
      int r = rand() % model[previous].sum;
      if (r < model[previous].a)
        output += string() + 'A';
      else if (r < model[previous].a + model[previous].t)
        output += string() + 'T';
      else if (r < model[previous].a + model[previous].t + model[previous].c)
        output += string() + 'C';

      else
        output += string() + 'G';
    }
    else {
      output += string() + bases[random() % 4];
    }
  }
  fout << output;
}

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

int main(int argc, char *argv[]) {
  // error checking for arguments
  if (argc != 3) {
    cout << "usage: ./markov-probability human-sample.fasta output-sample.fasta";
    return 1;
  }

  // set inputfilestream
  ifstream fin;
  ofstream fout;
  fout.open(argv[2]);
  fin.open(argv[1]);

  // train model
  map<string, results> p = train_model(fin);

  // close filestream for current file
  fin.close();

  // open for new file
  fin.open(argv[2]);

  // calculate probabilities
  create_string(fout, p);
  fout.close();
}
