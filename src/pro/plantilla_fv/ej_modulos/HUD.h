#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#define MAX_LIVES 5

class HUD{
    
    public:
        HUD(sf::Texture&  coraT, sf::Texture&  barraT, sf::Texture& barraColorT, sf::Texture& gridBarraT, sf::Texture& pistolaT,sf::Texture& texlaser);
        void posicionarHUD();
        std::vector<sf::Sprite> getCora();
        sf::Sprite getBarra();
        sf::Sprite getBarraColor();
        sf::Sprite getGridBarra();
        sf::Text getText();
        sf::Sprite getBotonPausa();
        sf::Sprite getPistola();
        sf::Sprite getLaser();
        void QuitarCora();
        void AumentarExp(sf::Texture& barraColorT);
        int getLongCora();
        void quitarExp(sf::Texture& barraColorT);
        void reiniciarExp(sf::Texture& barraColorT);
        void AumentarVida(sf::Texture& barraColorT);
    private:
        sf::Sprite barra, barraColor, gridBarra, pistola, lasergun;
        std::vector<sf::Sprite> cora;
        sf::Text text;
        int experiencia;
        sf::SoundBuffer hitBuffer;
        sf::Sound hit;
};