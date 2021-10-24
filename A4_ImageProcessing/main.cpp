// C++ Standard Libraries
#include <iostream>
// Third Party Libraries
#include <SFML/Graphics.hpp>
// Our Library
#include "Image.hpp"

// Entry point into the program
int main(){

    // Create an 'Image' called 'ourImage' on the stack.
    // Our constructor takes one argument for loading an image
    CImage ourImage("test.jpg");

    // Create an SFML Window
    // This window allows us to 'render graphics' onto a Window.
    // We will make the window as big as our image
    sf::RenderWindow window(sf::VideoMode(ourImage.GetWidth(),ourImage.GetHeight()), "Assignment!");
     
    // This is an infinite loop
    // This loop will continuously run our application
    // until we receive an event to close the window.
    while (window.isOpen()){
        // Within our loop (local scope) we create
        // an event. It is the first thing that we
        // do. 
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        // Retrieve the position of the mouse
		sf::Vector2i globalPosition = sf::Mouse::getPosition(window);
        
        // Handle button presses for our image
        ourImage.ChangeDisplay();
		 
        // Handle mouse clicks
        // Not used in this assignment, but here for reference
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		}

		// Clear the window at the start of every frame
        window.clear();
		// Setup the rendering
        window.draw(ourImage.GetSpriteRef());
		// Display to the window
        window.display();
    }
    

    return 0;
}
