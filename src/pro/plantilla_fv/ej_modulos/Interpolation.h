#ifndef TYPES_H
#pragma once
#include <iostream>
#define TYPES_H
#include "SFML/Graphics.hpp"

class Interpolacion {

    public:

        sf::Vector2f PosicionActual;
        sf::Vector2f UltimaPosicion;
      

        Interpolacion(sf::Vector2f actual, sf::Vector2f ultimo){
            PosicionActual = actual;
            UltimaPosicion = ultimo;
        }

typedef Interpolacion Posicion;

};
#endif