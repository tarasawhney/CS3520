#include "Image.hpp"

// C++ Standard Libraries
#include <iostream>
#include <thread>

// C Libraries
#include <cstring> // for memcpy

// Third Party Libraries
#include <SFML/Graphics.hpp>


// Constructor
// Reads in one file
CImage::CImage(std::string filename){
    // Attempt to load the file.
    // Note: We can do this within an 'if' statement, and
    //       then directtly evaluate the result.
    //       If the .loadFromFile function returns false,
    //       thene we take the opposite value(The ! operator)
    //       and then execute the associated code block.
    //       This will then terminate the program if this fails.
    if(!m_original.loadFromFile(filename.c_str())){
        std::cout << "image did not load!" << std::endl;
        exit(1);
    }
    // Create a texture from our image
    m_texture.loadFromImage(m_original);
    // Retrieve all of the pixels from the image into an array
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;   
    m_pixels = new sf::Uint8[pixelCount];
    // Copy the pixels from the image, into the newly
    // allocated m_pixels array.
    std::memcpy(m_pixels,m_original.getPixelsPtr(),pixelCount);
    // Assign our texture to this sprite.
    m_sprite.setTexture(m_texture);

    // Generate all of the filters
    GenerateRedPixelFilter();
    GenerateGrayPixelFilter();
    GenerateGrayPixelsThreshold(128);
}

// Destructor that must delete any memory
// that we have dynamically allocated.
// For objects like sf::CImage or sf::Sprite, 
// the SFML library will call those destructors
// automatically when this object is being destroyed.
CImage::~CImage(){
    
    // Delete any memory that has been allocated
    delete[] m_pixels; 
    delete[] m_redPixelFilter;
    delete[] m_grayPixelFilter;
    delete[] m_grayThresholdFilter;
}

// Copy Constructor
CImage::CImage(const CImage& copy){
    // TODO: Perform a Deep Copy
    m_pixels = copy.m_pixels; 
    //deep copy red filter
    m_redPixelFilter = copy.m_redPixelFilter;
    //deep copy gray pixel filter 
    m_grayPixelFilter = copy.m_grayPixelFilter; 
    //deep copy threshold filter 
    m_grayThresholdFilter = copy.m_grayThresholdFilter; 
    //copy original filter 
    m_original = copy.m_original; 
    m_sprite = copy.m_sprite; 
    m_texture = copy.m_texture;


}

// Copy Assignment Constructor
CImage& CImage::operator=(const CImage& rhs){
    // TODO: Write Copy Assignment Constructor
    m_pixels = rhs.m_pixels; 
    m_redPixelFilter = rhs.m_redPixelFilter;
    m_grayPixelFilter = rhs.m_grayPixelFilter; 
    m_grayThresholdFilter = rhs.m_grayThresholdFilter; 
    m_original = rhs.m_original; 
    m_sprite = rhs.m_sprite; 
    m_texture = rhs.m_texture; 


    return *this;
}

// Get a reference to the sprite stored internally
// that we are going to draw on.
// Recall this sprite has the texture data associated with it.
sf::Sprite& CImage::GetSpriteRef(){
    return m_sprite;
}
// Return the 'x' or 'height' dimension of the image
int CImage::GetWidth(){
    return m_original.getSize().x;
}
// Return the 'y' or 'height' dimension of the image
int CImage::GetHeight(){
    return m_original.getSize().y;
}



void CImage::RedPixelRowThread(int row){
    // TODO:
    //retrieve and cache the size of imageWidth 
    int imageWidth = m_original.getSize().x;

    //iterate through every 4 pixels in the row 
    for(int x = row*imageWidth*4; x<(row+1)*imageWidth*4; x+=4){
        //retrieve the red pixel at position defined by 
        //the row and the column 
        sf::Uint8 r = m_original.getPixelsPtr()[x];
        sf::Uint8 g = m_original.getPixelsPtr()[x+1]; 
        sf::Uint8 b = m_original.getPixelsPtr()[x+2]; 
        //sf::Uint8 a = m_original.getPixelsPtr()[x+3]; 

        //update unique pixel location with filter
        m_redPixelFilter[x+0] = r; 
        m_redPixelFilter[x+1] = 0; 
        m_redPixelFilter[x+2] = 0; 
        m_redPixelFilter[x+3] = 255; 

    }
} 


// (1) Allocate memory for m_redPixelFilter
// (2) Iterate through each of the pixels and
//     assign the G and B values to 0, while preserving
//     the R and Alpha values.
void CImage::GenerateRedPixelFilter(){ 

    // TODO:
    //get the pixel count 
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4; 
    //allocate memory for the m_redPixelFilter
    m_redPixelFilter = new sf::Uint8[pixelCount]; 

    //create a thread for every row in our image 
    for (int y=0; y<m_original.getSize().y; y++){
        //we launch the thread with a member function
        //so that each row will be operated on to 
        //perform the image processing 
        m_threads.push_back(std::thread(
                    &CImage::RedPixelRowThread, 
                    this, 
                    y)); 
        
    }
  
}

