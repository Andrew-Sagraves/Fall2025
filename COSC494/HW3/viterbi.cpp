#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    // Input rolls
    string seq;
    cin >> seq;
    int T = seq.size();

    // Two hidden states: 0 = Fair, 1 = Loaded
    int N = 2;

    // Transition matrix A
    vector<vector<double> > A(N, vector<double>(N, 0.0));
    A[0][0] = 0.9; A[0][1] = 0.1;
    A[1][0] = 0.1; A[1][1] = 0.9;

    // Emission matrix B (2x6)
    vector<vector<double> > B(N, vector<double>(6, 0.0));
    for (int i = 0; i < 6; i++) B[0][i] = 1.0/6.0; // Fair
    for (int i = 0; i < 5; i++) B[1][i] = 0.1;     // Loaded not 6
    B[1][5] = 0.5;                                // Loaded is 6

    // Initial distribution π
    vector<double> pi(N, 0.0);
    pi[0] = 0.5; pi[1] = 0.5;

    // Viterbi algorithm storage
    vector<vector<double> > delta(T, vector<double>(N, 0.0)); // max probabilities
    vector<vector<int> > psi(T, vector<int>(N, 0));           // backpointers

    // Initialization
    int firstObs = seq[0] - '1';
    for (int i = 0; i < N; i++) {
        delta[0][i] = pi[i] * B[i][firstObs];
        psi[0][i] = 0;
    }

    // Recursion
    for (int t = 1; t < T; t++) {
        int obs = seq[t] - '1';
        for (int j = 0; j < N; j++) {
            double maxProb = -1.0;
            int argMax = 0;
            for (int i = 0; i < N; i++) {
                double prob = delta[t-1][i] * A[i][j];
                if (prob > maxProb) {
                    maxProb = prob;
                    argMax = i;
                }
            }
            delta[t][j] = maxProb * B[j][obs];
            psi[t][j] = argMax;
        }
    }

    // Termination
    double bestProb = -1.0;
    int lastState = 0;
    for (int i = 0; i < N; i++) {
        if (delta[T-1][i] > bestProb) {
            bestProb = delta[T-1][i];
            lastState = i;
        }
    }

    // Backtracking
    vector<int> path(T, 0);
    path[T-1] = lastState;
    for (int t = T-2; t >= 0; t--) {
        path[t] = psi[t+1][path[t+1]];
    }

    // Output
    cout << fixed << setprecision(10);
    cout << "Most likely state path: ";
    for (int t = 0; t < T; t++) {
        if (path[t] == 0) cout << "Fair ";
        else cout << "Loaded ";
    }
    cout << endl;

    return 0;
}

