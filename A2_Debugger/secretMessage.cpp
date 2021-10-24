// Compile with: g++ -std=c++17 main.cpp -o prog
// Run with    : ./prog
//
// Compile for debugging with:
// g++ -std=c++17 -g main.cpp -o prog
// Run with gdb: gdb ./prog --tui
/////////////////////////////////////////////////

// @file main.cpp

// C++ Header Libraries
#include <iostream>
#include <string>

// Takes an input parameter for the string to encrypt.
// The second parameter is going to modify the string and
// serve as the output.

void decrypt(const std::string& input){ 
    //pass by reference - can tell by the & symbol 
    //initializing a new string called 'new_input'
    std::string new_input = input; 
    //using for loop and gathering length/all characters of the given input 
    for (int i = 0; i < new_input.length(); i++){
        //
        //new_input += new_input[i]; 
        new_input[i] += -2; 
    }
    //printing out the message using std::cout 
    std::cout << "\n" << new_input << "\n"; 
}
 


     //decrypt(new_input); 

    // Decrypt the string



// Entry point to program 'main'
int main(int argc, char* argv[]){


    // A secret message for you to decode
    // Note: The \" is an escape sequence so that you can write " marks in
    //       a string.
   std::string secretMessage = "\"[qw\"ctg\"c\"dgeqokpi\"c\"itgcv\"Rtqitcoogt\"";
    
    // Call the decrypt function
    decrypt(secretMessage);
    
    return 0;
}
