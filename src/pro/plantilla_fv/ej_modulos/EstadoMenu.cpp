#include "SFML/Graphics.hpp"
#include <iostream>
#include "EstadoMenu.h"
#include "SFML/Audio.hpp"
#include "EstadoControles.h"

#include "MotorGrafico.h"
MainMenu *MainMenu::instance = nullptr;
MainMenu* MainMenu::getInstancia(){
    MotorGrafico *motor = MotorGrafico::getInstancia();
    if(instance == 0){
        instance = new MainMenu(motor->getWindow()->getSize().x,motor->getWindow()->getSize().y);
    }
    return instance;
}
MainMenu::MainMenu(float width, float height) {

    if (!musicBuffer.loadFromFile("resources/Infernal.ogg")) {
        // Error al cargar el archivo de música
        //std::cout << "Error al cargar el archivo de música." << std::endl;
    }

    musica.setBuffer(musicBuffer);
    musica.play();

    if (!selectionBuffer.loadFromFile("resources/selection.ogg")) {
        // Error al cargar el archivo de música
        //std::cout << "Error al cargar el archivo de música." << std::endl;
    }

    selection.setBuffer(selectionBuffer);

    if (!enterBuffer.loadFromFile("resources/entergame.ogg")) {
        // Error al cargar el archivo de música
        //std::cout << "Error al cargar el archivo de música." << std::endl;
    }
    enter.setBuffer(enterBuffer);

    if (!enterBuffer.loadFromFile("resources/entergame.ogg")) {
        // Error al cargar el archivo de música
        //std::cout << "Error al cargar el archivo de música." << std::endl;
    }
    enter.setBuffer(enterBuffer);

    if(!font.loadFromFile("resources/Gamer.ttf")){
        //aqui da un error
    }
    textura.loadFromFile("resources/titulo.png");
    menusprite.setTexture(textura);
    menusprite.setScale(0.3, 0.3);
    menusprite.setPosition(100,40);

    textura2.loadFromFile("resources/sprites2.png");
    sf::IntRect spriteposicion(0,0,29,33);
    frame.setTextureRect(spriteposicion);
    frame.setTexture(textura2);
    frame.setScale(5, 5);
    frame.setPosition(150,400);

    textura3.loadFromFile("resources/fondo.jpg");
    fondo.setTexture(textura3);
    fondo.setScale(0.5, 0.5);
    fondo.setPosition(0,0);

    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Jugar");
    menu[0].setCharacterSize(90);
    menu[0].setPosition(sf::Vector2f(width/2.2, height/(MAX_NUM_ITEMS+1)*0.6));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Controles");
    menu[1].setCharacterSize(90);
    menu[1].setPosition(sf::Vector2f(width/2.2, height/(MAX_NUM_ITEMS+1)*1.6));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Tienda");
    menu[2].setCharacterSize(90);
    menu[2].setPosition(sf::Vector2f(width/2.2, height/(MAX_NUM_ITEMS+1)*2.6));

   
    menu[3].setFont(font);
    menu[3].setColor(sf::Color::White);
    menu[3].setString("Salir");
    menu[3].setCharacterSize(90);
    menu[3].setPosition(sf::Vector2f(width/2.2, height/(MAX_NUM_ITEMS+1)*3.6));

    itemseleccionado = 0;

}
// void MainMenu::dibujar(sf::RenderWindow &window){
//     for(int i = 0; i< MAX_NUM_ITEMS; i++){
//         window.draw(menu[i]);
//     }
// }
// void MainMenu::updateMusica(){
//    sf::Music music;
//     if (!music.openFromFile("resources/Infernal.ogg")) {
//         // Error al cargar el archivo de música
//     }
//     music.play();
// }

void MainMenu::arriba(){
    selection.play();
    if(itemseleccionado -1 >=0){
        menu[itemseleccionado].setColor(sf::Color::White);
        itemseleccionado--;
        menu[itemseleccionado].setColor(sf::Color::Red);
    }
}
void MainMenu::abajo(){
    selection.play();
    if(itemseleccionado +1 < MAX_NUM_ITEMS){
        menu[itemseleccionado].setColor(sf::Color::White);
        itemseleccionado++;
        menu[itemseleccionado].setColor(sf::Color::Red);
    }
}
void MainMenu::Render(MotorGrafico *motor){
    // std::cout<< "HE ENTRADO A MENU";
    motor->getWindow()->clear();
    motor->DrawMenu(motor->getWindow(),menu,menusprite,frame,fondo);
    motor->getWindow()->display();
    //  std::cout<< itemseleccionado;
}
void MainMenu::Update(Juego *juego){
  if(!musica.Playing){
    musica.play();
  }
}
void MainMenu::HandleInput(Juego *juego){
    // std::cout<< "BRUSCA GUAPO";
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
                jugar = Jugando::getInstancia();
                  enter.play();
                  musica.stop();
                  juego->CambiarEstado(jugar);
                  instance = nullptr;
                  // delete instance;
                  std::cout << "Aqui va el jugar" << std::endl;
                  break;

                case 1:
                controles = Controles::getInstancia();
                   juego->CambiarEstado(controles);
                  //  delete instance;
                  break;

                case 2:
                tienda = Tienda::getInstancia();
                   juego->CambiarEstado(tienda);
                  //  delete instance;
                  break;

                case 3:
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