// Neucleotide Analyzer written in c++
// Andrew Sagraves

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
struct sequence {
  double a = 0;
  double t = 0;
  double c = 0;
  double g = 0;
  double aa = 0;
  double at = 0;
  double ac = 0;
  double ag = 0;
  double ta = 0;
  double tt = 0;
  double tc = 0;
  double tg = 0;
  double ca = 0;
  double ct = 0;
  double cc = 0;
  double cg = 0;
  double ga = 0;
  double gt = 0;
  double gc = 0;
  double gg = 0;
  // this populates the counts for each value
  void bullshit(string file) {
    for (int i = 0; i < file.length(); i++) {
      if (file[i] == 'A') {
        a += 1;
        if (i != 0 && file[i - 1] == 'A') {
          aa += 1;
        }
        if (i != 0 && file[i - 1] == 'T') {
          at += 1;
        }
        if (i != 0 && file[i - 1] == 'C') {
          ac += 1;
        }
        if (i != 0 && file[i - 1] == 'G') {
          ag += 1;
        }
      } else if (file[i] == 'T') {
        t += 1;
        if (i != 0 && file[i - 1] == 'A') {
          ta += 1;
        }
        if (i != 0 && file[i - 1] == 'T') {
          tt += 1;
        }
        if (i != 0 && file[i - 1] == 'C') {
          tc += 1;
        }
        if (i != 0 && file[i - 1] == 'G') {
          tg += 1;
        }
      } else if (file[i] == 'C') {
        c += 1;
        if (i != 0 && file[i - 1] == 'A') {
          ca += 1;
        }
        if (i != 0 && file[i - 1] == 'T') {
          ct += 1;
        }
        if (i != 0 && file[i - 1] == 'C') {
          cc += 1;
        }
        if (i != 0 && file[i - 1] == 'G') {
          cg += 1;
        }
      } else if (file[i] == 'G') {
        g += 1;
        if (i != 0 && file[i - 1] == 'A') {
          ga += 1;
        }
        if (i != 0 && file[i - 1] == 'T') {
          gt += 1;
        }
        if (i != 0 && file[i - 1] == 'C') {
          gc += 1;
        }
        if (i != 0 && file[i - 1] == 'G') {
          gg += 1;
        }
      }
    };
  }
  void outputSingles() {
    double total = a + t + c + g;
    cout << "A: " << a / total << endl;
    cout << "T: " << t / total << endl;
    cout << "G: " << g / total << endl;
    cout << "C: " << c / total << endl;
  }
  void outputDoubles() {
    double total = a + t + c + g;
    cout << "AA:" << aa / total << endl;
    cout << "AT:" << at / total << endl;
    cout << "AG:" << ag / total << endl;
    cout << "AC:" << ac / total << endl;
    cout << "TA:" << ta / total << endl;
    cout << "TT:" << tt / total << endl;
    cout << "TG:" << tg / total << endl;
    cout << "TC:" << tc / total << endl;
    cout << "GA:" << ga / total << endl;
    cout << "GT:" << gt / total << endl;
    cout << "GG:" << gg / total << endl;
    cout << "GC:" << gc / total << endl;
    cout << "CA:" << ca / total << endl;
    cout << "CT:" << ct / total << endl;
    cout << "CG:" << cg / total << endl;
    cout << "CC:" << cc / total << endl;
  }
};
int main(int argc, char *argv[]) {
  // error checking for arguments
  if (argc != 2) {
    cout << "usage: ./freq lambda.fasta";
    return 1;
  }

  // set inputfilestream
  ifstream fin(argv[1]);

  // error checking for input files
  if (!fin) {
    cout << "Could not open input file";
    return 2;
  }
  // use this for inputting genome data
  string input;
  string file;
  // processing
  while (getline(fin, input)) {
    file += input;
  }
  sequence seq;
  seq.bullshit(file);
  seq.outputSingles();
  seq.outputDoubles();
}
