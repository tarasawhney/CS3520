#include "Particle.hpp"

Particle::Particle(){
}

Particle::~Particle(){

}

PARTICLE_TYPE Particle::GetParticleType(){
    return m_particletype;
}

void Particle::SetParticleType(PARTICLE_TYPE type){
    m_particletype = type;
}

sf::Vector2i Particle::GetPosition(){
    return m_position;
}

void Particle::SetPosition(int x, int y){
    m_position.x = x;
    m_position.y = y;
}

void Particle::Draw(sf::RenderWindow* windowRef){
    // Create our shape
    sf::RectangleShape shape(sf::Vector2f(1.0f,1.0f));
   // TODO: Implement as a switch
    if(m_particletype == PARTICLE_TYPE::AIR){
        shape.setFillColor(sf::Color::Black);
    }
    if(m_particletype == PARTICLE_TYPE::SAND){
        shape.setFillColor(sf::Color::White);
    } 
    if(m_particletype == PARTICLE_TYPE::STONE){
        shape.setFillColor(sf::Color::Red);
    } 
    if(m_particletype == PARTICLE_TYPE::WATER){
        shape.setFillColor(sf::Color::Blue);
    } 


    shape.setPosition(m_position.x,m_position.y);
    windowRef->draw(shape);
}
