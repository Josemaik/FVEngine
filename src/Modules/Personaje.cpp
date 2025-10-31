#include "Personaje.h"
#define NUM_FRAMES 3
// Constructor de la clase Personaje
Personaje::Personaje(sf::Texture& textura,sf::IntRect choosesprite, sf::Vector2f posicion,sf::Vector2f Origen){
    // p_sprite.setTexture(textura);
    // p_sprite.setOrigin(Origen.x,Origen.y);
    // p_sprite.setTextureRect(choosesprite);
    // p_sprite.setPosition(posicion.x,posicion.y);
    // p_sprite.setScale(2,2);
    frameactual = 0;
      for (int i = 0; i < 3; i++) {
            sf::Sprite frame(textura, sf::IntRect(i * 31, 0, 29, 33));
            frame.setScale(2,2);
            frames.push_back(frame);
    }
    // std::cout << posicion.x<< std::endl;
    inter =  nullptr;
    setInterpolacion(posicion, posicion);
    setDireccion('S');
    direccionactual = 'S';
    velocidad = 5.0;
    vidaactual = 5;
}
int Personaje::getVida(){
    return vidaactual;
}

void Personaje::quitarVida(){
    if(vidaactual > 0){
        vidaactual= vidaactual-1;
    }
}
void Personaje::setInterpolacion(sf::Vector2f posicion, sf::Vector2f Origen) {
    if (inter) { // Verificar si el objeto ya existe
        delete inter; // Eliminar objeto anterior
    }
    inter = new Interpolacion(posicion, posicion); // Crear nuevo objeto
    // std::cout << inter->PosicionActual.x << std::endl;
    //  std::cout << inter->PosicionActual.y << std::endl;
}
// Personaje::~Personaje() {
//     delete inter; // Eliminar objeto Interpolacion
// }
// Método para obtener las coordenadas del sprite
sf::FloatRect Personaje::getCoordenadas(){
    return p_sprite.getGlobalBounds();
}
float Personaje::getVelocidad(){
    return velocidad;
}
void Personaje::setVelocidad(float velo){
    velocidad = velo;
}
void Personaje::mover(int x,int y){ //Borrar 
        p_sprite.move(x,y);
}
// Método para obtener la posición del sprite
sf::Vector2f Personaje::getPosicion(){
    // return coordenadas->PosicionActual;
    //esto deberia ser con interpolacion
    // std::cout << coordenadas.PosicionActual.x<< std::endl;
    sf::Vector2f posi = {10-0,11.0};
    return posi;
}
void Personaje::setPosicion(float x,float y){
    frames[getFrameactual()].setPosition(x,y);
}
char Personaje::getDireccion(){
    return Direccion;
}
void Personaje::setDireccion(char dir){
    Direccion = dir;
    //  std::cout << Direccion << std::endl;
}
//Método para mover el personaje
void Personaje::nuevaX(float x){

inter->UltimaPosicion.x = inter->PosicionActual.x;
inter->PosicionActual.x = x;
}
float Personaje::getX(){
  return inter->PosicionActual.x;
}

void Personaje::nuevaY(float y){
// std::cout << inter->PosicionActual.y + '=' + inter->UltimaPosicion.y << std::endl;
inter->UltimaPosicion.y = inter->PosicionActual.y;
inter->PosicionActual.y = y;
}

float Personaje::getY(){

  return inter->PosicionActual.y;

}

sf::Vector2f Personaje::getPosicionActual(){
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

 sf::Vector2f Personaje::getUltimaPosicion(){

    return inter->UltimaPosicion;

 }
void Personaje::PonerFrame(int frame){
    frameactual = frame;
}
std::vector<sf::Sprite> Personaje::getFrames(){
    return frames;
}
int Personaje::getFrameactual(){
    return frameactual;
}
void Personaje::AumentarFrame(){
        frameactual++;
        if(frameactual == 3){
            frameactual = 0;
        }
}
void Personaje::ActualizarSprite(){
    // std::cout << frameactual << std::endl;
    AumentarFrame();
    frames[frameactual].setPosition(inter->PosicionActual.x,inter->PosicionActual.y);
}
//void Personaje::mover(int x,int y){ //Borrar 
// p_sprite.move(x,y);
//}
//Metodo para escalar
void Personaje::escalar(int x,int y){
    p_sprite.setScale(x,y);
}

//Metodo para eligir el sprite de la textura
void Personaje::elegirSprite(sf::Texture& textura,int top,int ancho,int alto){
    // std::cout << top << std::endl;
    
      if (Direccion != direccionactual) {
        frames.clear();
        for (int i = 0; i < 3; i++) {
            sf::Sprite frame(textura, sf::IntRect(i * 31, top, ancho, alto));
            frame.setPosition(getPosicionActual().x,getPosicionActual().y);
            frame.setScale(2,2);
            frames.push_back(frame);
        }
        direccionactual = Direccion;
    }
}
//Método para obtener sprite
sf::Sprite Personaje::getsprite(){
    return frames[getFrameactual()];
}
//Método para obtener centro del sprite
sf::Vector2f Personaje::getCentro(){
     sf::FloatRect rectSprite = frames[getFrameactual()].getGlobalBounds();

    // Calcular la posición del centro del rectángulo
    float centroX = rectSprite.left + rectSprite.width / 2.f;
    float centroY = rectSprite.top + rectSprite.height / 2.f;

    return sf::Vector2f(centroX, centroY);
}

void Personaje::setEstado(EstadoPersonaje estado){
    actual = estado;
}
// EstadoPersonaje Personaje::getEstadoActual(){
//     return actual;
// }