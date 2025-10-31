#include "SFML/Graphics.hpp"
#include <iostream>
#include <EstadoWinLose.h>

 
Partida *Partida::instance = nullptr;
Partida* Partida::getInstancia(){
    MotorGrafico *motor = MotorGrafico::getInstancia();
    if(instance == 0){
        instance = new Partida(motor->getWindow()->getSize().x,motor->getWindow()->getSize().y);
    }
    return instance;
}

Partida::Partida(float width, float height){
    std::cout << "Holaaa" << std::endl;
    if(!font.loadFromFile("resources/Gamer.ttf")){
        std::cout << "NO COJO EL FONT" << std::endl;
    }
    estadoJ = Jugando::getInstancia();
    itemseleccionado = 0;
    men[0].setFont(font);
    men[0].setColor(sf::Color::Red);
    men[0].setString("Volver a jugar");
    men[0].setCharacterSize(90);
    men[0].setPosition(sf::Vector2f(width/3.3, height/(MAX_NUM_ITEMS+1)*1.6));

    men[1].setFont(font);
    men[1].setColor(sf::Color::White);
    men[1].setString("Salir");
    men[1].setCharacterSize(90);
    men[1].setPosition(sf::Vector2f(width/3.3, height/(MAX_NUM_ITEMS+1)*2.6));
    
}
void Partida::arriba(){
    if(itemseleccionado -1 >=0){
        men[itemseleccionado].setColor(sf::Color::White);
        itemseleccionado--;
        men[itemseleccionado].setColor(sf::Color::Red);
    }
}
void Partida::abajo(){
    if(itemseleccionado +1 < 2){
        men[itemseleccionado].setColor(sf::Color::White);
        itemseleccionado++;
        men[itemseleccionado].setColor(sf::Color::Red);
    }
}

void Partida::HandleInput(Juego *juego){
    
    sf::Event event;
    while (juego->motor->getWindow()->pollEvent(event)) {
      switch (event.type) {
        case sf::Event::KeyReleased:
          switch (event.key.code) {
            case sf::Keyboard::W:
            std::cout<< "<<<<<<<<<ARRIBA>>>>>>>>>>>";
              arriba();
              break;

            case sf::Keyboard::S:
            std::cout<< "<<<<<<<<<ABAJO>>>>>>>>>>>";
              abajo();
              break;

            case sf::Keyboard::Return:
              switch (getBoton()) {
                case 0:
                    menu = MainMenu::getInstancia();
                    juego->CambiarEstado(menu);
                    instance = nullptr;
                  // delete instance;
                  std::cout << "Aqui va el jugar" << std::endl;
                break;

                case 1:
                    juego->motor->getWindow()->close();
                    juego->StopRunning();
                  //  delete instance;
                  break;
              }
              break;
            }
            break;
            case sf::Event::Closed:
                        juego->motor->getWindow()->close();
                        juego->StopRunning();
                        break;
      }
    }
}

void Partida::Update(Juego *juego){
    // Aqui tendremos que saber si es WIN o GAMEOVER

    //recojo la instancia de EstandoJugando 
    //
    if(estadoJ->getGanado()){
        text.setFont(font);
        text.setString("WWWIIIINNN");
        text.setCharacterSize(200);
        text.setColor(sf::Color::Green);
        text.setPosition(sf::Vector2f(180.0, 0.0));
    }
    else{
        text.setFont(font);
        text.setString("GAME OVER");
        text.setCharacterSize(200);
        text.setColor(sf::Color::Red);
        text.setPosition(sf::Vector2f(200.0, 0.0));
    }
}
void Partida::Render(MotorGrafico *motor){
    motor->getWindow()->clear();
    motor->DrawEstadoPartida(motor->getWindow(), text, men);
    motor->getWindow()->display();
}