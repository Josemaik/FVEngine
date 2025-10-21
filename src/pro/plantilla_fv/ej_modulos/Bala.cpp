#include "Bala.h"
#include <iostream>
// Constructor de la clase Bala

Bala::Bala(sf::Texture& textura, sf::Vector2f escala,sf::Vector2f posicion,float rotacion,sf::Vector2f dir){
    b_sprite.setTexture(textura);
    // b_sprite.setOrigin(Origen.x,Origen.y);
    b_sprite.setScale(escala);
    b_sprite.rotate(rotacion);
    direccion = dir;
    // b_sprite.setTextureRect(choosesprite);
    b_sprite.setPosition(posicion.x,posicion.y);
}
//Método para obtener sprite
sf::Sprite Bala::getSprite(){
    return b_sprite;
}
//Método para mover bala
void Bala::mover(float x,float y){
    b_sprite.move(x,y);
}
//Método recoger dirección
sf::Vector2f Bala::getdir(){
    return direccion;
}