#pragma once
#include <iostream>
#include "State.h"
#include <EstadoMenu.h>
#define MAX_NUM_ITEMS 4
class MainMenu;
class Tienda: public State {  

    public:
     Tienda(float width, float height);
    void arriba();
    void abajo();
    int getBoton(){return itemseleccionado;};
    static Tienda* getInstancia();
    void HandleInput(Juego *juego);
    void Update(Juego *juego);
    void Render(MotorGrafico *motor);
     int itemseleccionado;
     sf::Text menu[MAX_NUM_ITEMS];
     MainMenu *mainmenu;
        sf::Texture textura;
        sf::Sprite menusprite;

        sf::Texture textura2;
        sf::Sprite frame;

sf::Texture textura3;
        sf::Sprite fondo;
    private: 
        static Tienda *instance;
        sf::Font font;
};
