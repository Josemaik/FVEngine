#pragma once
#include <iostream>
#include "State.h"
#include <SFML/Audio.hpp>
#include <EstadoTienda.h>
#include <EstadoControles.h>
#include <EstadoJugando.h>

#define MAX_NUM_ITEMS 4
class Tienda;
class Controles;
class Jugando;
class MainMenu: public State {
    
    public:
        MainMenu(float width, float height);
        ~MainMenu();
        void arriba();
        void abajo();
        int getBoton(){return itemseleccionado;};
        static MainMenu* getInstancia();
        void HandleInput(Juego *juego);
        void Update(Juego *juego);
        void Render(MotorGrafico *motor);
        void updateMusica();
        Tienda *tienda;
        Controles *controles;
        Jugando *jugar;
        int itemseleccionado;
        sf::Text menu[MAX_NUM_ITEMS];
        sf::Texture textura;
        sf::Sprite menusprite;

        sf::Texture textura2;
        sf::Sprite frame;

        sf::Texture textura3;
        sf::Sprite fondo;


    private: 
        static MainMenu *instance;
        sf::Font font;
        sf::SoundBuffer musicBuffer;
        sf::Sound musica;
        sf::SoundBuffer selectionBuffer;
        sf::Sound selection;
        sf::SoundBuffer enterBuffer;
        sf::Sound enter;
};
