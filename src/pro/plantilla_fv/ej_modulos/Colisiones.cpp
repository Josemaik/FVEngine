#include "Colisiones.h"
#include <iostream>
bool Colisiones::ComprobarColisionObstaculo(sf::FloatRect rectP,sf::RectangleShape** obstaclesArray,int desplazamiento){
    sf::FloatRect rectPAfterMove = rectP;
    rectPAfterMove.left += desplazamiento;
    bool noColisiona = true;
    //Comprobar si el rectángulo del jugador colisiona con algún obstáculo
    for (int i = 0; i < 36; i++) {
            for (int j = 0; j < 24; j++) {
                    if (rectPAfterMove.intersects(obstaclesArray[i][j].getGlobalBounds())) {
                        noColisiona = false;
                        break;
                }
            }
    }
    return noColisiona;
}
void Colisiones::ColisionesPersonajes(Personaje *personaje,Enemigo *enemigo,sf::RectangleShape** obstaclesArray,HUD *hud) {
    //Obtengo los rectángulos del personaje y enemigo
    sf::FloatRect rectP = personaje->getsprite().getGlobalBounds();
    sf::FloatRect rectE = enemigo->getSprite().getGlobalBounds();
    //Obtengo los centros del personaje y enemigo
    sf::Vector2f CentroP = personaje->getCentro();
    sf::Vector2f CentroE = enemigo->getCentro();
    //Obtengo diferencias de centros en el eje x e y
    float difX = std::abs(CentroP.x - CentroE.x);
    float difY = std::abs(CentroP.y - CentroE.y);
    //reducimos el tamaño del rectángulo
    rectP.width /= 2;
    rectE.width /= 2;
    rectP.height /= 2;
    rectE.height /= 2;
    //En caso de colisionar
    if(rectP.intersects(rectE)){
        //  std::cout << "HAN COLISIONADO LOS PERSONAJES";

         std::cout << personaje->getVida();

        //hit.play();
        personaje->quitarVida();
         std::cout << personaje->getVida();
        hud->QuitarCora();
         if(difX > difY){
             if (CentroP.x > CentroE.x)//Colision lado derecho
             {
                 std::cout << "DERECHA";
                 // personaje->mover(70,0);
                // enemigo->mover(-20,0);
                sf::FloatRect rectPAfterMove = rectP;
                rectPAfterMove.left += 30;
                bool noColisiona = true;
                //Comprobar si el rectángulo del jugador colisiona con algún obstáculo
                for (int i = 0; i < 36; i++) {
                        for (int j = 0; j < 24; j++) {
                             if (rectPAfterMove.intersects(obstaclesArray[i][j].getGlobalBounds())) {
                                    noColisiona = false;
                                    break;
                            }
                        }
                }
                //Si el jugador no colisiona con ningún obstáculo, se actualiza su posición
                if (noColisiona) {
                    personaje->nuevaX(personaje->getPosicionActual().x + 30);
                    personaje->ActualizarSprite();
                }
                //  personaje->nuevaX(personaje->getPosicionActual().x + 30);
                 enemigo->nuevaX(enemigo->getPosicionActual().x - 20);
                // personaje->ActualizarSprite();
                enemigo->ActualizarSprite();
             }else{ //Colision lado izquierdo
             std::cout << "IZQUIERDA";
              sf::FloatRect rectPAfterMove = rectP;
                rectPAfterMove.left -= 30;
                bool noColisiona = true;
                //Comprobar si el rectángulo del jugador colisiona con algún obstáculo
                for (int i = 0; i < 36; i++) {
                        for (int j = 0; j < 24; j++) {
                             if (rectPAfterMove.intersects(obstaclesArray[i][j].getGlobalBounds())) {
                                    noColisiona = false;
                                    break;
                            }
                        }
                }
                //Si el jugador no colisiona con ningún obstáculo, se actualiza su posición
                if (noColisiona) {
                    personaje->nuevaX(personaje->getPosicionActual().x - 30);
                    personaje->ActualizarSprite();
                }
            //  personaje->nuevaX(personaje->getPosicionActual().x - 30);
                 enemigo->nuevaX(enemigo->getPosicionActual().x + 20);
                // personaje->ActualizarSprite();
                enemigo->ActualizarSprite();
                // personaje->mover(-70,0);
                // enemigo->mover(20,0);
             }
         }else{
             if(CentroP.y > CentroE.y){
                 std::cout << "ABAJO";
                  sf::FloatRect rectPAfterMove = rectP;
                rectPAfterMove.top += 30;
                bool noColisiona = true;
                //Comprobar si el rectángulo del jugador colisiona con algún obstáculo
                for (int i = 0; i < 36; i++) {
                        for (int j = 0; j < 24; j++) {
                             if (rectPAfterMove.intersects(obstaclesArray[i][j].getGlobalBounds())) {
                                    noColisiona = false;
                                    break;
                            }
                        }
                }
                //Si el jugador no colisiona con ningún obstáculo, se actualiza su posición
                if (noColisiona) {
                    personaje->nuevaY(personaje->getPosicionActual().y + 30);
                    personaje->ActualizarSprite();
                }
                //  personaje->nuevaY(personaje->getPosicionActual().x + 30);
                 enemigo->nuevaY(enemigo->getPosicionActual().y -20);
                //  ColisionPersonajeParedes(personaje,obstaclesArray);
                // personaje->ActualizarSprite();
                enemigo->ActualizarSprite();
                //  personaje->mover(0,70);
                // enemigo->mover(0,-20);
             }else{
                 std::cout << "ARRIBA";
                  sf::FloatRect rectPAfterMove = rectP;
                rectPAfterMove.top -= 30;
                bool noColisiona = true;
                //Comprobar si el rectángulo del jugador colisiona con algún obstáculo
                for (int i = 0; i < 36; i++) {
                        for (int j = 0; j < 24; j++) {
                             if (rectPAfterMove.intersects(obstaclesArray[i][j].getGlobalBounds())) {
                                    noColisiona = false;
                                    break;
                            }
                        }
                }
                //Si el jugador no colisiona con ningún obstáculo, se actualiza su posición
                if (noColisiona) {
                    personaje->nuevaY(personaje->getPosicionActual().y - 30);
                    personaje->ActualizarSprite();
                }
                //  personaje->nuevaY(personaje->getPosicionActual().y - 30);
                 enemigo->nuevaY(enemigo->getPosicionActual().y + 20);
                // personaje->ActualizarSprite();
                enemigo->ActualizarSprite();
                //  personaje->mover(0,-70);
                // enemigo->mover(0,20);
             }
         }
         ColisionPersonajeParedes(personaje,obstaclesArray);
    }
}

