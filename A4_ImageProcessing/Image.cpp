#include "Image.hpp"

// C++ Standard Libraries
#include <iostream>

// C Libraries
#include <cstring> // for memcpy

// Third Party Libraries
#include <SFML/Graphics.hpp>

//Math
#include <cmath>

// Constructor
// Reads in one file
CImage::CImage(std::string filename)
{
    // Attempt to load the file.
    // Note: We can do this within an 'if' statement, and
    //       then directtly evaluate the result.
    //       If the .loadFromFile function returns false,
    //       thene we take the opposite value(The ! operator)
    //       and then execute the associated code block.
    //       This will then terminate the program if this fails.
    if (!m_original.loadFromFile(filename.c_str()))
    {
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
    std::memcpy(m_pixels, m_original.getPixelsPtr(), pixelCount);
    // Assign our texture to this sprite.
    m_sprite.setTexture(m_texture);

    // Generate all of the filters
    GenerateRedPixelFilter();
    GenerateGrayPixelFilter();
    GenerateGrayPixelsThreshold(128);
    GenerateConvolutionBlurKernel();
    GenerateConvolutionGaussianBlurKernel();
    GenerateConvolutionEdgeDetectKernel();
}

// Destructor that must delete any memory
// that we have dynamically allocated.
// For objects like sf::CImage or sf::Sprite,
// the SFML library will call those destructors
// automatically when this object is being destroyed.
CImage::~CImage()
{

    // Delete any memory that has been allocated
    delete[] m_pixels;
    delete[] m_redPixelFilter;
    delete[] m_grayPixelFilter;
    delete[] m_grayThresholdFilter;
    delete[] m_convolutionBlurFilter;
    delete[] m_gaussianBlurFilter;
    delete[] m_edgeFilter;
}

// Copy Constructor
CImage::CImage(const CImage &copy)
{
    // TODO: Perform a Deep Copy
    m_pixels = copy.m_pixels;
    //deep copy red pixel filter
    m_redPixelFilter = copy.m_redPixelFilter;
    //deep copy gray pixel filter
    m_grayPixelFilter = copy.m_grayPixelFilter;
    //deep copy threshold filter
    m_grayThresholdFilter = copy.m_grayThresholdFilter;
    m_convolutionBlurFilter = copy.m_convolutionBlurFilter;
    m_gaussianBlurFilter = copy.m_gaussianBlurFilter;
    m_edgeFilter = copy.m_edgeFilter;
    //deep copy original filter
    m_original = copy.m_original;
    //deep copy sprite
    m_sprite = copy.m_sprite;
    //deep copy texture
    m_texture = copy.m_texture;
}

// Copy Assignment Constructor
CImage &CImage::operator=(const CImage &rhs)
{
    // TODO: Write Copy Assignment Constructor
    m_pixels = rhs.m_pixels;
    //deep copy red pixel filter
    m_redPixelFilter = rhs.m_redPixelFilter;
    //deep copy gray pixel filter
    m_grayPixelFilter = rhs.m_grayPixelFilter;
    //deep copy threshold filter
    m_grayThresholdFilter = rhs.m_grayThresholdFilter;
    m_convolutionBlurFilter = rhs.m_convolutionBlurFilter;
    m_gaussianBlurFilter = rhs.m_gaussianBlurFilter;
    m_edgeFilter = rhs.m_edgeFilter;
    //deep copy original filter
    m_original = rhs.m_original;
    //deep copy sprite
    m_sprite = rhs.m_sprite;
    //deep copy texture
    m_texture = rhs.m_texture;
    return *this;
}

// Get a reference to the sprite stored internally
// that we are going to draw on.
// Recall this sprite has the texture data associated with it.
sf::Sprite &CImage::GetSpriteRef()
{
    return m_sprite;
}
// Return the 'x' or 'height' dimension of the image
int CImage::GetWidth()
{
    return m_original.getSize().x;
}
// Return the 'y' or 'height' dimension of the image
int CImage::GetHeight()
{
    return m_original.getSize().y;
}

// (1) Allocate memory for m_redPixelFilter
// (2) Iterate through each of the pixels and
//     assign the G and B values to 0, while preserving
//     the R and Alpha values.
void CImage::GenerateRedPixelFilter()
{
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;
    m_redPixelFilter = new sf::Uint8[pixelCount];

    //123 42 55 32 11 13 22 50 19
    //123 0 0 32 11 0 0 50 19

    for (int i = 0; i < pixelCount; i++)
    {
        sf::Uint8 red_value = m_pixels[i];
        sf::Uint8 green_value = 0;
        sf::Uint8 blue_value = 0;
        sf::Uint8 alpha_value = m_pixels[i + 3];

        m_redPixelFilter[i] = red_value;
        m_redPixelFilter[i + 1] = green_value;
        m_redPixelFilter[i + 2] = blue_value;
        m_redPixelFilter[i + 3] = alpha_value;

        i += 3;
    }

    // TODO:
}

// (1) Allocate memory for m_grayPixelFilter
// (2) Iterate through each of the pixels
//     a.) Compute an average of the pixel value.
//         R*0.29 + G*0.59 + B*0.11
//     b.) Then assign R, G, and B values each to the average pixel value.
void CImage::GenerateGrayPixelFilter()
{
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;
    m_grayPixelFilter = new sf::Uint8[pixelCount];

    for (int i = 0; i < pixelCount; i++)
    {

        sf::Uint8 red_value = m_pixels[i];
        sf::Uint8 green_value = m_pixels[i + 1];
        sf::Uint8 blue_value = m_pixels[i + 2];
        sf::Uint8 alpha_value = m_pixels[i + 3];

        sf::Uint8 avg_val = red_value * 0.29 + green_value * 0.59 + blue_value * 0.11;

        m_grayPixelFilter[i] = avg_val;
        m_grayPixelFilter[i + 1] = avg_val;
        m_grayPixelFilter[i + 2] = avg_val;
        m_grayPixelFilter[i + 3] = alpha_value;

        i += 3;
    }

    // TODO:
}

// (1) Allocate memory for m_grayThresholdFilter
// (2) Iterate through each of the pixels
//     a.) Compute an average of the pixel value.
//         R*0.29 + G*0.59 + B*0.11
//     b.) Then assign R, G, and B values each to the average pixel value.
// (3) If the average pixel value < threshold
//     a.) Set, R, G, and B to (0,0,0)
void CImage::GenerateGrayPixelsThreshold(float threshold)
{
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;
    m_grayThresholdFilter = new sf::Uint8[pixelCount];

    for (int i = 0; i < pixelCount; i++)
    {

        sf::Uint8 red_value = m_pixels[i];
        sf::Uint8 green_value = m_pixels[i + 1];
        sf::Uint8 blue_value = m_pixels[i + 2];
        sf::Uint8 alpha_value = m_pixels[i + 3];

        sf::Uint8 avg_val = red_value * 0.29 + green_value * 0.59 + blue_value * 0.11;

        m_grayThresholdFilter[i] = avg_val;
        m_grayThresholdFilter[i + 1] = avg_val;
        m_grayThresholdFilter[i + 2] = avg_val;
        m_grayThresholdFilter[i + 3] = alpha_value;

        if (avg_val < threshold)
        {

            m_grayThresholdFilter[i] = 0;
            m_grayThresholdFilter[i + 1] = 0;
            m_grayThresholdFilter[i + 2] = 0;
            m_grayThresholdFilter[i + 3] = alpha_value;
        }

        i += 3;
    }
    // TODO:
}

// (1) Allocate memory for m_convolutionBlurFilter
// (2) Figure out the pixel
//    a.) Use the Box Blur formula: https://en.wikipedia.org/wiki/Kernel_(image_processing)
//    b.) Box blur is taking the pixels around the current pixel we are iterating through
//        and then computing an average value.
//        i.) If a pixel is potentially out of range (i.e. the edge) we can just ignore it)
void CImage::GenerateConvolutionBlurKernel()
{
    // TODO:
    // Allocate Memory
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;
    m_convolutionBlurFilter = new sf::Uint8[pixelCount];

    // Get the current position
    for (int i = 0; i < pixelCount; i++)
    {
        // Get the current_x position
        //int current_x = (i%m_original.getSize().x) / 4;
        int current_x = ((i / 4) % m_original.getSize().x);

        // Get the current_y position
        //int current_y = floor(i/m_original.getSize().x);
        int current_y = floor((i / 4) / m_original.getSize().x);
        //std::cout << current_x << " " << current_y << std::endl;
        //std::cout << i << " " << pixelCount << std::endl;
        //std::cout << m_original.getSize().x << " " << m_original.getSize().y << std::endl;
        // Ensure that there are surrounding pixels.
        // Find if the current location has all 9 surrounding pixels (including self)
        bool at_edge = false;
        if (current_x == (m_original.getSize().x / 4) - 1 || current_x == 0)
        {
            at_edge = true;
        }
        if (current_y == m_original.getSize().y - 1 || current_y == 0)
        {
            at_edge = true;
        }

        if (!at_edge)
        {
            // Get the surrounding pixels
            sf::Color top_left_pixel = m_original.getPixel(current_x - 1, current_y - 1);
            sf::Color top_top_pixel = m_original.getPixel(current_x, current_y - 1);
            sf::Color top_right_pixel = m_original.getPixel(current_x + 1, current_y - 1);
            sf::Color mid_left_pixel = m_original.getPixel(current_x - 1, current_y);
            sf::Color mid_mid_pixel = m_original.getPixel(current_x, current_y);
            sf::Color mid_right_pixel = m_original.getPixel(current_x + 1, current_y);
            sf::Color bottom_left_pixel = m_original.getPixel(current_x - 1, current_y + 1);
            sf::Color bottom_bottom_pixel = m_original.getPixel(current_x, current_y + 1);
            sf::Color bottom_right_pixel = m_original.getPixel(current_x + 1, current_y + 1);

            // Calculate the average of the surroudning pixels
            sf::Uint8 average_red_of_surrounding_pixels = (top_left_pixel.r + top_top_pixel.r + top_right_pixel.r + mid_left_pixel.r + mid_mid_pixel.r + mid_right_pixel.r + bottom_left_pixel.r + bottom_bottom_pixel.r + bottom_right_pixel.r) / 9;
            sf::Uint8 average_green_of_surrounding_pixels = (top_left_pixel.g + top_top_pixel.g + top_right_pixel.g + mid_left_pixel.g + mid_mid_pixel.g + mid_right_pixel.g + bottom_left_pixel.g + bottom_bottom_pixel.g + bottom_right_pixel.g) / 9;
            sf::Uint8 average_blue_of_surrounding_pixels = (top_left_pixel.b + top_top_pixel.b + top_right_pixel.b + mid_left_pixel.b + mid_mid_pixel.b + mid_right_pixel.b + bottom_left_pixel.b + bottom_bottom_pixel.b + bottom_right_pixel.b) / 9;
            //sf::Uint8 average_alpha_of_surrounding_pixels = (top_left_pixel.a + top_top_pixel.a + top_right_pixel.a + mid_left_pixel.a + mid_mid_pixel.a + mid_right_pixel.a + bottom_left_pixel.a + bottom_bottom_pixel.a + bottom_right_pixel.a) / 9;

            // Calculate the new value of the first pixel (The average of the surrounding pixels)
            sf::Uint8 new_value_of_red = average_red_of_surrounding_pixels;
            sf::Uint8 new_value_of_green = average_green_of_surrounding_pixels;
            sf::Uint8 new_value_of_blue = average_blue_of_surrounding_pixels;
            //sf::Uint8 new_value_of_alpha = average_alpha_of_surrounding_pixels;

            // Update he filter pixel
            m_convolutionBlurFilter[i] = new_value_of_red;
            m_convolutionBlurFilter[i + 1] = new_value_of_green;
            m_convolutionBlurFilter[i + 2] = new_value_of_blue;
            m_convolutionBlurFilter[i + 3] = m_pixels[i+3];
            //std::cout << "checkmark" << std::endl;
        }
        else
        {
            // Get the original Color value
            sf::Uint8 new_value_of_red = m_pixels[i];
            sf::Uint8 new_value_of_green = m_pixels[i + 1];
            sf::Uint8 new_value_of_blue = m_pixels[i + 2];
            sf::Uint8 new_value_of_alpha = m_pixels[i + 3];

            // Udpate ot eh the original color
            m_convolutionBlurFilter[i] = new_value_of_red;
            m_convolutionBlurFilter[i + 1] = new_value_of_green;
            m_convolutionBlurFilter[i + 2] = new_value_of_blue;
            m_convolutionBlurFilter[i + 3] = new_value_of_alpha;
        }

        i += 3;
    }
}

// (1) Allocate memory for m_gaussianBlurFilter
// (2) Figure out the pixel
//    a.) Use the Gaussian Blur 3x3 formula: https://en.wikipedia.org/wiki/Kernel_(image_processing)
//    b.) Gaussian blur is taking the pixels around the current pixel we are iterating through
//        and then computing a weighted avareage value.
//        Note: Some of the pixels are are multipled by 2 or 4, and then the rest 1.
//              The total 'sum' of the values is then what we divide by (i.e. 16).
//        i.) If a pixel is potentially out of range (i.e. the edge) we can just ignore it)
void CImage::GenerateConvolutionGaussianBlurKernel()
{
    // Allocate Memory
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;
    m_gaussianBlurFilter = new sf::Uint8[pixelCount];

    // Get the current position
    for (int i = 0; i < pixelCount; i++)
    {
        // Get the current_x position
        //int current_x = (i%m_original.getSize().x) / 4;
        int current_x = ((i / 4) % m_original.getSize().x);

        // Get the current_y position
        //int current_y = floor(i/m_original.getSize().x);
        int current_y = floor((i / 4) / m_original.getSize().x);
        //std::cout << current_x << " " << current_y << std::endl;
        //std::cout << i << " " << pixelCount << std::endl;
        //std::cout << m_original.getSize().x << " " << m_original.getSize().y << std::endl;
        // Ensure that there are surrounding pixels.
        // Find if the current location has all 9 surrounding pixels (including self)
        bool at_edge = false;
        if (current_x == (m_original.getSize().x / 4) - 1 || current_x == 0)
        {
            at_edge = true;
        }
        if (current_y == m_original.getSize().y - 1 || current_y == 0)
        {
            at_edge = true;
        }

        if (!at_edge)
        {
            // Get the surrounding pixels
            sf::Color top_left_pixel = m_original.getPixel(current_x - 1, current_y - 1);
            sf::Color top_top_pixel = m_original.getPixel(current_x, current_y - 1);
            sf::Color top_right_pixel = m_original.getPixel(current_x + 1, current_y - 1);
            sf::Color mid_left_pixel = m_original.getPixel(current_x - 1, current_y);
            sf::Color mid_mid_pixel = m_original.getPixel(current_x, current_y);
            sf::Color mid_right_pixel = m_original.getPixel(current_x + 1, current_y);
            sf::Color bottom_left_pixel = m_original.getPixel(current_x - 1, current_y + 1);
            sf::Color bottom_bottom_pixel = m_original.getPixel(current_x, current_y + 1);
            sf::Color bottom_right_pixel = m_original.getPixel(current_x + 1, current_y + 1);

            // Calculate the average of the surroudning pixels
            sf::Uint8 average_red_of_surrounding_pixels = (top_left_pixel.r + top_top_pixel.r * 2 + top_right_pixel.r + mid_left_pixel.r * 2 + mid_mid_pixel.r * 4 + mid_right_pixel.r * 2 + bottom_left_pixel.r + bottom_bottom_pixel.r * 2 + bottom_right_pixel.r) / 16;
            sf::Uint8 average_green_of_surrounding_pixels = (top_left_pixel.g + top_top_pixel.g * 2 + top_right_pixel.g + mid_left_pixel.g * 2 + mid_mid_pixel.g * 4 + mid_right_pixel.g * 2 + bottom_left_pixel.g + bottom_bottom_pixel.g * 2 + bottom_right_pixel.g) / 16;
            sf::Uint8 average_blue_of_surrounding_pixels = (top_left_pixel.b + top_top_pixel.b * 2 + top_right_pixel.b + mid_left_pixel.b * 2 + mid_mid_pixel.b * 4 + mid_right_pixel.b * 2 + bottom_left_pixel.b + bottom_bottom_pixel.b * 2 + bottom_right_pixel.b) / 16;
            //sf::Uint8 average_alpha_of_surrounding_pixels = (top_left_pixel.a + top_top_pixel.a * 2 + top_right_pixel.a + mid_left_pixel.a * 2 + mid_mid_pixel.a * 4 + mid_right_pixel.a * 2 + bottom_left_pixel.a + bottom_bottom_pixel.a * 2 + bottom_right_pixel.a) / 16;

            // Calculate the new value of the first pixel (The average of the surrounding pixels)
            sf::Uint8 new_value_of_red = average_red_of_surrounding_pixels;
            sf::Uint8 new_value_of_green = average_green_of_surrounding_pixels;
            sf::Uint8 new_value_of_blue = average_blue_of_surrounding_pixels;
            //sf::Uint8 new_value_of_alpha = average_alpha_of_surrounding_pixels;

            // Update he filter pixel
            m_gaussianBlurFilter[i] = new_value_of_red;
            m_gaussianBlurFilter[i + 1] = new_value_of_green;
            m_gaussianBlurFilter[i + 2] = new_value_of_blue;
            m_gaussianBlurFilter[i + 3] = m_pixels[i+3];
            //std::cout << "checkmark" << std::endl;
        }
        else
        {
            // Get the original Color value
            sf::Uint8 new_value_of_red = m_pixels[i];
            sf::Uint8 new_value_of_green = m_pixels[i + 1];
            sf::Uint8 new_value_of_blue = m_pixels[i + 2];
            sf::Uint8 new_value_of_alpha = m_pixels[i + 3];

            // Udpate ot eh the original color
            m_gaussianBlurFilter[i] = new_value_of_red;
            m_gaussianBlurFilter[i + 1] = new_value_of_green;
            m_gaussianBlurFilter[i + 2] = new_value_of_blue;
            m_gaussianBlurFilter[i + 3] = new_value_of_alpha;
        }

        i += 3;
    }
}

// (1) Allocate memory for m_edgeFilter
// (2) Figure out the pixel
//    a.) First convert pixels to grayscale
//        i.) Can use sf::Image graySource.create(...,...,m_grayPixelFilter);
//    b.) Use the 'edge detection': https://en.wikipedia.org/wiki/Kernel_(image_processing)
//    b.) edge detection is taking the pixels around the current pixel we are iterating through
//        and then zero'ing out some of the pixels..
//        i.) If a pixel is potentially out of range (i.e. the edge) we can just ignore it)
void CImage::GenerateConvolutionEdgeDetectKernel()

{
    sf::Image graySource;
    graySource.create(m_original.getSize().x, m_original.getSize().y, m_grayPixelFilter);
    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;
    m_edgeFilter = new sf::Uint8[pixelCount];

    for (int i = 0; i < pixelCount; i++)
    {
        // Get the current_x position
        //int current_x = (i%m_original.getSize().x) / 4;
        int current_x = ((i / 4) % m_original.getSize().x);

        // Get the current_y position
        //int current_y = floor(i/m_original.getSize().x);
        int current_y = floor((i / 4) / m_original.getSize().x);
        //std::cout << current_x << " " << current_y << std::endl;
        //std::cout << i << " " << pixelCount << std::endl;
        //std::cout << m_original.getSize().x << " " << m_original.getSize().y << std::endl;
        // Ensure that there are surrounding pixels.
        // Find if the current location has all 9 surrounding pixels (including self)
        bool at_edge = false;
        if (current_x == (m_original.getSize().x / 4) - 1 || current_x == 0)
        {
            at_edge = true;
        }
        if (current_y == m_original.getSize().y - 1 || current_y == 0)
        {
            at_edge = true;
        }

        if (!at_edge)
        {
            // Get the surrounding pixels
            sf::Color top_left_pixel = graySource.getPixel(current_x - 1, current_y - 1);
            sf::Color top_top_pixel = graySource.getPixel(current_x, current_y - 1);
            sf::Color top_right_pixel = graySource.getPixel(current_x + 1, current_y - 1);
            sf::Color mid_left_pixel = graySource.getPixel(current_x - 1, current_y);
            sf::Color mid_mid_pixel = graySource.getPixel(current_x, current_y);
            sf::Color mid_right_pixel = graySource.getPixel(current_x + 1, current_y);
            sf::Color bottom_left_pixel = graySource.getPixel(current_x - 1, current_y + 1);
            sf::Color bottom_bottom_pixel = graySource.getPixel(current_x, current_y + 1);
            sf::Color bottom_right_pixel = graySource.getPixel(current_x + 1, current_y + 1);

            // Calculate the average of the surroudning pixels
            sf::Uint8 average_red_of_surrounding_pixels = (top_left_pixel.r * -1 + top_top_pixel.r * -1 + top_right_pixel.r * -1 + mid_left_pixel.r * -1 + mid_mid_pixel.r * 8 + mid_right_pixel.r * -1 + bottom_left_pixel.r * -1 + bottom_bottom_pixel.r * -1 + bottom_right_pixel.r * -1);
            sf::Uint8 average_green_of_surrounding_pixels = (top_left_pixel.g * -1 + top_top_pixel.g * -1 + top_right_pixel.g * -1 + mid_left_pixel.g * -1 + mid_mid_pixel.g * 8 + mid_right_pixel.g * -1 + bottom_left_pixel.g * -1 + bottom_bottom_pixel.g * -1 + bottom_right_pixel.g * -1);
            sf::Uint8 average_blue_of_surrounding_pixels = (top_left_pixel.b * -1 + top_top_pixel.b * -1 + top_right_pixel.b * -1 + mid_left_pixel.b * -1 + mid_mid_pixel.b * 8 + mid_right_pixel.b * -1 + bottom_left_pixel.b * -1 + bottom_bottom_pixel.b * -1 + bottom_right_pixel.b * -1);
            //sf::Uint8 average_alpha_of_surrounding_pixels = (top_left_pixel.a * -1 + top_top_pixel.a * -1 + top_right_pixel.a * -1 + mid_left_pixel.a * -1 + mid_mid_pixel.a * 8 + mid_right_pixel.a * -1 + bottom_left_pixel.a * -1 + bottom_bottom_pixel.a * -1 + bottom_right_pixel.a * -1);

            // Calculate the new value of the first pixel (The average of the surrounding pixels)
            sf::Uint8 new_value_of_red = average_red_of_surrounding_pixels;
            sf::Uint8 new_value_of_green = average_green_of_surrounding_pixels;
            sf::Uint8 new_value_of_blue = average_blue_of_surrounding_pixels;
            //sf::Uint8 new_value_of_alpha = average_alpha_of_surrounding_pixels;

            // Update he filter pixel
            m_edgeFilter[i] = new_value_of_red;
            m_edgeFilter[i + 1] = new_value_of_green;
            m_edgeFilter[i + 2] = new_value_of_blue;
            m_edgeFilter[i + 3] = m_pixels[i + 3];
            //std::cout << "checkmark" << std::endl;
        }
        else
        {
            // Get the original Color value
            sf::Uint8 new_value_of_red = m_pixels[i];
            sf::Uint8 new_value_of_green = m_pixels[i + 1];
            sf::Uint8 new_value_of_blue = m_pixels[i + 2];
            sf::Uint8 new_value_of_alpha = m_pixels[i + 3];

            // Udpate ot eh the original color
            m_edgeFilter[i] = new_value_of_red;
            m_edgeFilter[i + 1] = new_value_of_green;
            m_edgeFilter[i + 2] = new_value_of_blue;
            m_edgeFilter[i + 3] = new_value_of_alpha;
        }

        i += 3;
    }
}

// Based on the key pressed change the filter
void CImage::ChangeDisplay()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        std::cout << "m_pixels sf::Keyboard::Num1" << std::endl;
        m_texture.update(m_pixels);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        std::cout << "m_redPixel Filter sf::Keyboard::Num2" << std::endl;
        m_texture.update(m_redPixelFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        std::cout << "m_grayPixelFilter sf::Keyboard::Num3" << std::endl;
        m_texture.update(m_grayPixelFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        std::cout << "m_grayPixelFilter sf::Keyboard::Num4" << std::endl;
        m_texture.update(m_grayThresholdFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        std::cout << "m_convolutionBlurFilter sf::Keyboard::Num5" << std::endl;
        m_texture.update(m_convolutionBlurFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
    {
        std::cout << "m_gaussianBlurFilter sf::Keyboard::Num6" << std::endl;
        m_texture.update(m_gaussianBlurFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
    {
        std::cout << "m_edgeFilter sf::Keyboard::Num7" << std::endl;
        m_texture.update(m_edgeFilter);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
    {
        std::cout << "(Optional) Add your own" << std::endl;
        //m_texture.update(...);
    }
}

// Restore the m_pixels to
void CImage::ResetPixels()
{

    size_t pixelCount = m_original.getSize().x * m_original.getSize().y * 4;
    m_pixels = new sf::Uint8[pixelCount];
    // Note to students that std::memcpy is faster than iteration of loop
    // avoid using a for-loop.
    std::memcpy(m_pixels, m_original.getPixelsPtr(), pixelCount);
}
