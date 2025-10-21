#include "Enemigo.h"

// Constructor de la clase Personaje
Enemigo::Enemigo(sf::Texture& textura,sf::IntRect chooseimagen, sf::Vector2f posicion,sf::Vector2f Origen,int nivel){
    // e_sprite.setTexture(textura);
    // e_sprite.setOrigin(Origen.x,Origen.y);
    // e_sprite.setTextureRect(chooseimagen);
    // e_sprite.setPosition(posicion.x,posicion.y);
    // e_sprite.setScale(2,2);
    frameactual = 0;
    if(nivel == 1){
        int j = 12;
        for (int i = 0; i < 10; i++) {
                sf::Sprite frame(textura, sf::IntRect(j, 0, 50, 60));
                frame.setScale(1.5,1.5);
                frames.push_back(frame);
                j = j + 64;
        } 
        velocidad = 3;
        vidaenemigo = 125;
    }else if(nivel == 0){
         int j = 288;
      for (int i = 0; i < 11; i++) {
            sf::Sprite frame(textura, sf::IntRect(j, 34, 30, 30));
            frame.setScale(2,2);
            frames.push_back(frame);
            j = j + 32;
        }
        velocidad = 1.5;
        vidaenemigo = 100;
    }else if(nivel == 2){
        cout << "boss creado en Enemigo.cpp" << endl;
        int j = -64;
      for (int i = 0; i < 4; i++) {
            sf::Sprite frame(textura, sf::IntRect(j, 0, 60, 50));
            frame.setScale(3,3);
            frames.push_back(frame);
            j = j + 65;
        }
        velocidad = 2.5;
        vidaenemigo = 2000;
    }
    inter =  nullptr;
    setInterpolacion(posicion, posicion);
    setDireccion('A');
    direccionactual = 'S';
}

void Enemigo::setInterpolacion(sf::Vector2f posicion, sf::Vector2f Origen) {
    if (inter) { // Verificar si el objeto ya existe
        delete inter; // Eliminar objeto anterior
    }
    inter = new Interpolacion(posicion, posicion); // Crear nuevo objeto
    // std::cout << inter->PosicionActual.x << std::endl;
    //  std::cout << inter->PosicionActual.y << std::endl;
}

void Enemigo::setPosicion(float x,float y){
    frames[getFrameactual()].setPosition(x,y);
}
char Enemigo::getDireccion(){
    return Direccion;
}
void Enemigo::setDireccion(char dir){
    Direccion = dir;
    //  std::cout << Direccion << std::endl;
}
//Método para mover el personaje
void Enemigo::nuevaX(float x){

inter->UltimaPosicion.x = inter->PosicionActual.x;
inter->PosicionActual.x = x;
}
float Enemigo::getX(){
  return inter->PosicionActual.x;
}

void Enemigo::nuevaY(float y){
// std::cout << inter->PosicionActual.y + '=' + inter->UltimaPosicion.y << std::endl;
inter->UltimaPosicion.y = inter->PosicionActual.y;
inter->PosicionActual.y = y;
}

float Enemigo::getY(){

  return inter->PosicionActual.y;

}

sf::Vector2f Enemigo::getPosicionActual(){
    if (inter == nullptr){
         std::cout << "jejejje" << std::endl;
    }
     if (inter) { // Verificar si el puntero es nulo o no
    //   std::cout << "hola"<< std::endl;
        return inter->PosicionActual;
    } else {
        std::cerr << "Error: el objeto Interpolacion no ha sido inicializado correctamente." << std::endl;
    }
}

 sf::Vector2f Enemigo::getUltimaPosicion(){

    return inter->UltimaPosicion;

 }
 void Enemigo::PonerFrame(int frame){
    frameactual = frame;
}
std::vector<sf::Sprite> Enemigo::getFrames(){
    return frames;
}
int Enemigo::getFrameactual(){
    return frameactual;
}
void Enemigo::AumentarFrame(){
    // std::cout << "AUMENTO FRAME" << std::endl;
        //  std::cout << frameactual<< std::endl;
        frameactual++;
        //  std::cout << frames.size() << std::endl;
        if(frames.size() == 3){
            //  std::cout << "NOOOOOOOO" << std::endl;
             if(frameactual == 3){
                frameactual = 0;
            }
        }else if(frames.size() == 11){
            //  std::cout << "ECUENCIA" << std::endl;
            if(frameactual == 10){
                //  std::cout << "REINICIO SECUENCIA" << std::endl;
                frameactual = 0;
            }
        }
        else {
            if(frameactual == 3){
                //   std::cout << "REINICIO SECUENCIA" << std::endl;
                frameactual = 0;
            }
        }
}
void Enemigo::ActualizarSprite(){
    AumentarFrame();
    frames[frameactual].setPosition(inter->PosicionActual.x,inter->PosicionActual.y);
}

