#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>

#include "MotorGrafico.h"

#include<stack>
using namespace std;
#include <State.h>
class State;
class MotorGrafico;
class Juego{
    
    public:
        Juego();
        ~Juego();
        static Juego* getInstancia();
        MotorGrafico *motor;
        //  void CambiarEstado(sf::RenderWindow &window,State estado);
        bool isRunning();
        void StopRunning();
        State* getEstadoActual();
        // void LiberarMemoria();
        void CambiarEstado(State *state);
        void HandleInput();
        void Update();
        void Render();
    private:
        bool running;
        State *estadoactual;
        static Juego *instance;
        std::stack<State*> pilaestados;
};