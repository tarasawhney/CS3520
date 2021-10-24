#include "World.hpp"
#include <iostream>

World::World(sf::RenderWindow* w,int width, int height){
    m_windowPtr = w;
    m_width = width;
    m_height = height;
    // Initialize our array
    m_grid = new PARTICLE_TYPE[width*height];
    for(int i=0; i < width*height; i++){
        m_grid[i] = PARTICLE_TYPE::AIR;
    }
}

World::~World(){
    delete[] m_grid;
}

// May have to implement copy constructor
void World::AddParticle(Particle p){
    m_particles.push_back(p); 
}

// Iterate through all particles.
// Update our 'grid' structure
// Figure out what type they are, and how they move
void World::Update(){
    // Refresh grid to all '0's or air 
    for(int i=0; i < m_width*m_height; i++){
        m_grid[i] = PARTICLE_TYPE::AIR;
    }
    // Update grid structure
    for(int i=0; i < m_particles.size(); i++){
        sf::Vector2i pos = m_particles[i].GetPosition();
        m_grid[pos.y * m_width + pos.x] = m_particles[i].GetParticleType();
    }
    
    // Move our particles        
    for(int i=0; i < m_particles.size(); i++){
        // Get particle position and type
        sf::Vector2i pos = m_particles[i].GetPosition();
        PARTICLE_TYPE type = m_particles[i].GetParticleType();
       
        if(type==PARTICLE_TYPE::SAND){
            PARTICLE_TYPE bottomCellType = m_grid[(pos.y+1) * m_width + pos.x];

            PARTICLE_TYPE bottomLeftCellType = m_grid[(pos.y+1) * m_width + pos.x-1];

            PARTICLE_TYPE bottomRightCellType = m_grid[(pos.y+1) * m_width + pos.x+1];
            if(bottomCellType==PARTICLE_TYPE::AIR){
                // Update grid to reflect, that sand has moved one unit down
                m_grid[(pos.y+1)*m_width + pos.x] = type;
                m_particles[i].SetPosition(pos.x,pos.y+1);
                // Update grid, to reflect that 'air' has moved one unit up
                m_grid[(pos.y)* m_width+pos.x] = PARTICLE_TYPE::AIR;
            }       
            if(bottomLeftCellType==PARTICLE_TYPE::AIR){
                m_grid[(pos.y+1) * m_width + pos.x-1] = type;
                m_particles[i].SetPosition(pos.x-1, pos.y+1); 
                //Update grid 
                m_grid[(pos.y)*m_width+pos.x] = PARTICLE_TYPE::AIR; 
            }  
            if(bottomRightCellType==PARTICLE_TYPE::AIR){
                m_grid[(pos.y+1) * m_width + pos.x+1] = type;
                m_particles[i].SetPosition(pos.x+1, pos.y+1); 
                //Update grid 
                m_grid[(pos.y)*m_width+pos.x] = PARTICLE_TYPE::AIR; 
            }  

        //move water particle
        if(type==PARTICLE_TYPE::WATER){
            PARTICLE_TYPE leftCellType = m_grid[(pos.y-1)*m_width+pos.x-1]; 

            PARTICLE_TYPE rightCellType = m_grid[(pos.y+1)*m_width+pos.x+1]; 

            PARTICLE_TYPE bottomCellType = m_grid[(pos.y+1)*m_width + pos.x]; 

            if(leftCellType==PARTICLE_TYPE::AIR){
                m_grid[(pos.y-1)*m_width+pos.x-1] = type; 
                m_particles[i].SetPosition(pos.x-1, pos.y-1); 
                //update grid 
                m_grid[(pos.y)*m_width+pos.x] = PARTICLE_TYPE::AIR; 
            }
            if(rightCellType==PARTICLE_TYPE::AIR){
                m_grid[(pos.y+1)*m_width+pos.x+1] = type; 
                m_particles[i].SetPosition(pos.x+1, pos.y+1); 
                //Update grid 
                m_grid[(pos.y)*m_width+pos.x] = PARTICLE_TYPE::AIR; 
            }
            if(bottomCellType==PARTICLE_TYPE::AIR){
                m_grid[(pos.y+1)*m_width+pos.x] = type; 
                m_particles[i].SetPosition(pos.x, pos.y+1); 
                //Update Grid 
                m_grid[(pos.y)*m_width+pos.x] = PARTICLE_TYPE::AIR; 
            }
        
    
        }
   

            //PARTICLE_TYPE bottomCellType = m_grid[(pos.y+1) * m_width + pos.x-1];
            //PARTICLE_TYPE bottomCellType = m_grid[(pos.y+1) * m_width + pos.x+1];
        }
    }

 

}
void World::SwitchParticle(){


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //if left mouse is clicked 
            //create first particle 

            sf::Vector2i localPosition = sf::Mouse::getPosition(m_windowPtr);
             

        }
       
    }
}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //if left mouse is clicked 
            //create first particle 

            sf::Vector2i localPosition = sf::Mouse::getPosition(m_windowPtr);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //if left mouse is clicked 
            //create first particle 

            sf::Vector2i localPosition = sf::Mouse::getPosition(m_windowPtr);
        }

    }

void World::Draw(){
    for(int i=0; i < m_particles.size(); i++){
       m_particles[i].Draw(m_windowPtr); 
    }
}
