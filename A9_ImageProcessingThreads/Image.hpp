#ifndef IMAGE_HPP
#define IMAGE_HPP

// Standard libraries
#include <vector>
#include <thread>

// Third Party Libraries
#include <SFML/Graphics.hpp>


/* TODO: This is the class you are implementing 
 *       You can study this header here to see what
 *       functionality is here. You can also add
 *       any other functions if you think they 
 *       may be useful.
 */     
class CImage{
public:
    // Delete the Default Constructor
    CImage() = delete;
    // Constructor
    CImage(std::string filename);
    // Destructor
    ~CImage();
    // Copy Constructor
    CImage(const CImage& copy);
    // Copy Assignment Constructor
    CImage& operator=(const CImage& rhs);
    // Returns a reference back to the sprite
    sf::Sprite& GetSpriteRef();

    // Returns the dimensions of the image we have loaded
    int GetWidth();
    int GetHeight();

    // This function resets the pixels of the original image
    // that has been loaded
    // It also hows a very quick way of how to 'copy' pixels
    // from one source to the other using std::memcpy
    void ResetPixels();

    // Threaded funtions to enable multi-threading
    void RedPixelRowThread(int row);

    void GrayPixelRowThread(int row); 

    void GrayThresholdFilterRowThread(int row, float threshold); 

    // Each of the following functions allocates
    // memory for an image, and then performs the
    // appropriate transformation on the pixels array
    // to create a new filter.
    void GenerateRedPixelFilter();
    void GenerateGrayPixelFilter();
    void GenerateGrayPixelsThreshold(float threshold);

    // Update and display the texture
    // that will be shown to the user based on the
    // user input
    void ChangeDisplay();

private:
    // sf::Image data structure from the SFML library
    // that will hold the image that we load
    // The original image is tored in this data structure,
    // and we will be modifiying the pixels in each of our
    // image filters.
    sf::Image m_original;
    // Stores the original pixels of the iamge
    sf::Uint8* m_pixels; 
    // Allocate memory for each of the types of filters
    // that the user can generate.
    // Each of the following are 1D-arrays in which you will be
    // updating the pixels from the m_original Image, and appropriately
    // setting the pixels.
    sf::Uint8* m_redPixelFilter;            // red filter
    sf::Uint8* m_grayPixelFilter;           // Gray filter
    sf::Uint8* m_grayThresholdFilter;       // Gray filter, with a threshold

    // NOTE: textures and sprites aren't needed for this assignment,
    //       but could be used for more advanced filters if we were
    //       to move the image and do a 'motion detection' filter for
    //       example.
    // Create a texture from our pixel data
    // Textures are 'images' that are stored in the GPU.
    // This allows you to display images faster
    // because they utilize your graphics card for drawing.
    // The memory on the GPU will thus get updated.
    sf::Texture m_texture;
    // sf::Sprite that we will draw a texture onto
    sf::Sprite m_sprite;

    // Threads collection
    std::vector<std::thread> m_threads;
};

#endif
