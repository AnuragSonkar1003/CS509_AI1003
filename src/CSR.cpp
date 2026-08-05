#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("input_csr.txt");
    ofstream fout("output.txt");

    if (!fin) {
        cout << "Error opening input.txt" << endl;
        return 1;
    }

    int rows, cols;
    fin >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));

    // Read matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fin >> matrix[i][j];
        }
    }

    vector<int> values;
    vector<int> colIndex;
    vector<int> rowPtr;

    rowPtr.push_back(0);

    // Convert to CSR
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                values.push_back(matrix[i][j]);
                colIndex.push_back(j);
            }
        }
        rowPtr.push_back(values.size());
    }

    // Write output
    fout << "Values:\n";
    for (int x : values)
        fout << x << " ";

    fout << "\n\nColumn Index:\n";
    for (int x : colIndex)
        fout << x << " ";

    fout << "\n\nRow Pointer:\n";
    for (int x : rowPtr)
        fout << x << " ";

    fin.close();
    fout.close();

    cout << "CSR conversion completed successfully." << endl;
    cout << "Output written to output.txt" << endl;

    return 0;
}