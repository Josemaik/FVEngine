#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include "tinyxml2.h"
using namespace tinyxml2;
using namespace std;
using namespace sf;
const int MAP_ANCHO = 36;
const int MAP_ALTO = 24;
const int TILE_TAM = 30;
class Mapa{
    
    public:
        Mapa(const std::string rutaMapa);
        ~Mapa();
        static Mapa * getInstancia();
        int getMap_Width();
        int getMap_Height();
        sf::RectangleShape** getObstacles();
        int getNumCapas();
        sf::Sprite**** getMapa();
        sf::Sprite* getVectorImagen();
        std::string getRuta();
    private:
        int numCapas, mapWidth, mapHeight, tileWidth, tileHeight;
        sf::Sprite**** mapSprite;
        sf::Sprite* tilesSprites;
        sf::Texture textTile;
        tinyxml2::XMLDocument doc;
        static Mapa * instance;
        sf::RectangleShape** obstaclesArray;
        sf::RectangleShape obstacles[MAP_ANCHO][MAP_ALTO];
        int mapp[MAP_ANCHO][MAP_ALTO];
        std::string imgFILE;
};