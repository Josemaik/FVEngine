#include "Juego.h"
#include <iostream>
// bool creado = false;
Juego *Juego::instance = nullptr;
Juego::Juego(){
    running = true;
    motor = MotorGrafico::getInstancia();
}
Juego::~Juego(){
    delete motor;
    delete estadoactual;
}
bool Juego::isRunning(){
    return running;
}
void Juego::StopRunning(){
    running = false;
}
// void Juego::LiberarMemoria(){
//     delete motor; motor = NULL;
//     delete instance; instance = NULL;
//     delete estadoactual; estadoactual = NULL;
// }
void Juego::CambiarEstado(State *state){
    pilaestados.push(state);
}
// void Juego::CambiarEstado(sf::RenderWindow &window,State estadoactual) {
//     pilaestados.push(estadoactual);
//     HandleInput(estadoactual);
//     Update(estadoactual);
//     Render(estadoactual);
    // switch (estado)
    // {
    // case 0:  //std::cout<< "MENU";
    //         pilaestados.push(0);
    //         mainMenu->HandleInput(window);
    //         window.clear();
    //         mainMenu->RenderMenu(window);
    //         window.display();
    //     break;
    // case 1: std::cout<<"SALA PRINCIPAL";
    //         pilaestados.push(1);
    //         //RenderJuego(sala)
    //         //Crear clase Juego o Niveles
    //         //HandleInput()
    // case 2: std::cout<<"NIVEL 1";
    //         pilaestados.push(2);
    //         //RenderJuego(nivel1)
    //         //HandleInput()
    // default:
    //     break;
    // }
// }
Juego* Juego::getInstancia(){
    if(instance == 0){
        instance = new Juego();
    }
    return instance;
}
State* Juego::getEstadoActual(){
    return pilaestados.top();
}
void Juego::HandleInput(){
    estadoactual = getEstadoActual();
    estadoactual->HandleInput(instance);
}
void Juego::Update(){
    estadoactual = getEstadoActual();
    estadoactual->Update(instance);
}
void Juego::Render(){
    estadoactual = getEstadoActual();
    estadoactual->Render(motor);
}