void CImage::GrayPixelRowThread(int row){
    int imageWidth = m_original.getSize().x; 

    //iterate through every 4 pixels in the row 
    for(int x = row*imageWidth*4; x<(row+1)*imageWidth*4; x+=4){
        //retrieve the red pixel at position defined by 
        //the row and the column 
        sf::Uint8 r = m_original.getPixelsPtr()[x];
        sf::Uint8 g = m_original.getPixelsPtr()[x+1]; 
        sf::Uint8 b = m_original.getPixelsPtr()[x+2]; 
        sf::Uint8 a = m_original.getPixelsPtr()[x+3]; 

        sf::Uint8 avg_val = r * 0.29 + g * 0.59 + b * 0.11;

        m_grayPixelFilter[x] = avg_val;
        m_grayPixelFilter[x + 1] = avg_val;
        m_grayPixelFilter[x + 2] = avg_val;
        m_grayPixelFilter[x + 3] = a;
        
         
    }
    
} 



// (1) Allocate memory for m_grayPixelFilter
// (2) Iterate through each of the pixels 
//     a.) Compute an average of the pixel value. 
//         R*0.29 + G*0.59 + B*0.11
//     b.) Then assign R, G, and B values each to the average pixel value. 
void CImage::GenerateGrayPixelFilter(){
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4; 

    //allocate memory for gray pixel filter 
    m_grayPixelFilter = new sf::Uint8[pixelCount]; 

    for(int y=0; y<m_original.getSize().y; y++){
        m_threads.push_back(std::thread(
                    &CImage::GrayPixelRowThread, 
                    this, 
                    y)); 
        
    }
    for(int i=0; i<m_threads.size(); i++){
        m_threads[i].join();

    }
    m_threads.erase(m_threads.begin(), m_threads.end()); 
    // TODO:

}
void CImage::GrayThresholdFilterRowThread(int row, float threshold){

    int imageWidth = m_original.getSize().x;

    for (int x = row*imageWidth*4; x<(row+1)*imageWidth*4; x+=4){
        sf::Uint8 r = m_original.getPixelsPtr()[x];
        sf::Uint8 g = m_original.getPixelsPtr()[x+1]; 
        sf::Uint8 b = m_original.getPixelsPtr()[x+2]; 
        sf::Uint8 a = m_original.getPixelsPtr()[x+3]; 

        sf::Uint8 avg_val = r * 0.29 + g * 0.59 + b * 0.11;

        m_grayThresholdFilter[x] = avg_val;
        m_grayThresholdFilter[x + 1] = avg_val;
        m_grayThresholdFilter[x + 2] = avg_val;
        m_grayThresholdFilter[x + 3] = a;



       if (avg_val < threshold){
        m_grayThresholdFilter[x] = 0; 
        m_grayThresholdFilter[x+1] = 0; 
        m_grayThresholdFilter[x+2] = 0; 
        m_grayThresholdFilter[x+3] = a; 
       }
        //x += 3; 
    }

}
// (1) Allocate memory for m_grayThresholdFilter 
// (2) Iterate through each of the pixels 
//     a.) Compute an average of the pixel value. 
//         R*0.29 + G*0.59 + B*0.11
//     b.) Then assign R, G, and B values each to the average pixel value. 
// (3) If the average pixel value < threshold
//     a.) Set, R, G, and B to (0,0,0)
void CImage::GenerateGrayPixelsThreshold(float threshold){
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4; 

    //allocate memory for the gray threshold filter 
    m_grayThresholdFilter = new sf::Uint8[pixelCount]; 

    //create a thread for every row in our image
    for(int y=0; y<m_original.getSize().y; y++){
        m_threads.push_back(std::thread(
                    &CImage::GrayThresholdFilterRowThread, 
                    this, 
                    y, 
                    threshold));
    }
    for (int i=0; i<m_threads.size(); i++){
        m_threads[i].join(); 
    }
    m_threads.erase(m_threads.begin(), m_threads.end()); 
// TODO:
    
}



// Based on the key pressed change the filter
void CImage::ChangeDisplay(){

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
        std::cout << "m_pixels sf::Keyboard::Num1" << std::endl;
        m_texture.update(m_pixels);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        std::cout << "m_redPixel Filter sf::Keyboard::Num2" << std::endl;
        m_texture.update(m_redPixelFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
        std::cout << "m_grayPixelFilter sf::Keyboard::Num3" << std::endl;
        m_texture.update(m_grayPixelFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
        std::cout << "m_grayPixelFilter threshold sf::Keyboard::Num4" << std::endl;
        m_texture.update(m_grayThresholdFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
        std::cout << "(Optional) Add your own" << std::endl;
        //m_texture.update(...);
    }
}


// Restore the m_pixels to 
void CImage::ResetPixels(){
    
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;   
    m_pixels = new sf::Uint8[pixelCount];   
    // Note to students that std::memcpy is a faster way to do a copy
    // if you need to copy a large chunk of memory (i.e. an array)
    // all at once. Doing the large copy all at once is faster than
    // iterating through an array and copying every element one at a time.
    std::memcpy(m_pixels,m_original.getPixelsPtr(),pixelCount);    
}
