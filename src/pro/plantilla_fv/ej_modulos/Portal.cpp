#include "Portal.h"

Portal::Portal(sf::Texture& textura,sf::Vector2f posicion){
    frameactual = 0;
    int j = 5;
     for (int i = 0; i < 8; i++) {
            sf::Sprite frame(textura, sf::IntRect(j, 0, 40, 60));
            frame.setScale(2,2);
            frame.setPosition(posicion);
            frames.push_back(frame);
            j = j + 64;
    }
}
void Portal::PonerFrame(int frame){
     frameactual = frame;
}
int Portal::getFrameactual(){
    return frameactual;
}
void Portal::AumentarFrame(){
        frameactual++;
        if(frameactual == 8){
            frameactual = 0;
        }
}
 std::vector<sf::Sprite> Portal::getFrames(){
     return frames;
 }

 sf::Sprite Portal::getsprite(){
    return frames[getFrameactual()];
}