#include "SFML/Graphics.hpp"
#include <iostream>
#include "EstadoControles.h"
#include "MotorGrafico.h"
Controles *Controles::instance = nullptr;
Controles* Controles::getInstancia(){
    MotorGrafico *motor = MotorGrafico::getInstancia();
    if(instance == 0){
        instance = new Controles(motor->getWindow()->getSize().x,motor->getWindow()->getSize().y);
    }
    return instance;
}
Controles::Controles(float width, float height) {
     mainmenu = MainMenu::getInstancia();
    if(!font.loadFromFile("resources/Gamer.ttf")){
        //aqui da un error
    }
    textura3.loadFromFile("resources/fondo.jpg");
    fondo.setTexture(textura3);
    fondo.setScale(0.5, 0.5);
    fondo.setPosition(0,0);
 

    texturaC.loadFromFile("resources/wasd.png");
    
    controles.setTexture(texturaC);
    controles.setScale(2, 2);
    controles.setPosition(sf::Vector2f(width/3.6, height/(MAX_NUM_ITEMS+1)*1));

    menu.setFont(font);
    menu.setColor(sf::Color::Red);
    menu.setString("Volver");
    menu.setCharacterSize(90);
    menu.setPosition(sf::Vector2f(width/2.2, height/(MAX_NUM_ITEMS+1)*3.6));

    itemseleccionado = 3;

}

void Controles::Render(MotorGrafico *motor){
    // std::cout<< "HE ENTRADO A MENU";
    motor->getWindow()->clear();
    motor->DrawControles(motor->getWindow(),controles,menu,fondo);
    motor->getWindow()->display();
    //  std::cout<< itemseleccionado;
}
void Controles::Update(Juego *juego){

}
void Controles::HandleInput(Juego *juego){
    // std::cout<< "BRUSCA GUAPO";
    sf::Event event;
    while (juego->motor->getWindow()->pollEvent(event)) {
      switch (event.type) {
        case sf::Event::KeyReleased:
          switch (event.key.code) {
            case sf::Keyboard::Return:
              switch (getBoton()) {
                case 3:
                  std::cout << "Aqui va el volver" << std::endl;
                  juego->CambiarEstado(mainmenu);
                  return;
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