void Colisiones::ColisionPersonajeParedes(Personaje *character, sf::RectangleShape** obstacles) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 24; j++) {
            if (obstacles[i][j].getGlobalBounds().intersects(character->getsprite().getGlobalBounds())) {
                sf::FloatRect characterBounds = character->getsprite().getGlobalBounds();
                sf::FloatRect obstacleBounds = obstacles[i][j].getGlobalBounds();
                
                // Calculate the overlap between the character and obstacle
                float overlapLeft = characterBounds.left + characterBounds.width - obstacleBounds.left;
                float overlapRight = obstacleBounds.left + obstacleBounds.width - characterBounds.left;
                float overlapTop = characterBounds.top + characterBounds.height - obstacleBounds.top;
                float overlapBottom = obstacleBounds.top + obstacleBounds.height - characterBounds.top;
                
                // Determine the direction of minimum overlap
                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
                if (minOverlap == overlapLeft) {
                    
                    float newPos = character->getPosicionActual().x - overlapLeft;
                    if(newPos > 0 && character->getDireccion() == 'D'){
                        std::cout << "derecha" << std::endl;
                        character->nuevaX(newPos);
                        character->ActualizarSprite();
                    }
                } else if (minOverlap == overlapRight) {
                    
                    float newPos = character->getPosicionActual().x + overlapRight;
                    if(newPos > 0 && character->getDireccion() == 'A'){
                        std::cout << "izquierda" << std::endl;
                        character->nuevaX(newPos);
                        character->ActualizarSprite();
                    }
                } else if (minOverlap == overlapTop) {
                    
                    float newPos = character->getPosicionActual().y - overlapTop;
                    if(newPos > 0 && character->getDireccion() == 'S'){
                        std::cout << "abajo" << std::endl;
                        character->nuevaY(newPos);
                        character->ActualizarSprite();
                    }
                } else if (minOverlap == overlapBottom) {
                    
                    float newPos = character->getPosicionActual().y + overlapBottom;
                    if(newPos > 0 && character->getDireccion() == 'W'){
                        std::cout << "arriba" << std::endl;
                        character->nuevaY(newPos);
                        character->ActualizarSprite();
                    }
                }
            }
        }
    }
}


