#ifndef SPLINE_HPP
#define SPLINE_HPP

#include "point2D.hpp"
// TODO: Move this to it's own .hpp and .cpp file
class CatmullRomSpline{
    public:
        // I have discussed how we should create constructors
        // for all of our classes. Sometimes however, we just
        // want to use the default that the compiler will
        // generate for us.
        // In this case, we can explicitly declare that this
        // is something we want to do.
        CatmullRomSpline()=default;
        ~CatmullRomSpline()=default;

        // Add a point to our spline by specifying
        // the x and y coordinate
        void AddPoint(float x, float y);
        
        void Render(sf::RenderWindow& windowRef); 
          
        void Update(sf::RenderWindow& windowRef); 

        Point2D GetSplinePoint(float t); 


    
    private:
        // Holds the control points in the spline.
        std::vector<Point2D> m_points;
};

    



#endif
