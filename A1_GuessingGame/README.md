# Guessing Game 

I have written this program to guess a randomly generated number. 

# Compiling/running the program 

To run this program, you may use the clang++ or g++ compiler.

# Requirements of the game 

1) The user will play the game a total of 5 times in a row 
2) For each round, a new number from 1-10 must be randomly generated
3) The user will guess the number: 
    -- if the number is correct, the game will end 
    -- if the number is incorrect, a hint will be provided for whether the user's guess should be higher or lower 
4) Each time a user guesses, the number of guesses the user has made per round is incremented 
5) When the user guesses the correct answer, the program will output that they have finished
    -- the user can then either 
        --- start a new game 
        --- or output the summary of how many guesses the user made over the 5 games 

# Logistics 

For this program, I have taken advantage of std::array and std::vector to store the number of guesses the user made each round.
Additionally, std::rand has been used to generate random numbers. 
