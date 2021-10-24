// g++ -g -std=c++20 main.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

#include "spline.hpp"


// Add a point to our spline by specifying
// the x and y coordinate
void CatmullRomSpline::AddPoint(float x, float y){
    Point2D newPoint;
    newPoint.x = x;
    newPoint.y = y;

    m_points.push_back(newPoint);
}

        // Allowed for user interaction
        // We checked distance, against our right mouse click
        // and allowed the user to reposition the point while the
        // right-click was held.
        //
        // TODO: Could be improved to make moving smoother.
        void CatmullRomSpline::Update(sf::RenderWindow& windowRef){
            // Loop through all of our points
            for(int i=0; i < m_points.size(); i++){
                float distance = 100000.0f;
                sf::Vector2i localPosition = sf::Mouse::getPosition(windowRef);
                // Compute the distance.        
                float xx = std::pow(localPosition.x - m_points[i].x,2);
                float yy = std::pow(localPosition.y - m_points[i].y,2);
                distance = std::sqrt(xx+yy);

                // If the distance between our moue and
                // the 'point' that we are hovering over is 
                // less than half the radius of the circle, then
                // we can move that point.
                if(distance < m_points[i].radius/2.0f && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
//                    std::cout << "Point " << i << "was right-clicked\n"; 
                    m_points[i].x = localPosition.x;
                    m_points[i].y = localPosition.y;
                }

            } 
        }
// Draw our spline.
        // The render function is where the rendering of 
        // the spline takes place.
        //
        // The goal of this function is to take a series
        // of control points, and draw the 'spline' as well
        // as the control points.
        void CatmullRomSpline::Render(sf::RenderWindow& windowRef){    
            // Our spline ranges from the value of 0.0 to 1.0
            // You can think of this as 0-100% value of the
            // curve between '2' points.
            //
            // In order to iterate through all of our spline
            // points, we adjust the number of points that we
            // are going to draw by subtracting '3' from our
            // loop.
            //
            // Why? Well,l in the 'GetSplinePoint(t)' function,
            // we are looking forward '2' points at any given
            // time from our current point in order to draw 
            // the spline.
            for(float t = 0.0f; t < (float)m_points.size()-3.0f; t+=0.01f){
                // We are going to return the appropriate
                // x,y coordinate along our spline.
                Point2D pos = GetSplinePoint(t);
                pos.Render(windowRef);
            }
            // To draw our control points
            // We did this after drawing the intermediate 'red' points'
            // so that othey would appear on top.
            for(int i=0; i < m_points.size(); i++){
                sf::CircleShape circle(m_points[i].radius);
                circle.setFillColor(sf::Color::Blue);
                circle.setPosition(m_points[i].x,m_points[i].y);
                windowRef.draw(circle);
            }
        }

    // Function that takes in a value 't' and returns
    // and 'x,y' coordinate.
    //
    // This is the key function in drawing the spline.
    // It's goal is to take some value t that ranges from
    // 0.0 to 1.0 (or 0 to 100%) and draw the spline.
    // It one control point before, and one control point
    // after to 'influence' the overall curve between two
    // points.
    Point2D CatmullRomSpline::GetSplinePoint(float t){
        Point2D result; 
        // This is the point that we will
                        // generate and return from the
                        // function.

        // TODO: Implement GetSpline Point
        // The control points around our spline.
        // We are essentially grabbing 'nearby' points
        // Note that 't' is coming in as a floating point
        // value, and we can cast it to an integer to
        // otherwise 'round' it to the 'floor'
        // (e.g. 3.1 the floor is '3')
        // (e.g. 3.9 the floor is '3')
        //
        // p0,p1,p2,p3 are the indices in an array for
        // our control points.
        int p1 = (int)t + 1; // The 'floor' value
        int p2 = p1+1;
        int p3 = p2+1;
        int p0 = p1-1;
        
        // Recall that we are normalizing 't'
        // This means that we want the range to be from
        // 0.0 to 1.0. So if we subtract our 'floor'
        // from t, we will get a value ranging between
        // 0.0 and 1.0.
        //
        // Consider for example if 't' is 3.5, we are still
        // only needing to calculate the range betwen 0.0-1.0
        // for a given set of control points.
        t = t - (int)t;
         // Cache the values of t.
        // This is a trick to save computations that we are
        // going to repeat over and over again by computing
        // the value once, and then storing the result in a 
        // variable.
        float tt = t*t;
        float ttt = t*t*t;

        // Cubic values for drawing the spline.
        // These are for Catmull-Rom splines, but the intuition
        // is to notice the alternating negative values which
        // 'push' or 'repel' points towards the right direction.
        //
        float q1 =      -ttt + 2.0f*tt - t;
        float q2 =  3.0f*ttt - 5.0f*tt + 2.0f;
        float q3 = -3.0f*ttt + 4.0f*tt + t;
        float q4 =       ttt -      tt;
    
        // Compute the x and y values of our point.
        float tx = 0.5f* (m_points[p0].x*q1 + m_points[p1].x*q2 + m_points[p2].x*q3 + m_points[p3].x*q4); 
        float ty = 0.5f* (m_points[p0].y*q1 + m_points[p1].y*q2 + m_points[p2].y*q3 + m_points[p3].y*q4); 

        // Populate our point with the computed 'x' and 'y'
        // value and then return that point.
        result.x = tx;
        result.y = ty;
        result.radius = 1.0f;

        return result;
    }
