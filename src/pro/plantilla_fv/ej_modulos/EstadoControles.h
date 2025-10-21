#pragma once
#include <iostream>
#include "State.h"
#include <EstadoMenu.h>
#define MAX_NUM_ITEMS 4
class MainMenu;
class Controles: public State {  

    public:
        Controles(float width, float height);
        void arriba();
        void abajo();
        int getBoton(){return itemseleccionado;};
        static Controles* getInstancia();
        void HandleInput(Juego *juego);
        void Update(Juego *juego);
        void Render(MotorGrafico *motor);
        int itemseleccionado;
        MainMenu *mainmenu;
    private: 
        sf::Text menu;
        sf::Texture texturaC;
        sf::Sprite controles;
         sf::Texture textura3;
        sf::Sprite fondo;
        static Controles *instance;
        sf::Font font;
};
