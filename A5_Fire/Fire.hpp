#ifndef FIRE_HPP
#define FIRE_HPP

// Third Party Libraries
#include <SFML/Graphics.hpp>


// Plain old data (POD) structure
// with primitive data types.
// In this case, I am using this
// struct to store the pixel
// R,G,B, and A(alpha) values.
// Note: I am using the sfml type
//       for Uint (as opposed to uint8_t),
//       to be consistent with their
//       API.       
struct RGBA{
    sf::Uint8 r,g,b,a;
};


// This is my fire class 
// This is responsible for storing
// the pixels for the fire effect,
// and performing the animation.
//
class Fire{
private:
    // Holds all of the fire pixel values
    int* m_firePixels;
    // Dimensions
    unsigned int m_width, m_height; 
public:
    // Input parameter is the 'pixel' position in a 1D array
    Fire(unsigned int width, unsigned int height);

    // Default Destructor
    ~Fire();

    // No copy constructo
    // In C++ you can explicitly delete
    // special member functions to ensure
    // that they cannot be called.
    //
    // In this case 'no copies' will be
    // allowed to be created of our object.
    // link: https://en.cppreference.com/w/cpp/language/function#Deleted_functions
    Fire(const Fire& Fire) = delete;

    // Input parameter is the 'pixel' position in a 1D array
    // 
    // This function is responsible for updating the pixel colors
    void SpreadFire(int from);

    // Input parameter is the 'pixel' position in a 1D array
    // 
    // This function is responsible for updating the pixel colors
    void SpreadFireWave(int from);

    // Iterate through each pixel. This function will call
    // 'SpreadFireWave'.
    void DoFire();

    // Render the fire
    void Render(sf::RenderWindow& window);
};


#endif
