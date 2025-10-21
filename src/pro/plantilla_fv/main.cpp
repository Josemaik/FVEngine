#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include "include/config.h"
#include <Juego.h>
#include <EstadoMenu.h>

#define UPDATE_TICK_TIME 1000/15
#define kVel 5

int main() {
  //Creamos la ventana
  // sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
  //Cambiamos a estado 0
  Juego *juego = Juego::getInstancia();
  MainMenu *menu = MainMenu::getInstancia();
  juego->CambiarEstado(menu);
  while(juego->isRunning()){
    juego->HandleInput();
    juego->Update();
    juego->Render();
  }
  delete juego;
  juego = NULL;

  return 0;
}