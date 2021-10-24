//Fire.cpp
//TODO: Your implementation here

//Packages 
#include <iostream> 
#include <vector> 
#include <string> 
#include <math.h>
#include "Fire.hpp"
#include <stdlib.h>
#include<time.h>

//define width and height 

// Iterate through each pixel. This function will call
// 'SpreadFireWave'.

// Initialize several structs of color
// Colors interpolated using this tool: https://meyerweb.com/eric/tools/color-blend/#538DD6:C5D9F1:1:rgbd

//RGBA palette w minor edits 
static RGBA g_firePallete[] = {
    {3,3,3,3}, // White is the hottest - changed this to make the screen black 
    {140,179,228,255},
    {197,217,241,255},
    {226,236,248,255},
    {201,56,30, 255},
    {255,255,229,255},
    {255,255,202,255},
    {255,255,102,255},
    {254,255,1,255},
    {255,224,1,255},
    {255,192,0,255},
    {254,96,1,255},
    {253,0,2,255},
    {223,96,97,255},
    {192,192,192,255},
    {128,128,128,255},
    {64,64,64,255},
    {255,32,32,255},
    {255,255,255}          // Black is the darkest
};

//creating the constructor 
Fire::Fire(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;

    size_t pixelCount = m_width * m_height;
    m_firePixels = new int[pixelCount]; //initializing 

    for (int i = 0; i < m_width * m_height; i++) {
        m_firePixels[i] = 0;
    }

    for (int i = 0; i < m_width; i++) {
        m_firePixels[m_width * (m_height - 1) + i] = 36; //36 colors in palette
    }
}

Fire::~Fire(){
    delete[] m_firePixels; //frees up space
}



void Fire::DoFire(){
    for(int i = 0; i < m_width; i++){
        for (int j = 1; j < m_height; j++){
            SpreadFire(j * m_width + i); //calling SpreadFire function on every single pixel except for bottom
        }

    } 
}   
void Fire::SpreadFire(int from){

        if(m_firePixels[from] == 0) { //represents the color of each pixel 
            m_firePixels[from - m_width] = 0; //if the color is sky blue, pixel above doesn't change 
        } else {
            //otherwise set random generator to 3 
            //fire will spread randomly instead of being uniform 
            int random = rand() % 3; 
            int to = from - random + 1; 
            m_firePixels[to - m_width] = m_firePixels[from] - (random & 1); 
        }

        
}


//'main' function 
void Fire::Render(sf::RenderWindow& window){
    DoFire();

    sf::Texture texture; //setting up the texture - color of picture 
    sf::Sprite sprite; //setting up the sprite - position of picture 
    texture.create(m_width, m_height); //creates the size of the pictures - pixels
    sprite.setTexture(texture); //connects sprite and texture together 
    sf::Uint8* pixels;
    pixels = new sf::Uint8[m_width * m_height * 4];
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {

            RGBA first_rgba = g_firePallete[m_firePixels[i + (j * m_width)]];
            pixels[(i + (j * m_width)) * 4] = first_rgba.r;
            pixels[(i + (j * m_width)) * 4 + 1] = first_rgba.g;
            pixels[(i + (j * m_width)) * 4 + 2] = first_rgba.b;
            pixels[(i + (j * m_width)) * 4 + 3] = first_rgba.a;

        }
     }
     texture.update(pixels);
     window.draw(sprite);
}
