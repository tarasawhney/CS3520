#include "spline.cpp"

// Entry point into our program
int main(){

    // Setup our SFML Render window
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

    // Create our spline data structure
    CatmullRomSpline spline;
    spline.AddPoint(5.0f, 5.0f); 
    spline.AddPoint(1.0f, 1.0f); 
    spline.AddPoint(7.0f,7.0f); 
    spline.AddPoint(4.0f,4.0f); 
    // Added some test points
    // TODO: Add at least 4 points to create the spline
    // e.g. spline.AddPoint(5.0f,5.0f);



    // Our main loop while the window is open.
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            // Mouse interaction
            // Handle one mouse click
            // Every time the user presses the mouse click,
            // then a new point is added.
            if(event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window); 
                spline.AddPoint(localPosition.x,localPosition.y);
            }
        }
        // Clear our window
        window.clear();
        // Handle any user interaction
        spline.Update(window);
        // Render our spline
        spline.Render(window);
        // Show our window contents
        window.display();
    }

    return 0; 

}
