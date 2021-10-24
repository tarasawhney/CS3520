// Compile with: g++ -std=c++17 main.cpp -o prog
// Run with    : ./prog
//
// Compile for debugging with:
// g++ -std=c++17 -g main.cpp -o prog
// Run with gdb: gdb ./prog --tui
/////////////////////////////////////////////////

// @file main.cpp

// Header Files
#include <iostream> // For input and output
#include <fstream>  // For file input/output
#include <string>   
#include <vector>
#include <utility> // Contains std::pair
#include <cstdlib> // For random numbers
#include <time.h>  // For getting time
#include <chrono>  // For duration and timepoint

// Forward declarations of functions
bool validTransactionID(int parity);
std::pair<int,int> CreateTransation();
void WriteLog();

// Global variables
// Note: the 'g_' prefix in the variable name
//       indicates that this is a global variable.
std::vector<std::pair<int,int> > g_transactions;

// This function returns 
std::pair<int,int> CreateTransaction(){
    std::pair<int,int> transaction;
    // Generate a random value for the transaction amount
    transaction.first = rand()%100000;
    // Generate a random value for the parity id
    //changed to .second to work with second value in the pair 
    transaction.second = rand()%100000; 
    // Return our 'std::pair'
    return transaction; 
}

// Helper function to check if a transaction is valid
bool isValidTransaction(int parity){
    if(parity%2==0){
        return true;
    }else{ 
        return false; //flipped return true and return false 
    }
    
}

// Writes a log out of all of the transaction
// values and parities.
void WriteLog(){
    std::ofstream Log("Log.txt");
    if(Log.is_open()){
        for(int i=0; i < g_transactions.size(); i++){
            Log << g_transactions[i].first << " " << g_transactions[i].second << "\n"; //changed to .second
        }
    }else{
        std::cout << "could not write file" << std::endl;
    }
}


// Entry to program
int main(int argc, char* argv[]){
    // Random number seed
    // This will generate a pseudo random number
    // based on the current which is 
    // what time(NULL) returns.
    srand(time(NULL));

    // Delay in milliseconds before every transaction
    const int delay = 15;
    // Keep track of the total transactions
    int transactions = 0;

    // Log the current time with the 'chrono' library. 
    std::chrono::system_clock::time_point lastTransactionTime = std::chrono::system_clock::now(); 

    // The program will run for a finite number of transactions
    while(transactions < 1000){
        // Get  the current time
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now(); 

        // Compute the elapsed time between the time 'now'
        // and the time since the 'lastTransactionTime'
        std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTransactionTime);


        if(elapsedTime.count() > delay){
            // Convert the time to something that can be printed 
            std::time_t tt = std::chrono::system_clock::to_time_t(now);
            // Update the start time
            lastTransactionTime = std::chrono::system_clock::now(); 
            // Create a new transaction and store it in 'newTransaction'
            std::pair<int,int> newTransaction = CreateTransaction();

            // If the transaction is valid then add it.
            // We do this by checking the second parity portion of the transaction.
            if(isValidTransaction(newTransaction.second)){ //changed to check the second parity portion
                // Print the time a valid transaction occurred.
                std::cout << "[" << transactions << "] " << ctime(&tt);
                // Add the transaction to the log
                g_transactions.push_back(newTransaction);
                std::cout << newTransaction.first << " " << newTransaction.second  <<"\n"; //print transaction
                // Increment the number of transactions that took place
                transactions++; 
            }
        }
    }

    // Log all of the transactions at the end of the program
    WriteLog();
    
    return 0;
}
