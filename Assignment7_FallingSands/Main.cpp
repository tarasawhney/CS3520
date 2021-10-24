// C++ Standard Libraries
#include <iostream>

// Third Party Libraries
#include <SFML/Graphics.hpp>


// Our Libraries
#include "World.hpp"

//dimensions 
const int g_worldWidth = 400; 
const int g_worldHeight = 400; 



// Entry point to the program
int main(){
    
    //create the window
    sf::RenderWindow window(sf::VideoMode(g_worldWidth, g_worldHeight), "Falling Sands"); 

    //create our world for the simulation 
    World FallingSand (&window, g_worldWidth, g_worldHeight);
    
    //run program as long as window is open
    
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
             //check all the window events 
            if (event.type == sf::Event::Closed)
            window.close(); 
        }
    
        Particle particle; 
        particle.SetParticleType(PARTICLE_TYPE::SAND);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
        
            particle.SetParticleType(PARTICLE_TYPE::SAND);
         
       
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        particle.SetParticleType(PARTICLE_TYPE::WATER);
        
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            particle.SetParticleType(PARTICLE_TYPE::STONE);
        }    


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //if left mouse is clicked 
            //create first particle 


            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            particle.SetPosition(localPosition.x, localPosition.y);
       
            FallingSand.AddParticle(particle);
        
        }

   
    //clear the window with black color 
    window.clear(sf::Color::Black); 

    FallingSand.Update(); 

    //draw everything here...
    FallingSand.Draw(); 

    //end the current time 
    window.display();



    }
    return 0; 
  
    
}
