#pragma once
#include <SFML/Graphics.hpp>


class Portal{
    
    public:
        Portal(sf::Texture& textura,sf::Vector2f posicion);
        void PonerFrame(int frame);
        int getFrameactual();
        void AumentarFrame();
        std::vector<sf::Sprite> getFrames();
        sf::Sprite getsprite();
    private:
       std::vector<sf::Sprite> frames;
        int frameactual;
};