#pragma once
#include <iostream>
#include "State.h"
#include "EstadoMenu.h"
#include "EstadoJugando.h"
class Jugando;
class Partida: public State {


    public:
        Partida(float width, float height);
        int itemseleccionado;
        void partidaWIN();
        void partigaGameOver();
        sf::Text men[2];
        static Partida* getInstancia();
        void HandleInput(Juego *juego);
        void Update(Juego *juego);
        void Render(MotorGrafico *motor);
        void arriba();
        void abajo();
        int getBoton(){return itemseleccionado;};
    private:
        static Partida *instance;
        sf::Font font;
        MainMenu *menu;
        sf::Text text;
        Jugando *estadoJ;

}; 