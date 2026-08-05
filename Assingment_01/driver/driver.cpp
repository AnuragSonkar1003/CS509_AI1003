#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    int choice;

    cout << "========== Matrix Algorithms ==========\n";
    cout << "1. Simple GEMM\n";
    cout << "2. Blocking GEMM\n";
    cout << "3. CSR Conversion\n";
    cout << "Enter your choice: ";
    cin >> choice;

    auto start = high_resolution_clock::now();

    switch(choice)
    {
        case 1:
            system("../src/simple_gemm");
            break;

        case 2:
            system("../src/blocking");
            break;

        case 3:
            system("../src/CSR");
            break;

        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "\nExecution Time: "
         << duration.count()
         << " ms" << endl;

    return 0;
}