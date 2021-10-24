/////////////////////////////////////////////////
// Compile with: g++ -std=c++17 main.cpp BinaryTree.cpp -o prog
// Run with    : ./prog
//
// Compile for debugging with:
// g++ -std=c++17 -g main.cpp BinaryTree.cpp -o prog
// Run with gdb: gdb ./prog --tui
/////////////////////////////////////////////////
// @file main.cpp
// Bring in a header file on our include path
// this happens to be in the standard library
// (i.e. default compiler path)
#include <iostream>
#include "BinaryTree.hpp"
// Tests basic insertion of nodes into a tree
bool unitTest1(){
    BinaryTree tree;
    tree.Insert(4);
    return tree.Exists(4);
}
// Tests less trivial insertion into tree
bool unitTest2(){
    BinaryTree tree;
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(7);
    return tree.Exists(7);
}
// Tests trivial insertion into a tree
bool unitTest3(){
    BinaryTree tree;
    tree.Insert(4);
    tree.Remove(4);
    return tree.Exists(4);
}
// Tests less trivial removal from tree
bool unitTest4(){
    BinaryTree tree;
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(7);
   
    tree.Remove(7);
    return tree.Exists(7);
}
// Tests the sum of the tree
bool unitTest5(){
    BinaryTree tree;
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(7);
   
    int sum = tree.Sum();
    return (sum==21);
}
// Tests the copy constructor
bool unitTest6(){
    BinaryTree tree;
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(7);
    // Copy constructor
    BinaryTree tree2(tree);
   
    return (tree.Sum()==tree2.Sum());
}
// Tests the copy assignemnt operator
bool unitTest7(){
    BinaryTree tree;
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(7);
    // Copy constructor
    BinaryTree tree2;
    tree2 = tree;
    return (tree.Sum()==tree2.Sum());
}
// Tests the printing of the tree
bool unitTest8(){
    BinaryTree tree;
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(7);
   
    tree.Print();
    return tree.Exists(7);
}
// Each unit test returns a result, and we check
// that the unit test matches the expected result
// in order for the test to pass.
void test(int testNumber, bool result, bool expected){
    if(result==expected){
        std::cout << "unitTest " << testNumber << " passed" << std::endl;
    }
    else{
        std::cout << "unitTest " << testNumber << " failed" << std::endl;
    }
}
// Entry point to program 'main' function
int main(int argc, char* argv[]){
    test(1,unitTest1(),true);
    test(2,unitTest2(),true);
    test(3,unitTest3(),false);
    test(4,unitTest4(),false);
    test(5,unitTest5(),true);
    test(6,unitTest6(),true);
    test(7,unitTest7(),true);
    // The fifth test is if the tree prints in order
    // For now, it is sufficient to inspect the tree
    // to see that it has printed out in order
    std::cout << "unitTest8: Is your tree printing in order below?" << std::endl;
    unitTest8();
    return 0;
}
