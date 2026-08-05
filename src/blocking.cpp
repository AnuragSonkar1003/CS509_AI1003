#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define BLOCK_SIZE 32

int main() {
    ifstream fin("../input/input_blocking.txt");
    ofstream fout("../output/output.txt");

    if (!fin) {
        cout << "Error opening input.txt" << endl;
        return 1;
    }

    int M, K, N;
    fin >> M >> K >> N;

    // Read Matrix A
    vector<vector<float>> A(M, vector<float>(K));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < K; j++)
            fin >> A[i][j];

    // Read Matrix B
    vector<vector<float>> B(K, vector<float>(N));
    for (int i = 0; i < K; i++)
        for (int j = 0; j < N; j++)
            fin >> B[i][j];

    // Result Matrix C
    vector<vector<float>> C(M, vector<float>(N, 0));

    // Blocked GEMM
    for (int ii = 0; ii < M; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < K; kk += BLOCK_SIZE) {

                int i_max = min(ii + BLOCK_SIZE, M);
                int j_max = min(jj + BLOCK_SIZE, N);
                int k_max = min(kk + BLOCK_SIZE, K);

                for (int i = ii; i < i_max; i++) {
                    for (int j = jj; j < j_max; j++) {
                        for (int k = kk; k < k_max; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    // Write Output
    fout << M << " " << N << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            fout << C[i][j] << " ";
        }
        fout << endl;
    }

    fin.close();
    fout.close();

    cout << "Blocked GEMM completed successfully." << endl;
    cout << "Result written to output.txt" << endl;

    return 0;
}