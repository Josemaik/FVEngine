#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Interpolation.h"
#include <SFML/Audio.hpp>
using namespace std;


class Personaje{
    
    public:
    Personaje(sf::Texture&  textura,sf::IntRect choosesprite, sf::Vector2f posicion,sf::Vector2f Origen);
        sf::Vector2f getPosicion();
        void setPosicion(float x,float y);
        void nuevaX(float x);
        float getX();
        void nuevaY(float y);
        float getY();
        void mover(int x,int y);
        void setInterpolacion(sf::Vector2f posicion, sf::Vector2f Origen);
        sf::Vector2f getUltimaPosicion();
        sf::Vector2f getPosicionActual();
        sf::FloatRect getCoordenadas();
        void ActualizarSprite();
        void AumentarFrame();
        void PonerFrame(int frame);
        int getFrameactual();
        std::vector<sf::Sprite> getFrames();
        void elegirSprite(sf::Texture& textura,int top,int ancho,int alto);
        void escalar(int x,int y);
        // void mover(int x,int y);
        sf::Vector2f getCentro();
        sf::Sprite getsprite();
        float getVelocidad();
        void setVelocidad(float velo);
        char getDireccion();
        void setDireccion(char dir);
        enum EstadoPersonaje{
            Caminando,Parado,Disparando
        };
        EstadoPersonaje actual;
        void setEstado(EstadoPersonaje estado);
        EstadoPersonaje getEstadoActual() const{return actual;}
        // ~Personaje();
        int getVida();
        void quitarVida();
    private:
        sf::Sprite p_sprite;
        std::vector<sf::Sprite> frames;
        float velocidad;
        char Direccion;
        char direccionactual;
        int vidaactual;
        // Interpolacion::Posicion *coordenadas;
        Interpolacion *inter;
        sf::SoundBuffer disparoBuffer;
        sf::Sound disparoSound;

    protected:
        int frameactual;
};
