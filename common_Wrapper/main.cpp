#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

void runProgram(const string &name, const string &command)
{
    cout << "\n========== " << name << " ==========\n";

    auto start = high_resolution_clock::now();

    int status = system(command.c_str());

    auto stop = high_resolution_clock::now();

    if (status == 0)
        cout << name << " executed successfully.\n";
    else
        cout << "Failed to execute " << name << endl;

    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Execution Time: " << duration.count() << " ms\n";
}

int main()
{
    int choice,choices;

    cout << "Assignment 01\n";
    cout << "Assignment 02\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice){

        case 1:
            
            cout << "========== Assignment 01 ==========\n";
            cout << "1. Simple GEMM\n";
            cout << "2. Blocking GEMM\n";
            cout << "3. CSR Conversion\n";
            cout << "4. Run All\n";
            cin >> choices;
        
            if (choices == 1){
                runProgram("Simple GEMM", "./Assingment_01/src/simple_gemm");
                
            }
            else if (choices == 2){
                runProgram("Blocking GEMM", "./Assingment_01/src/blocking");
            }
            else if (choices == 3){
                runProgram("CSR Conversion", "./Assingment_01/src/CSR");
            }
            else if (choices == 4){
                runProgram("Simple GEMM", "./Assingment_01/src/simple_gemm");
                runProgram("Blocking GEMM", "./Assingment_01/src/blocking");
                runProgram("CSR Conversion", "./Assingment_01/src/CSR");
            }
            else{
                cout << "Invalid choice!" << endl;
                return 1;
            };
            break;
   

        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    return 0;
}



