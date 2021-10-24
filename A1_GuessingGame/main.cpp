#include <iostream>
#include <array>
#include <time.h> 
#include <cstdlib>
#include <vector>
///////////////////////////////


//Entry point to program 'main' 
int main(int argc, char* argv[]){
    int user_guesses; 
    //int num_guesses = 0; 
    int round_number = 0; 
    //stores number of guesses user made
    std::vector<int>num_guesses; 
    for (int i =0; i <5; i++) {
        num_guesses.push_back(1); 
    }

 ////////////////////////////////////////////////////////////////////// 
    //Introducing game to the user
    std::cout << "\n" << "Thank you for playing our guessing game!" << "\n"; 
    std::string user_name; 
    //Prompt user to enter their name 
    std::cout << "\n" << "What is your name?" << "\n"; 
    std::cin >> user_name; 

    //welcome the user and state the rules of the game 
    std::cout << "\n" << "Welcome " << user_name << " :)" << "\n"; 
     // stating rules of the game for the user 
    std::cout <<"\n" << "Here are the rules of the game: " << "\n";
    std::cout << " - You will play the guessing game a total of 5 times in a row" << "\n"; 
    std::cout << " - You will guess a number from 1-10" << "\n"; 

    //Prompt the user to press any key to begin the game
    std::cout << "\n" << "Let's begin" << " (Press any key!)" << "\n"; 
    std::cin >> user_name; 

/////////////////////////////////////////////////////////////////////////
    //Setting 5 rounds for the game 
    while (round_number < 5){
        //print out round number 
        std::cout << "\n" << "Round: " << round_number << "\n"; 
        std::cout << "Pick a number 1-10" << "\n"; 
        std::cin >> user_guesses; 
        
        //used to store the number of guesses a user makes per round 

          std::srand(time(NULL));
          //std::cout << num << std::endl; 
          int num = rand()%10+1; 
          

        //implementing while the user does not get the number 
        while (user_guesses != num){
            //if the user enters a number less than 1 
            //report that they must enter a number between 1-10
            if (user_guesses < 1) {
                std::cout << "Must be a number betwwen 1-10" << "\n"; 
                std::cin >> user_guesses; 
            }
            else if (user_guesses > 10){
                //if the user enters a number greater than 10 
                //report that they must enter a number between 1-10
                std::cout << "Must be a number between 1-10" << "\n"; 
                std::cin >> user_guesses; 
            }
            if (user_guesses < num){
                //if the user's guess is lower than the random number prompt them to guess higher 
                std::cout << "Guess higher" << "\n"; 
                std::cin >> user_guesses; 
                num_guesses[round_number]++; // incrementing the number of guesses made

            }
            else if (user_guesses > num){
                //if the user's guess is lower than the random number prompt them to guess lower 
                std::cout << "Guess lower" << "\n"; 
                std::cin >> user_guesses;
                num_guesses[round_number]++; // incrementing the number of guesses made 
            }
        }while (user_guesses == num){
            // print congrats if the user has guessed the number correctly 
            std::cout << "Congrats! You guessed correctly :) " << "\n"; 
            std::cout << "Round: " << round_number << " over!" << "\n"; 
            break; 
    

    }round_number++; 
    //std::cout << "Game Over!" << "\n"; 
    } std::cout << "\n" << "Final Results" << "\n" << "############################"; 
    
    //printing out user's final results 
    //outputs the total number of guesses the user made per round 
    for (round_number =0; round_number <5; round_number++){
        std::cout << "\n" << "Round: " << round_number << "\n" << "Total Guesses:" << num_guesses[round_number] << "\n";  
   
    }
    
    return 0; 



} 
