#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
    int choice;

    cout << "========== Shortest Path Algorithms ==========\n";
    cout << "1. Floyd-Warshall\n";
    cout << "2. Bellman-Ford\n";
    cout << "Enter your choice: ";
    cin >> choice;

    auto start = high_resolution_clock::now();

    switch (choice) {
        case 1:
            system("../src/floyd");
            break;

        case 2:
            system("../src/bellman");
            break;

        default:
            cout << "Invalid choice!\n";
            return 1;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "\nExecution Time: " << duration.count() << " ms\n";
    return 0;
}