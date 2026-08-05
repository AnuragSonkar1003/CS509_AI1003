#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("../input/input_gemm.txt");
    ofstream fout("../output/output.txt");

    if (!fin) {
        if (!fin) {
            cerr << "Error: Cannot open ../input/input_gemm.txt" << endl;
            return 1;
    
    }
}

    int M, K, N;
    fin >> M >> K >> N;

    // Read Matrix A
    vector<vector<int>> A(M, vector<int>(K));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            fin >> A[i][j];
        }
    }

    // Read Matrix B
    vector<vector<int>> B(K, vector<int>(N));
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            fin >> B[i][j];
        }
    }

    // Result Matrix C
    vector<vector<int>> C(M, vector<int>(N, 0));

    // Simple GEMM
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Write result to output file
    fout << M << " " << N << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            fout << C[i][j] << " ";
        }
        fout << endl;
    }

    fin.close();
    fout.close();

    cout << "Matrix multiplication completed.\n";
    cout << "Output written to output.txt" << endl;

    return 0;
}