void Enemigo::elegirSprite(sf::Texture& textura,int top,int ancho,int alto,int nivel){
    // std::cout << top << std::endl;
    //aqui es 0
    if(nivel == 0){
        int j = 288;
      if (Direccion != direccionactual) {
            frames.clear();
            for (int i = 0; i < 3; i++) {
                sf::Sprite frame(textura, sf::IntRect(j, top, ancho, alto));
                frame.setScale(2,2);
                frames.push_back(frame);
                j = j + 32;
            }
        }
    }else if(nivel == 1){ 
          int j = 12;
      if (Direccion != direccionactual) {
          //std::cout << "camnio dir" << std::endl;
            frames.clear();
            for (int i = 0; i < 10; i++) {
                sf::Sprite frame(textura, sf::IntRect(j, top, ancho, alto));
                frame.setScale(1.5,1.5);
                frames.push_back(frame);
                j = j + 64;
            }
        }
    }
    else if(nivel == 2){
        // cout << "BOSSS" << endl;
        int j = -64;
      if (Direccion != direccionactual) {
        //   std::cout << "jajajaj" << std::endl;
            frames.clear();
            for (int i = 0; i < 4; i++) {
                sf::Sprite frame(textura, sf::IntRect(j, top, ancho, alto));
                frame.setScale(3,3);
                frames.push_back(frame);
                j = j + 65;
            }
        }
    }
    direccionactual = Direccion;
}
// Método para obtener las coordenadas del sprite
sf::FloatRect Enemigo::getCoordenadas(){
    return e_sprite.getGlobalBounds();
}

// Método para obtener la posición del sprite
sf::Vector2f Enemigo::getPosicion(){
    return e_sprite.getPosition();
}
//Método para obtener sprite
sf::Sprite Enemigo::getSprite(){
    return frames[getFrameactual()];
}
//Método para mover el personaje
void Enemigo::mover(int x,int y){
    e_sprite.move(x,y);
}


//Método para obtener centro del sprite
sf::Vector2f Enemigo::getCentro(){
    sf::FloatRect rectSprite = frames[getFrameactual()].getGlobalBounds();

    // Calcular la posición del centro del rectángulo
    float centroX = rectSprite.left + rectSprite.width / 2.f;
    float centroY = rectSprite.top + rectSprite.height / 2.f;

    return sf::Vector2f(centroX, centroY);
}

float Enemigo::getVelocidad(){
    return velocidad;
}
void Enemigo::setVelocidad(float velo){
    velocidad = velo;
}
int Enemigo::getVidaEnemigo(){
    return vidaenemigo;
}
void Enemigo::quitarVidaEnemigo(){
    vidaenemigo= vidaenemigo-25;
}
// void Enemigo::moverHacia(sf::Vector2f pos,sf::Time time){
//     // std::cout << "se mueve" << std::endl;
//      // Calculamos el vector dirección hacia el jugador
//     sf::Vector2f direccion = pos - e_sprite.getPosition();
//     // Normalizamos el vector
//     // float longitud = std::sqrt(direccion.x*direccion.x + direccion.y*direccion.y);
//     // direccion /= longitud;
//     // Calculamos la velocidad hacia el jugador
//     velocidad = direccion * 500.0f;
//     // Actualizamos la posición del enemigo
//     e_sprite.setPosition(e_sprite.getPosition() + velocidad * time.asSeconds());
// }
void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(e_sprite, states);
}