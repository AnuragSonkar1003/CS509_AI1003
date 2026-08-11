#include <chrono>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace chrono;

void runProgram(const string& name, const string& command) {
    cout << "\n========== " << name << " ==========\n";

    auto start = high_resolution_clock::now();
    int status = system(command.c_str());
    auto stop = high_resolution_clock::now();

    if (status != 0) {
        cout << "Failed to execute " << name << '\n';
    }

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Execution Time: " << duration.count() << " ms\n";
}

int main() {
    int choice;

    cout << "========== Main Menu ==========\n";
    cout << "1. Assignment 01\n";
    cout << "2. Assignment 02\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            runProgram("Assignment 01",
                       "cd Assignment_01/driver && ./driver");
            break;

        case 2:
            runProgram("Assignment 02",
                       "cd Assignment_02/driver && ./driver");
            break;

        default:
            cout << "Invalid choice!\n";
            return 1;
    }

    return 0;
}