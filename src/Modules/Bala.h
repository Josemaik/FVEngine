#pragma once
#include <SFML/Graphics.hpp>

#define MAX_LIVES 5

class Bala{
    
    public:
        Bala(sf::Texture&  textura, sf::Vector2f escala,sf::Vector2f posicion,float rotacion,sf::Vector2f dir);
        sf::Sprite getSprite();
        void mover(float x , float y);
        sf::Vector2f getdir();
    private:
        sf::Sprite b_sprite;
        sf::Vector2f direccion;
};