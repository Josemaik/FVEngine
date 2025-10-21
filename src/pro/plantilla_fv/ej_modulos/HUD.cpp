#include "HUD.h"
#include <iostream>
#include "SFML/Audio.hpp"
#define currentHealth 10
#define maxHealth 10
#define totalMoney 00000

HUD::HUD(sf::Texture&  coraT, sf::Texture&  barraT, sf::Texture& barraColorT, sf::Texture& gridBarraT, sf::Texture& pistolaT,sf::Texture& texlaser){
    barra.setTexture(barraT);
    pistola.setTexture(pistolaT);
    sf::Sprite barraC(barraColorT);
    barraColor = barraC;
    experiencia = 0;
    sf::IntRect textureRect(0, 0, experiencia, barraColorT.getSize().y);
    barraColor.setTextureRect(textureRect);
    gridBarra.setTexture(gridBarraT);
    // text("00000", textT, 54);
    lasergun.setTexture(texlaser);

    for (int i = 0; i < MAX_LIVES; i++) {
      sf::Sprite vida;
      vida.setTexture(coraT);
      cora.push_back(vida);
    }

    //Sonidos de colision
    if (!hitBuffer.loadFromFile("resources/agh.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    hit.setBuffer(hitBuffer);
}

void HUD::posicionarHUD(){
    // text.setFillColor(sf::Color::White);
    // text.setPosition(50, 550);




    const int HEART_SIZE = 50;
    const float HEART_SPACING = 0.5;
    for (int i = 0; i < MAX_LIVES; i++) {
      cora[i].setPosition(40 + i * (HEART_SIZE + HEART_SPACING), 620);
      cora[i].setScale(1.0f, 1.0f);
    }

    if (currentHealth < maxHealth) {
      int visibleLives = currentHealth / (maxHealth / MAX_LIVES);
      std::cout << visibleLives << std::endl;
      std::cout << currentHealth << std::endl;
      std::cout << maxHealth << std::endl;
      std::cout << MAX_LIVES << std::endl;
      for (int i = 0; i < MAX_LIVES; i++) {
          if (i < visibleLives) {
              cora[i].setColor(sf::Color::White);
          } else {
              cora[i].setColor(sf::Color::Transparent);
          }
      }
    }
    pistola.setScale(2.5f, 2.5f);
    pistola.setPosition(950, 630);
    lasergun.setScale(0.09f, 0.09f);
    lasergun.setPosition(850, 580);
    // lasergun.setColor(sf::Color::Green);

    barra.setPosition(440, 640);
    barraColor.setPosition(440, 640);
    gridBarra.setPosition(440, 640);

    gridBarra.setOrigin(5, 5);
    gridBarra.setColor(sf::Color::Black);
}

std::vector<sf::Sprite> HUD::getCora() {
    return cora;
}
int HUD::getLongCora() {
    return cora.size();
}
sf::Sprite HUD::getBarra(){
    return barra;
}
sf::Sprite HUD::getBarraColor(){
    // std::cout << experiencia<< std::endl;
    return barraColor;    
}
sf::Sprite HUD::getGridBarra(){
    return gridBarra;
}



sf::Sprite HUD::getPistola(){
    return pistola;
}   
sf::Sprite HUD::getLaser(){
    return lasergun;
} 
void HUD::QuitarCora(){
    hit.play();
    if(cora.size() > 0){
        // std::cout << "quito corazon" << std::endl;
        cora.pop_back();
    }
}
void HUD::AumentarExp(sf::Texture& barraColorT){
        if(experiencia < 272){
            experiencia = experiencia + 68;
        }

//    int valor =  barraColor.getTextureRect().width;
   sf::IntRect textureRect(0, 0, experiencia, barraColorT.getSize().y);
   barraColor.setTextureRect(textureRect);
    // std::cout << valor << std::endl;
}
void HUD::quitarExp(sf::Texture& barraColorT){
    std::cout << experiencia << std::endl;
    experiencia -= 2;

    sf::IntRect textureRect(0, 0, experiencia, barraColorT.getSize().y);
   barraColor.setTextureRect(textureRect);

}
void HUD::reiniciarExp(sf::Texture& barraColorT){
    std::cout << "holaaaaaaaaaa" << std::endl;
    experiencia = 0;
    sf::IntRect textureRect(0, 0, experiencia, barraColorT.getSize().y);
     barraColor.setTextureRect(textureRect);
}
void HUD::AumentarVida(sf::Texture& coratext){
    if(cora.size() < 5){
         sf::Sprite vida;
        vida.setTexture(coratext);
        vida.setScale(0.5f, 0.5f);
        vida.setPosition(cora.back().getPosition().x + 60,620);
        cora.push_back(vida);
    }
}