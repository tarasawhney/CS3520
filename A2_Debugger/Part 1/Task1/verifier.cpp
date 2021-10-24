///////////////////////////////////////////////
// Compile with: g++ -std=c++17 verifier.cpp -o verifier
// Run with    : ./verifier
//
// Compile for debugging with:
// g++ -std=c++17 -g verifier.cpp -o verifier
// Run with gdb: gdb ./verifier --tui
/////////////////////////////////////////////////

// @file verifier.cpp

// This program does not contain any known bugs.
// This will verify a valid log file.
//
// Use this as an example to learn from for reading input.
// You do not need to make any changes to this file.

// C++ Header Files
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[]){

    // Keep track of transactions and errors.
    int transactions=0;
    int errorcount =0;

    // File we are reading in
    std::ifstream myFile("Log.txt");
    
    // If the file exists (i.e. you have run the other main program at least once)
    if(myFile.is_open()){
        // Variables to store values in our Log.txt
        int amount,parity;
        // Read in two integers at a time until there are no more in the file.
        while(myFile >> amount >> parity){
            // Verify the parity values are divisible by 2.
            if (parity%2==0){
                std::cout << amount << " " << parity << std::endl;   
            }else{
                // If not increment the error count.
                std::cout << "error:" << amount << " " << parity << std::endl;   
                errorcount++;
            }
            // Every line we read is a transaction
            transactions++;
        }
    }else{
        std::cout << "Log.txt does not exist, did you run your program?" << std::endl;
    }

    // If for some reason there are not exactly 1000 transactions, then
    // log an error.
    if(transactions!=1000){
        std::cout << "error: transactions !=1000" << transactions << std::endl;
    }else{
        std::cout << "transactions = " << transactions << std::endl;
    }

    // Report the error count.
    std::cout << "errorcount: " << errorcount << std::endl;

    return 0;
}
