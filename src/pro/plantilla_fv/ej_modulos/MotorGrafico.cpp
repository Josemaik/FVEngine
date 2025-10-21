
#include "MotorGrafico.h"
#include "SFML/Graphics.hpp"
#include <iostream>

MotorGrafico* MotorGrafico::instance = nullptr;
MotorGrafico::MotorGrafico(){
    window = new sf::RenderWindow(sf::VideoMode(1080, 720), "P0. Fundamentos de los Videojuegos. DCCIA");
}
void MotorGrafico::DrawMenu(sf::RenderWindow *window,sf::Text menu[4], sf::Sprite menusprite,sf::Sprite frame,sf::Sprite fondo) {
            window->draw(fondo);

    window->draw(menusprite);
     window->draw(frame);

    // std::cout<< "HE DIBUJADO EL MENU";
   for(int i = 0; i< 4; i++){
        window->draw(menu[i]);
         
    }
   

}

void MotorGrafico::DrawControles(sf::RenderWindow *window,sf::Sprite textura, sf::Text menu,sf::Sprite fondo) {
    // std::cout<< "HE DIBUJADO EL MENU";
                window->draw(fondo);

        window->draw(menu);

        window->draw(textura);
}

void MotorGrafico::DrawPersonaje(sf::RenderWindow *window, Personaje *personaje){
    window->draw(personaje->getFrames()[personaje->getFrameactual()]);
}
void MotorGrafico::DrawHUD(sf::RenderWindow *window,HUD *hud,bool ulti){
     window->draw(hud->getBarra());
    window->draw(hud->getBarraColor());
    window->draw(hud->getGridBarra());
    if(ulti){
        // std::cout << "LASERRRRRRRRRR" << std::endl;
         window->draw(hud->getLaser());
    }else{
         window->draw(hud->getPistola());
    }
    std::vector<sf::Sprite> cora2 = hud->getCora();
    for(int i = 0; i < cora2.size();i++){
        window->draw(cora2[i]);
    }
}
void MotorGrafico::DrawBalas(sf::RenderWindow *window, std::vector<Bala*> balas){
    if(!balas.empty()){
       for (auto& bala : balas)
            window->draw(bala->getSprite());
    }
}
void MotorGrafico::DrawEnemigo(sf::RenderWindow *window,std::vector<Enemigo*> vectorEnemigos){
    for(int i = 0; i < vectorEnemigos.size();i++) {
        window->draw(vectorEnemigos[i]->getFrames()[vectorEnemigos[i]->getFrameactual()]);
    }
}
void MotorGrafico::DrawPortal(sf::RenderWindow *window,Portal *portal){
    window->draw(portal->getFrames()[portal->getFrameactual()]);
}
void MotorGrafico::DrawEstadoPartida(sf::RenderWindow *window, sf::Text text, sf::Text menu[2]){
    window->draw(text);
    for(int i = 0; i < 2 ; i++){
        window->draw(menu[i]);
    }
}
void MotorGrafico::DrawPocimas(sf::RenderWindow *window,std::vector<sf::Sprite*> vectorpocimas){
      for(int i = 0; i < vectorpocimas.size();i++) {
        window->draw(*vectorpocimas[i]);
    }
}
void MotorGrafico::DrawBaby(sf::RenderWindow *window,                       std::vector<sf::Sprite*> vectorbebes){

     for(int i = 0; i < vectorbebes.size();i++) {
        window->draw(*vectorbebes[i]);
    }
}
void MotorGrafico::DrawMapa(sf::RenderWindow *window,int num_tiles,int map_width,int map_height, sf::RectangleShape** obstaclesArray,sf::Sprite**** tilemapSprite,sf::Sprite* vectorSprite,std::string ruta){
    //  std::cout << "holaaaaaaaaaaaa" << std::endl;
            // for (int i = 0; i < num_tiles; i++) {
            //     int x = i % map_width;
            //     int y = i / map_width;
            //     tiles[i].setPosition(x * 32, y * 32);
            //     window->draw(tiles[i]);
            // }
            sf::Texture textura;
            textura.loadFromFile(ruta);
            for (int l = 0; l < num_tiles; l++) {
                for (int y = 0; y < map_height; y++) {
                    for (int x = 0; x < map_width; x++) {
                        sf::Sprite *tesela= new sf::Sprite(textura,tilemapSprite[l][y][x]->getTextureRect());
                        tesela->setPosition(tilemapSprite[l][y][x]->getPosition());
                        if(tilemapSprite[l][y][x] != NULL){
                            //window->draw(*tilemapSprite[l][y][x]);
                            window->draw(*tesela);
                        }
                    }
                }
            }
             for (int i = 0; i < MAP_ANCHO; i++) {
                for (int j = 0; j < MAP_ALTO; j++) {
                   window->draw(obstaclesArray[i][j]);
                }
            }
            // sf::Sprite *tesela= new sf::Sprite(textura,tilemapSprite[0][0][0]->getTextureRect());
            // tesela->setPosition(270,450);
            // window->draw(*tesela);
}
sf::RenderWindow *MotorGrafico::getWindow(){
    return window;
}
MotorGrafico* MotorGrafico::getInstancia(){
    if(instance == nullptr){
        instance = new MotorGrafico();
    }
    return instance;
}
void MotorGrafico::InterpolarJugador(float PercenTick,Personaje *personaje){
    //  std::cout << PercenTick << std::endl;
    float drawX = personaje->getUltimaPosicion().x * (1.0 - PercenTick) + personaje->getPosicionActual().x * PercenTick;
    float drawY = personaje->getUltimaPosicion().y * (1.0 - PercenTick) + personaje->getPosicionActual().y * PercenTick;

    personaje->setPosicion(drawX,drawY);
}
void MotorGrafico::InterpolarEnemigo(float PercenTick,Enemigo *enemigo){
    //  std::cout << PercenTick << std::endl;
    float drawX = enemigo->getUltimaPosicion().x * (1.0 - PercenTick) + enemigo->getPosicionActual().x * PercenTick;
    float drawY = enemigo->getUltimaPosicion().y * (1.0 - PercenTick) + enemigo->getPosicionActual().y * PercenTick;

    enemigo->setPosicion(drawX,drawY);
}
// char MotorGrafico::getDireccion(){
//     return personaje->getDireccion();
// }
void MotorGrafico::MoverArriba(Personaje *personaje){
    // std::cout << "arriba" << std::endl;
    // std::cout << personaje->getPosicionActual().x  + '=' + personaje->getPosicionActual().y << std::endl;
    sf::Vector2f nuevaPosicion = sf::Vector2f(personaje->getPosicionActual().x,personaje->getPosicionActual().y - personaje->getVelocidad());
    // personaje->setVelocidad(0.0);
    // std::cout << "Saleee" << std::endl;
    personaje->nuevaY(nuevaPosicion.y);
    personaje->ActualizarSprite();
}
void MotorGrafico::MoverIzquierda(Personaje *personaje){
    // std::cout << "izquierda" << std::endl;
    // std::cout << personaje->getPosicionActual().x  + '=' + personaje->getPosicionActual().y << std::endl;
    sf::Vector2f nuevaPosicion = sf::Vector2f(personaje->getPosicionActual().x - personaje->getVelocidad(),personaje->getPosicionActual().y);
    // personaje->setVelocidad(0.0);
    //std::cout << "Saleee" << std::endl;
    personaje->nuevaX(nuevaPosicion.x);
    personaje->ActualizarSprite();
}
void MotorGrafico::MoverAbajo(Personaje *personaje){
    // std::cout << "abajo" << std::endl;
    // std::cout << personaje->getPosicionActual().x  + '=' + personaje->getPosicionActual().y << std::endl;
    sf::Vector2f nuevaPosicion = sf::Vector2f(personaje->getPosicionActual().x,personaje->getPosicionActual().y + personaje->getVelocidad());
    // personaje->setVelocidad(0.0);
    //std::cout << "Saleee" << std::endl;
    personaje->nuevaY(nuevaPosicion.y);
    personaje->ActualizarSprite();
}
void MotorGrafico::MoverDerecha(Personaje *personaje){
    // std::cout << "derecha" << std::endl;
    // std::cout << personaje->getPosicionActual().x  + '=' + personaje->getPosicionActual().y << std::endl;
    sf::Vector2f nuevaPosicion = sf::Vector2f(personaje->getPosicionActual().x + personaje->getVelocidad(),personaje->getPosicionActual().y);
    // personaje->setVelocidad(0.0);
    //std::cout << "Saleee" << std::endl;
    personaje->nuevaX(nuevaPosicion.x);
    personaje->ActualizarSprite();
}
void MotorGrafico::MoverEnemigo(Enemigo *enemigo,sf::Vector2f pos,sf::Time time,Personaje *personaje,int nivel){
    text.loadFromFile("resources/sprites2.png");
    textenemigonivel1.loadFromFile("resources/goblinsword.png");
    boss.loadFromFile("resources/boss.png");
    // std::cout << "se mueve" << std::endl;
     // Calculamos el vector dirección hacia el jugador
    sf::Vector2f direccion = pos - enemigo->getPosicionActual();
    // Normalizamos el vector
    // float longitud = std::sqrt(direccion.x*direccion.x + direccion.y*direccion.y);
    // direccion /= longitud;
    // Calculamos la velocidad hacia el jugador
    // enemigo->setVelocidad(direccion * 15000.0f);

     if (direccion.x > 0 && std::abs(direccion.x) > std::abs(direccion.y)) {
        // std::cout << "derecha" << std::endl;
         enemigo->setDireccion('D');
         //Luego cambiarlo lo pongo al reves para probar
         if(nivel == 0){
            //  enemigo->elegirSprite(text,65,30,30,0);
             //CAMBIO LUEGO A 0 PORQUE ESOTY
            enemigo->elegirSprite(text,0,30,30,0);
         }else if(nivel == 1){ 
             enemigo->elegirSprite(textenemigonivel1,60,50,60,1);
         }
         else if(nivel == 2){
             enemigo->elegirSprite(boss,130,60,60,2);
         }
         enemigo->nuevaX(enemigo->getPosicionActual().x + enemigo->getVelocidad());
    } else if (direccion.x < 0 && std::abs(direccion.x) > std::abs(direccion.y)) {
        // std::cout << "izquierda" << std::endl;
         enemigo->setDireccion('A');
         if(nivel == 0){
            //  enemigo->elegirSprite(text,34,30,30,0);
             //CAMBIO LUEGO A 0 PORQUE ESOTY
            enemigo->elegirSprite(text,0,30,30,0);
         }else if(nivel == 1){
             enemigo->elegirSprite(textenemigonivel1,200,50,60,1);
         }
         else if(nivel == 2){
             enemigo->elegirSprite(boss,195,60,60,2);
         }
        enemigo->nuevaX(enemigo->getPosicionActual().x - enemigo->getVelocidad());
    } else if (direccion.y < 0 && std::abs(direccion.y) > std::abs(direccion.x)) {
        // std::cout << "arriba" << std::endl;
         enemigo->setDireccion('W');
         if(nivel == 0){
            enemigo->elegirSprite(text,96,30,30,0);
             //CAMBIO LUEGO A 0 PORQUE ESOTY
         }else if(nivel == 1){
             enemigo->elegirSprite(textenemigonivel1,140,50,57,1);
         }
         else if(nivel == 2){
             enemigo->elegirSprite(boss,65,60,60,2);
         }
        enemigo->nuevaY(enemigo->getPosicionActual().y - enemigo->getVelocidad());
    } else if (direccion.y > 0 && std::abs(direccion.y) > std::abs(direccion.x)) {
        // std::cout << "abajo" << std::endl;
         enemigo->setDireccion('S');
         if(nivel == 0){
             //CAMBIO LUEGO A 0 PORQUE ESOTY
            enemigo->elegirSprite(text,0,30,30,0);
         }else if(nivel == 1){
             enemigo->elegirSprite(textenemigonivel1,0,50,60,1);
         }
         else if(nivel == 2){
             //cout << "entro en el 2 de MotorGrafico" << endl;
             enemigo->elegirSprite(boss,0,60,60,2);
         }
        enemigo->nuevaY(enemigo->getPosicionActual().y + enemigo->getVelocidad());
    }

    // Actualizamos la posición del enemigo
    enemigo->ActualizarSprite();
}