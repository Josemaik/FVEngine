#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Juego.h"
using namespace std;
class Juego;
class MotorGrafico;
class State{
    public:
        virtual void HandleInput(Juego *juego)=0;
        virtual void Update(Juego *juego)=0;
        virtual void Render(MotorGrafico *motor)=0;
};