void Colisiones::ColisionEnemigoParedes(Enemigo *enemigo,sf::RectangleShape** obstacles){
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 24; j++) {
            if (obstacles[i][j].getGlobalBounds().intersects(enemigo->getSprite().getGlobalBounds())) {
                sf::FloatRect characterBounds = enemigo->getSprite().getGlobalBounds();
                sf::FloatRect obstacleBounds = obstacles[i][j].getGlobalBounds();
                
                // Calculate the overlap between the character and obstacle
                float overlapLeft = characterBounds.left + characterBounds.width - obstacleBounds.left;
                float overlapRight = obstacleBounds.left + obstacleBounds.width - characterBounds.left;
                float overlapTop = characterBounds.top + characterBounds.height - obstacleBounds.top;
                float overlapBottom = obstacleBounds.top + obstacleBounds.height - characterBounds.top;
                
                // Determine the direction of minimum overlap
                float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
                if (minOverlap == overlapLeft) {
                    enemigo->nuevaX(enemigo->getPosicionActual().x -overlapLeft);
                    enemigo->ActualizarSprite();
                } else if (minOverlap == overlapRight) {
                    enemigo->nuevaX(enemigo->getPosicionActual().x +overlapRight);
                    enemigo->ActualizarSprite();
                } else if (minOverlap == overlapTop) {
                    enemigo->nuevaY(enemigo->getPosicionActual().y -overlapTop);s
                    enemigo->ActualizarSprite();
                } else if (minOverlap == overlapBottom) {
                    enemigo->nuevaY(enemigo->getPosicionActual().y +overlapBottom);
                    enemigo->ActualizarSprite();
                }
            }
        }
    }
}
bool Colisiones::ColisionBalaEnemigo(Enemigo *enemigo, Bala *bala){
    // Obtengo los rectángulos del personaje y enemigo
    sf::FloatRect rectE = enemigo->getSprite().getGlobalBounds();
    sf::FloatRect rectB = bala->getSprite().getGlobalBounds();
    rectE.width /= 2;
    rectB.width /= 2;
    if(rectB.intersects(rectE)){
        // std::cout << "HA COLISIONADO LA BALA";
        enemigo->quitarVidaEnemigo();
        return true;
    }
    return false;
}
bool Colisiones::ColisionBalaParedes(Bala *bala,sf::RectangleShape** obstaclesArray){
     for (int i = 0; i < 36; i++) {
            for (int j = 0; j < 24; j++) {
                sf::FloatRect rectObs = obstaclesArray[i][j].getGlobalBounds();
                sf::FloatRect rectB = bala->getSprite().getGlobalBounds();
                rectB.width /=2;
                rectObs.width /= 2;
                if (rectObs.intersects(rectB)){
                    return true;
                }
            }
    }
    return false;
}
bool Colisiones::ColisionBalaPortal(Portal *portal,Bala *bala){
     sf::FloatRect rectBa = bala->getSprite().getGlobalBounds();
    sf::FloatRect rectPor = portal->getsprite().getGlobalBounds();
    rectBa.width /= 2;
    rectPor.width /= 2;
     if(rectBa.intersects(rectPor)){
        std::cout << "HA COLISIONADO PORTAL";
        return true;
    }
    return false;
}
 bool Colisiones::ColisionPersonajePortal(Personaje *personaje,Portal *portal){
     sf::FloatRect rectPer = personaje->getsprite().getGlobalBounds();
    sf::FloatRect rectPor = portal->getsprite().getGlobalBounds();
      rectPer.width /= 2;
        rectPor.width /= 2;
        rectPer.height /= 2;
        rectPor.height /= 2;
     if(rectPer.intersects(rectPor)){
        std::cout << "HA COLISIONADO PORTAL";
        return true;
    }
    return false;
 }
 bool Colisiones::ColisionBebe(Personaje *personaje,std::vector<sf::Sprite*> bebes){
    for(int i = 0; i < bebes.size();i++){
        sf::FloatRect rectBebe = bebes[i]->getGlobalBounds();
        sf::FloatRect rectPer = personaje->getsprite().getGlobalBounds();
        rectPer.width /= 2;
        rectBebe.width /= 2;
        if(rectPer.intersects(rectBebe)){
            std::cout << "HA COLISIONADO PORTAL";
            return true;
        }
    }
    return false;
 }

int Colisiones::ColisionPersonajePocima(Personaje *personaje, std::vector<sf::Sprite*> vectorpocimas){
    for(int i = 0; i < vectorpocimas.size();i++){
        sf::FloatRect rectPoc = vectorpocimas[i]->getGlobalBounds();
        sf::FloatRect rectPer = personaje->getsprite().getGlobalBounds();
        rectPer.width /= 2;
        rectPoc.width /= 2;
        if(rectPer.intersects(rectPoc)){
            return i;
        }
    }
    return -1;
}