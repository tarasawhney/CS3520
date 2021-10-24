# Overview 

This program utilizes debugging skills and working with strings. 

# Task 1: Fixing the bugs

Here, the user first needs to open up the file in main.cpp. A prompt in the source code will state the problem you are trying to solve. The goal is to investigate the program 
and fix the bugs. 

Hints: 
  -- You do not need to write any lines of code 
  -- Execute program through GDB to understand how it works 
  -- There are only a few subtle bugs 
 
# Compiling/running the program 

The buggy program (main.cpp)
  -- g++ -std=c++17 -g main.cpp -o prog
  -- Run with gdb: gdb ./prog --tui
  
The verifier 
  -- g++ -std=c++17 -g verifier.cpp -o verifier
  -- Run with ./verifier
  
----
  
# Task 2: Cipher 

In this task, the user is provided a secret message as a string in secretMessage.cpp. This uses a Caesar cipher. 

Important info: 
  -- Each of the characters have been shifted by some unknown integer value either in a positive or negative direction 
  -- The shift value is the same for all of the characters in the string 
  -- The individual characters are represented by intergers (ASCII numbers - the objective is to shift them all up or down such that a secret message in English will 
  be revealed 
  
# Compiling/running the program 

    -- g++ -std=c++17 -g secretMessage.cpp -o prog
    -- Run with gdb: gdb ./prog --tui 
  
  
