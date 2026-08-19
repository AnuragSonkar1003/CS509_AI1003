#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    int choice;

    cout << "========== MSTree Algorithms ==========\n";
    cout << "1. prims\n";
    cout << "2. kruskal\n";
    cout << "Enter your choice: ";
    cin >> choice;

    auto start = high_resolution_clock::now();

    switch(choice)
    {
        case 1:
            system("../src/prims");
            break;

        case 2:
            system("../src/kruskal");
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
