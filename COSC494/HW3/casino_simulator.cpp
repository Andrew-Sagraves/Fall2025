#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int generate_even_number(int i) { return i % 6 + 1; }

int generate_weighted_number(int i) {
  i = i % 10 + 1;
  if (i > 5) {
    return 6;
  }
  return i;
}

int main() {

  // seed random number generator with current time
  srand(time(0));

  // assume casino is always fair
  bool fair = true;
  for (int i = 0; i < 300; i++) {
    int percent = rand() % 101;
    int num = rand();
    if (fair) {
      cout << generate_weighted_number(num);
      if (percent < 5) fair = false;

    } else {
      cout << generate_even_number(num);
      if (percent < 5) fair = true;
    }
  }
}
