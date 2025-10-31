#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <Juego.h>
#include <Personaje.h>
#include <HUD.h>
#include "Personaje.h"
#include "Mapa.h"
#include <vector>
#include <Bala.h>
#include <Enemigo.h>
#include <Portal.h>
#include <Colisiones.h>
#include <Mapa.h>
using namespace std;
using namespace sf;
class State;
class MotorGrafico{
    
    public:
        MotorGrafico();
        static MotorGrafico* getInstancia();
        void DrawMenu(sf::RenderWindow *window,sf::Text menu[4], sf::Sprite menusprite,sf::Sprite frame,sf::Sprite fondo);
        void DrawControles(sf::RenderWindow *window, sf::Sprite textura, sf::Text menu, sf::Sprite fondo);
        void DrawPersonaje(sf::RenderWindow *window, Personaje *personaje);
        void DrawHUD(sf::RenderWindow *window,HUD *hud,bool ulti);
        void DrawBalas(sf::RenderWindow *windows, std::vector<Bala*> balas);
        void DrawEnemigo(sf::RenderWindow *window,std::vector<Enemigo*> vectorEnemigos);
        void DrawPortal(sf::RenderWindow *window,Portal *portal);
        void DrawMapa(sf::RenderWindow *window,int numtiles,int map_width,int map_height, sf::RectangleShape** obstaclesArray,sf::Sprite**** tilemapSprite,sf::Sprite* vectorSprite,std::string ruta);
        void DrawBaby(sf::RenderWindow *window,  std::vector<sf::Sprite*> vectorbebes);
        void DrawEstadoPartida(sf::RenderWindow *window, sf::Text text, sf::Text menu[2]);
        void DrawPocimas(sf::RenderWindow *window,std::vector<sf::Sprite*> vectorpocimas);
        sf::RenderWindow *getWindow();
        void InterpolarJugador(float percenTick,Personaje *personaje);
        void InterpolarEnemigo(float percenTick,Enemigo *enemigo);
        void MoverArriba(Personaje *personaje);
        void MoverIzquierda(Personaje *personaje);
        void MoverAbajo(Personaje *personaje);
        void MoverDerecha(Personaje *personaje);
        void MoverEnemigo(Enemigo *enemigo,sf::Vector2f pos,sf::Time time,Personaje *personaje,int nivel);
        // char getDireccion();
    private:
        static MotorGrafico* instance;
        sf::RenderWindow *window;
                Colisiones *coli;
                // Mapa *mapa;
                sf::Texture text,textenemigonivel1, boss;
        // Personaje *personaje = personaje->getInstancia();
};