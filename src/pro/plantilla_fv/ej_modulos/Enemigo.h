#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Interpolation.h"
using namespace std;
class Enemigo{
    
    public:
    Enemigo(sf::Texture& textura,sf::IntRect chooseimagen, sf::Vector2f posicion,sf::Vector2f Origen,int nivel);
        sf::Vector2f getPosicion();
        void setPosicion(float x,float y);
        void nuevaX(float x);
        float getX();
        void nuevaY(float y);
        float getY();
        void setInterpolacion(sf::Vector2f posicion, sf::Vector2f Origen);
        sf::Vector2f getUltimaPosicion();
        sf::Vector2f getPosicionActual();
        void ActualizarSprite();
        void AumentarFrame();
        void PonerFrame(int frame);
        int getFrameactual();
        std::vector<sf::Sprite> getFrames();
        void elegirSprite(sf::Texture& textura,int top,int ancho,int alto,int nivel);
        sf::FloatRect getCoordenadas();
        sf::Sprite getSprite();
        sf::Vector2f getCentro();
        void mover(int x , int y);
        // void moverHacia(sf::Vector2f pos,sf::Time time);
         float getVelocidad();
        void setVelocidad(float velo);
        char getDireccion();
        void setDireccion(char dir);
        void quitarVidaEnemigo();
        int getVidaEnemigo();

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite e_sprite;
        float velocidad;
        Interpolacion *inter;
        std::vector<sf::Sprite> frames;
        char Direccion;
        char direccionactual;
        int vidaenemigo;
    protected:
        int frameactual;
};