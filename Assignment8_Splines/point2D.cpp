// g++ -g -std=c++20 main.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

// TODO: Move this into it's own C++ implementation file
struct Point2D{
    float x,y; // coordinate in the window
    float radius=10.0f;

    void Render(sf::RenderWindow& windowRef){
        // Create and draw our circle
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::Red);
        // Get the radius of our first point
        float halfRadius = radius/2.0f;
        circle.setPosition(x+halfRadius,y+halfRadius);
        // Draw the circle
        windowRef.draw(circle);
    }
};
