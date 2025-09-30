#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    // Input sequence of dice rolls
    string seq;
    cin >> seq;
    int T = seq.size();

    // Two hidden states: 0 = Fair, 1 = Loaded
    int N = 2;

    // Transition matrix A (2x2)
    vector<vector<double> > A(N, vector<double>(N, 0.0));
    A[0][0] = 0.95; A[0][1] = 0.05; // transition from Fair
    A[1][0] = 0.05; A[1][1] = 0.95; // transition from Loaded

    // Emission matrix B (2x6)
    vector<vector<double> > B(N, vector<double>(6, 0.0));

    // Fair die (uniform distribution)
    for (int i = 0; i < 6; i++) {
        B[0][i] = 1.0 / 6.0;
    }

    // Loaded die (6 with prob 0.5, others 0.1)
    for (int i = 0; i < 5; i++) {
        B[1][i] = 0.1;
    }
    B[1][5] = 0.5;

    // Initial distribution 
    vector<double> pi(N, 0.0);
    pi[0] = 1.0; // Fair
    pi[1] = 0.0; // Loaded

    // Forward algorithm with log-space computations
    vector<vector<double> > logAlpha(T, vector<double>(N, -INFINITY));

    // Initialization
    int firstObs = seq[0] - '1'; // convert char to 0..5
    for (int i = 0; i < N; i++) {
        logAlpha[0][i] = log(pi[i]) + log(B[i][firstObs]);
    }

    // Induction
    for (int t = 1; t < T; t++) {
        int obs = seq[t] - '1';
        for (int j = 0; j < N; j++) {
            double maxLog = -INFINITY;
            for (int i = 0; i < N; i++) {
                double val = logAlpha[t - 1][i] + log(A[i][j]);
                if (val > maxLog) maxLog = val;
            }
            double sumExp = 0.0;
            for (int i = 0; i < N; i++) {
                double val = logAlpha[t - 1][i] + log(A[i][j]);
                sumExp += exp(val - maxLog);
            }
            logAlpha[t][j] = log(B[j][obs]) + maxLog + log(sumExp);
        }
    }

    // Termination (log-sum-exp over final states)
    double maxLog = logAlpha[T - 1][0];
    if (logAlpha[T - 1][1] > maxLog) {
        maxLog = logAlpha[T - 1][1];
    }

    double sumExp = exp(logAlpha[T - 1][0] - maxLog) + exp(logAlpha[T - 1][1] - maxLog);
    double logProb = maxLog + log(sumExp);

    cout << fixed << setprecision(6);
    cout << "Log probability of sequence = " << logProb << endl;

    return 0;
}

