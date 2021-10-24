/////////////////////////////////////////////// 
// Compile with: g++ -std=c++17 main.cpp -o prog      
// Run with    : ./prog
// 
// Compile for debugging with:
// g++ -std=c++17 -g main.cpp -o prog
// Run with gdb: gdb ./prog --tui
////////////////////////////////////////////////                                                                                       
// @file main.cpp                             
#include <iostream>     // For general I/O
#include <string>       // std::string data type
#include <vector>       // std::vector data type
#include <filesystem>   // Checking if file exists
#include <fstream>      // Useful for opening files

// Image dimensions
// Recall: Anything in C++ that begins
//         with a '#' sign is read in by
//         the preprocessor before compiling
//         our code.
#define WIDTH 294   // How 'wide' the image is in pixels
#define HEIGHT 251  // How 'high' the image is in pixels
#define CHANNELS 3  // 3 Channels, (R)ed, (G)reen, (B)lue.
   
// The 'brightness' string is  is a series of 
// total of 65 characters. The characters are 
// arranged from 'least bright' to 'most bright' 
// when generating an ASCII representation of an image.
// You are welcome to adjust this string as you see fit
// if you think you can generate a better image.
const std::string brightness = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

/* LoadPPMImage 
 * Input: filename
 *
 * This function loads up a PPM Image. PPM Images
 * can be generated from programs like GIMP 2.0 for
 * free.
 *  
 * The goal is to be able to 'parse' or read in this file 
 * and store the red, green, and blue values, and output
 * the values into a vector.
 *
 * Lines that start with a '#' can be ignored.
 */
std::vector<uint8_t> LoadPPMImage(const std::string filename){
    // Storage of pixels.

    std::vector<uint8_t> pixels;

    // reading the file 
    std::ifstream readFile;
    readFile.open(filename); 
   // if file is open - read line by line 
    if (readFile.is_open()){
        std::string line; 

        int counter = 0; 

        while (getline(readFile, line)){

            if(counter < 4){
                counter++; 

            }
            else{ 
                try{
                int line_converted = std::stoi(line); 
                pixels.push_back(line_converted); 
                //std::cout << line_converted << "\n"; 
            }
                catch (std::exception file_exception) {


            }

            }

       
         

        }
        

    }

    return pixels;
}

/* ConvertPixelsToGray
 * Input: Vector of RGB Pixels
 *
 * Takes in a vector of RGB pixels and converts them to a single 
 * gray value.
 * e.g.
 * RGB RGB RGB (The 'average' value of RGB maps to a single G value)
 * G G G
 */
std::vector<uint8_t> ConvertPixelsToGray(const std::vector<uint8_t>& pixels){
    std::vector<uint8_t> result;

    for (int i = 0; i < pixels.size() - 2; i++){
        //calculating average of each pixel (three numbers that represent RGB values) 
        int pixels_avg = (pixels.at(i) + pixels.at(i+1) + pixels.at(i+2)) / 3; 
        //std::cout << (int)pixels.at(i) << (int)pixels.at(i+1) << (int)pixels.at(i+2) << std::endl; 
        //std::cout << pixels_avg << "\n"; 
        i +=2; 
        result.push_back(pixels_avg); 

    }

    return result;
}

/* MapValueToIndex 
 * (Helper Function)
 * You can create whatever helper functions you like for
 * this assignment, but I used this one (and the other provided
 * functions) in my solution.
 *
 * The goal is to take in your 'brightness string' and then 
 * 'map' a value from 0-255 (your grayscale pixel) to a value
 * between 0 and 64(i.e. each individual character in 
 * your 'brightness string').
 *
 * This will be useful when printing out your characters to
 * the terminal.
 */
char MapValueToIndex(const std::string& chars, uint8_t value, uint8_t start, uint8_t end){
    //converting (0-255) to (0-64) 
    int value_converted = ((double)value/255) * 64; 

    //std::cout << (int)value; 
    //std::cout << value_converted << "\n"; 
    
    //returns converted value 
    return chars.at(value_converted);
}

/* PrintPixelsAsChar
 * Input: vector of grayscale pixel values
 * This function will iterate through the
 * pixel values and print out one character at a time
 * for the WIDTH of an image. Then move down to the next
 * row to print out the characters.
 *
 * The character printed out is a character that maps
 * to the 'brightness string' from the grayscale image.
 *
 */
void PrintPixelsAsChar(const std::vector<uint8_t>& pixels){

    for (int i = 0; i < pixels.size(); i++){
        char pix = MapValueToIndex(brightness, pixels.at(i), 0, 255); 

        if (i%WIDTH == 0){
            std::cout << "\n"; 
        }

        
        std::cout << pix; 

    }

   
}
    

// Entry point of the program.
int main(int argc, char* argv[]){
 
    // The vector ppm will store the R,G,B pixel values
    // of the PPM.
    const std::vector<uint8_t> rgbPixels = LoadPPMImage("test.ppm");
    // The 'grayscale' pixels array converts the 'rgbPixels'
    // to grayscale pixels.
    // So if we have a bunch of pixels as such: 
    std::vector<uint8_t> grayscalePixels = ConvertPixelsToGray(rgbPixels);
    // PrintPixelsAsChar takes in the grayscale Pixels, maps the
    // pixels color to an ASCII character, and then outputs
    // those characters to the terminal.
    PrintPixelsAsChar(grayscalePixels);
  
    return 0; 
}
