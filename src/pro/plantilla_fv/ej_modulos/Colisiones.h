#pragma once
#include <SFML/Graphics.hpp>
#include <Enemigo.h>
#include <Personaje.h>
#include <Bala.h>
#include <Portal.h>
#include <HUD.h>


class Colisiones{
    
    public:
        void ColisionesPersonajes(Personaje *personaje,Enemigo *enemigo,sf::RectangleShape** obstaclesArray,HUD *hud);
        void ColisionPersonajeParedes(Personaje *personaje,sf::RectangleShape** obstaclesArray);
        void ColisionEnemigoParedes(Enemigo *enemigo,sf::RectangleShape** obstaclesArray);
        bool ColisionBalaEnemigo(Enemigo *enemigo,Bala *bala);
        bool ColisionBalaParedes(Bala *bala,sf::RectangleShape** obstaclesArray);
        bool ComprobarColisionObstaculo(sf::FloatRect rectP,sf::RectangleShape** obstaclesArray,int desplazamiento);
        bool ColisionPersonajePortal(Personaje *personaje,Portal *portal);
        bool ColisionBalaPortal(Portal *portal,Bala *bala);
        int ColisionPersonajePocima(Personaje *personaje, std::vector<sf::Sprite*> vectorpocimas);
        bool ColisionBebe(Personaje *personaje,std::vector<sf::Sprite*> bebes);
};