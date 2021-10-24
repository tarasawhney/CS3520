// C++ Standard Libraries
#include <iostream>
#include <math.h>
// C Libraries
#include <cstring> // for memcpy
// Third Party Libraries
#include <SFML/Graphics.hpp>

// Our Libraries
#include "Fire.hpp"

// Entry point to the program
int main(){
    // Initialize a random seed
    srand(time(NULL));
    // Set dimensions of the window
    const int width = 400;
    const int height = 400;
    // Create a fire
    Fire f(width,height);
    // Create the window
    sf::RenderWindow window(sf::VideoMode(width,height), "Fire");
    // Limit to 30 FPS
    window.setFramerateLimit(30);
    
    // Main loop of the program
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
		// Clear the window at the start of every frame
        window.clear();

        // Do the fire rendering
        f.Render(window);

		// Display to the window
        window.display();
    }


    return 0;
}
