
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "EstadoJugando.h"
#include <EstadoWinLose.h>
#define UPDATE_TICK_TIME 1000/15
#define kVel 5

Jugando *Jugando::instance = nullptr;
Jugando* Jugando::getInstancia(){
    MotorGrafico *motor = MotorGrafico::getInstancia();
    if(instance == 0){
        instance = new Jugando(motor->getWindow()->getSize().x,motor->getWindow()->getSize().y);
    }
    return instance;
}


Jugando::Jugando(float width, float height){
    text.loadFromFile("resources/sprites2.png");
    textenemigonivel1.loadFromFile("resources/goblinsword.png");
    boss.loadFromFile("resources/boss.png");
    textportal.loadFromFile("resources/Purple Portal Sprite Sheet.png");
    personaje = new Personaje(text,sf::IntRect(0 * 75, 0 * 75, 30, 30),  {480,80},{75/2,75/2});
    hudT0.loadFromFile("resources/cora.png");
    hudT1.loadFromFile("resources/Bar.png");
    hudT2.loadFromFile("resources/BarColor.png");
    hudT3.loadFromFile("resources/gridBar.png");
    //hudT4.loadFromFile("resources/Gamer.ttf");
    hudT6.loadFromFile("resources/pistola.png");
    texlaser.loadFromFile("resources/laser.png");
    mapa = new Mapa("resources/inicio.tmx");
    hud = new HUD(hudT0, hudT1, hudT2, hudT3, hudT6,texlaser);
    texBala.loadFromFile("resources/bala.png");
    textUlti.loadFromFile("resources/ulti.png");
    textpocima.loadFromFile("resources/pocionvida.png");
    textbebe.loadFromFile("resources/bebe.png");
   //enemigo = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{420,240},{100/2,100/2});
   vidaanterior = 600;
   enemigo_creado = false;
   recompensa_recogida = false;
   sf::Sprite *pocima = new sf::Sprite();
   pocima->setTexture(textpocima);
   pocima->setPosition(420,550);
   pocima->setScale(0.05,0.05);
   sf::Sprite *pocima1 = new sf::Sprite();
    pocima1->setTexture(textpocima);
    pocima1->setPosition(420,350);
    pocima1->setScale(0.05,0.05);
     sf::Sprite *pocima2 = new sf::Sprite();
    pocima2->setTexture(textpocima);
    pocima2->setPosition(420,150);
    pocima2->setScale(0.05,0.05);
    vectorpocimas.push_back(pocima);
    vectorpocimas.push_back(pocima1);
    vectorpocimas.push_back(pocima2);
    sf::Sprite *bebe = new sf::Sprite();
    bebe->setTexture(textbebe);
    bebe->setTextureRect(sf::IntRect(35,64,25,34));
    bebe->setPosition(1000,280);
    bebe->setScale(1.5,1.5);
    vectorbebe.push_back(bebe);
    time0 = 0;
    setEstado(EstadoPartida::RESPAWN);
    if(actual == EstadoPartida::RESPAWN){
       portal = new Portal(textportal,{1000,350});
   }
    if (!inicioBuffer.loadFromFile("resources/inicio.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    inicio.setBuffer(inicioBuffer);
    inicio.play();

   if (!disparoBuffer.loadFromFile("resources/pistol.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    disparoSound.setBuffer(disparoBuffer);
    disparoSound.setVolume(50);

    if (!portalBuffer.loadFromFile("resources/portal2.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    portalsound.setBuffer(portalBuffer);

    if (!level1Buffer.loadFromFile("resources/normalevel.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    level1.setBuffer(level1Buffer);

    if (!finalBuffer.loadFromFile("resources/bebeBoss.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    finalS.setBuffer(finalBuffer);

    if (!disparonormalBuffer.loadFromFile("resources/disparonormal.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    disparonormal.setBuffer(disparonormalBuffer);
    disparonormal.setVolume(50);

    if (!ultiBuffer.loadFromFile("resources/ulti.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    ultisound.setBuffer(ultiBuffer);
    ultisound.setVolume(100);

    if (!winnerBuffer.loadFromFile("resources/win.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    winnersound.setBuffer(winnerBuffer);

    if (!gameoverBuffer.loadFromFile("resources/gameover.wav")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    gameover.setBuffer(gameoverBuffer);
    if (!rugidoBuffer.loadFromFile("resources/bossFin.ogg")) {
    std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    rugido.setBuffer(rugidoBuffer);
    
    if (!bebeBuffer.loadFromFile("resources/bebe.ogg")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    bebeS.setBuffer(bebeBuffer);

    if (!masVBuffer.loadFromFile("resources/masVida.wav")) {
        std::cerr << "Error al cargar el archivo de sonido de disparo." << std::endl;
    }

    masV.setBuffer(masVBuffer);
}

    


bool Jugando::getGanado() {
    return ganado;
}
Jugando::~Jugando(){
    delete personaje;
    delete hud;
    delete mapa;
    for(int i = 0; i < 3; i++){
       delete vectorEnemigos[i];
    }
    // delete enemigo;
    delete coli;
    for(auto bala : balas){
        delete bala;
    }
    balas.clear();
    if (portal){
        delete portal;
    }
    instance = nullptr;
}
void Jugando::setEstado(EstadoPartida estado){
        if (estado == EstadoPartida::NIVEL0) {
            tiempo_aparicion = sf::Time::Zero;
        }
        actual = estado;
}
void Jugando::HandleInput(Juego *juego){
    sf::Event event;
        hud->posicionarHUD();
    while (juego->motor->getWindow()->pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
                juego->motor->getWindow()->close();
                juego->StopRunning();
                // delete instance;
                // delete instance; instance = NULL;
                break;
        case sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button) {
                    case sf::Mouse::Right:
                    // std::cout << personaje->getDireccion() << std::endl;
                    // std::cout << "VOY A CREAR BALAS" << std::endl;
                    if(ulti){
                        disparoSound.play();
                    }else disparonormal.play();
                    
                    
                    switch (personaje->getDireccion()) {
                        //  std::cout << "VOY A CREAR BALita xd" << std::endl;
                        case 'D': if(!ulti) {
                            bala = new Bala(texBala,{0.04,0.04},{personaje->getCentro().x + 65,personaje->getCentro().y+25},180,{0.75,0});
                            balas.push_back(bala);
                        }else{
                            bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x + 20,personaje->getCentro().y},0,{0.5,0});
                            balas.push_back(bala);
                            bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x + 20,personaje->getCentro().y},-45,{0.5,-0.5});
                            balas.push_back(bala);
                            bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x + 30,personaje->getCentro().y},45,{0.5,0.5});
                            balas.push_back(bala);
                        }
                        break;
                        case 'A': 
                        if(!ulti) {
                            // disparo.play();
                            bala = new Bala(texBala,{0.04,0.04},{personaje->getCentro().x-50,personaje->getCentro().y-15},0,{-0.75,0});
                            balas.push_back(bala);
                        }else{
                             bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x-20,personaje->getCentro().y+10},180,{-0.5,0});
                            balas.push_back(bala);
                            bala = new Bala(textUlti,{0.3,0.3}, {personaje->getCentro().x-30, personaje->getCentro().y}, 225, {-0.5, -0.5});
                            balas.push_back(bala);
                            bala = new Bala(textUlti,{0.3,0.3}, {personaje->getCentro().x, personaje->getCentro().y}, 135, {-0.5, 0.5});
                            balas.push_back(bala);
                        }
                        break;
                        case 'W': if(!ulti) {
                            // disparo.play();
                            bala = new Bala(texBala,{0.04,0.04},{personaje->getCentro().x+15,personaje->getCentro().y-80},90,{0,-0.75});
                            balas.push_back(bala);
                        }else{
                             bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x-10,personaje->getCentro().y-20},-90,{0,-0.5});
                            balas.push_back(bala);
                            bala = new Bala(textUlti,{0.3,0.3}, {personaje->getCentro().x, personaje->getCentro().y-20}, 225, {-0.5, -0.5});
                            balas.push_back(bala);
                            bala = new Bala(textUlti, {0.3,0.3},{personaje->getCentro().x , personaje->getCentro().y-50}, -45, {0.5, -0.5});
                            balas.push_back(bala);
                        }
                        break;
                        case 'S': if(!ulti) {
                            // disparo.play();
                            bala = new Bala(texBala,{0.04,0.04},{personaje->getCentro().x-15,personaje->getCentro().y+80},-90,{0,0.75});
                            balas.push_back(bala);
                        }else{
                            bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x+30,personaje->getCentro().y+20},90,{0,0.5});
                            balas.push_back(bala);
                            bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x+20,personaje->getCentro().y+40},135,{-0.5,0.5});
                            balas.push_back(bala);
                            bala = new Bala(textUlti,{0.3,0.3},{personaje->getCentro().x+20,personaje->getCentro().y+10},45,{0.5,0.5});
                            balas.push_back(bala);
                        }
                        break;
                        default:
                        break;
                    }
                    // Bala *bala = new Bala(texbala,{personaje->getPosicion().x + 30,personaje->getPosicion().y+20},{75/2,75/2});
                    // std::cout << "BALA CREADA";
                    break;
        }
        case sf::Event::KeyPressed:
        evento = true;
          switch (event.key.code) {
            case sf::Keyboard::W:
                personaje->setDireccion('W');
                personaje->elegirSprite(text,96,30,30);
                // personje->setDireccion("W");
                // personaje->mover(0, -kVel);
                break;
            case sf::Keyboard::A:
                personaje->setDireccion('A');
                personaje->elegirSprite(text,34,30,30);
                //Reflejo vertical
                // personaje->mover(-kVel, 0);
                break;
            case sf::Keyboard::S:
                personaje->setDireccion('S');
                personaje->elegirSprite(text,0,29,33);
                // personaje->mover(0, kVel);
                break;
            case sf::Keyboard::D:
                personaje->setDireccion('D');
                personaje->elegirSprite(text,65,30,30);
                //Escala por defecto
                // personaje->mover(kVel, 0);
                break;
          }
        // coli->ColisionesPersonajes(personaje,enemigo);
        }
    }
    // std::cout << evento << std::endl;
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) == false && sf::Keyboard::isKeyPressed(sf::Keyboard::S) == false && sf::Keyboard::isKeyPressed(sf::Keyboard::A) == false && sf::Keyboard::isKeyPressed(sf::Keyboard::D) == false){
         evento = false;
        // personaje->setDireccion('Q');
    }
}
void Jugando::Update(Juego *juego){
    //disparo.play();
    if(!balas.empty()){
          for (auto& bala : balas)
          bala->mover(bala->getdir().x,bala->getdir().y);
    }
     if(!balas.empty()){
      for (auto it = balas.begin(); it != balas.end();){
        if (coli->ColisionBalaParedes(bala,mapa->getObstacles())){
          it = balas.erase(it);
        }else{
          ++it;
        }
      }
      if(portal){
          for (auto it = balas.begin(); it != balas.end();){
                if (coli->ColisionBalaPortal(portal,bala)){
                     cout << "HOLAAAA" << endl;
                    it = balas.erase(it);
                }else{
                    ++it;
                }
         }
      }
      if(enemigo_creado == true && vectorEnemigos.size() != 0){
           for(int i = 0; i < vectorEnemigos.size();i++) {
               for (auto it = balas.begin(); it != balas.end();){
                    if (coli->ColisionBalaEnemigo(vectorEnemigos[i], *it)){
                        it = balas.erase(it);
                        if (vectorEnemigos[i]->getVidaEnemigo() == 0) {
                            vectorEnemigos.erase(vectorEnemigos.begin() + i);
                            if(!ulti){
                                hud->AumentarExp(hudT2);
                            }
                        }
                    }else{
                        ++it;
                    }
                }
           }
      }
    }
    sf::Clock reloj;
    // std::cout << "NO UPDATE" << std::endl;
    int numLoops = 4;
    maxLoops = 8;
    long time1 = clock.getElapsedTime().asMilliseconds();
    long deltaTime = time1 - this->time0;
    // std::cout << numLoops<< std::endl;
    // std::cout << maxLoops<< std::endl;
    while(deltaTime > UPDATE_TICK_TIME && numLoops < maxLoops){
         sf::Time tiempotranscurrido = reloj.restart();
        // std::cout << personaje->getDireccion() << std::endl;
        if(evento == true){
            if(personaje->getDireccion() == 'W'){
            // std::cout << "arrriba españaaa" << std::endl;
            juego->motor->MoverArriba(personaje);
            }else{
                if(personaje->getDireccion() == 'A'){
                    juego->motor->MoverIzquierda(personaje);
                }else{
                    if(personaje->getDireccion() == 'S'){
                        juego->motor->MoverAbajo(personaje);
                    }else{
                        if(personaje->getDireccion() == 'D'){
                            juego->motor->MoverDerecha(personaje);
                        }
                    }
                }
            }
        }
        if(getEstadoActual() == EstadoPartida::RESPAWN){
            if(portal){
                if(coli->ColisionPersonajePortal(personaje,portal)){
                    std::cout << "PASO A NIVEL 0" << std::endl;
                    inicio.stop();
                    portalsound.play();
                    delete portal;
                    portal = NULL;
                    delete mapa;
                    mapa = NULL;
                    mapa = new Mapa("resources/infierno1.tmx");
                    setEstado(EstadoPartida::NIVEL0);
                    level1.play();
                    personaje->nuevaX(100);
                    //PROBAR EL BOSS
                    Enemigo *enemigo = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{620,100},{100/2,100/2},0);
                    vectorEnemigos.push_back(enemigo);
                     Enemigo *enemigo1 = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{620,240},{100/2,100/2},0);
                    vectorEnemigos.push_back(enemigo1);
                    Enemigo *enemigo2 = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{620,440},{100/2,100/2},0);
                    vectorEnemigos.push_back(enemigo2);
                    Enemigo *enemigo3 = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{620,550},{100/2,100/2},0);
                    vectorEnemigos.push_back(enemigo3);
                    Enemigo *enemigo4 = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{320,550},{100/2,100/2},0);
                    vectorEnemigos.push_back(enemigo4);
                     Enemigo *enemigo5 = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{120,550},{100/2,100/2},0);
                    vectorEnemigos.push_back(enemigo5);
                     Enemigo *enemigo6 = new Enemigo(text,sf::IntRect(290, 0, 30, 30),{420,80},{100/2,100/2},0);
                    vectorEnemigos.push_back(enemigo6);
                    enemigo_creado = true;
                }
            }
        }
        if(getEstadoActual() == EstadoPartida::NIVEL0){
            if(vectorEnemigos.size() == 0){
                 if(portal == nullptr){
                     portal =  new Portal(textportal,{1000,280});
                 }
                 if(coli->ColisionPersonajePortal(personaje,portal)){
                     delete portal;
                    portal = NULL;
                     if(ulti){
                         hud->reiniciarExp(hudT2);
                         ulti = false;
                     }
                     std::cout << "PASO A NIVEL 1" << std::endl;
                     portalsound.play();
                     level1.play();
                    setEstado(EstadoPartida::NIVEL1);
                    personaje->nuevaX(100);
                     Enemigo *enemigo = new Enemigo(textenemigonivel1,sf::IntRect(290, 0, 30, 30),{220,40},{100/2,100/2},1);
                    vectorEnemigos.push_back(enemigo);
                    Enemigo *enemigo1 = new Enemigo(textenemigonivel1,sf::IntRect(290, 0, 30, 30),{720,240},{100/2,100/2},1);
                    vectorEnemigos.push_back(enemigo1);
                    Enemigo *enemigo2 = new Enemigo(textenemigonivel1,sf::IntRect(290, 0, 30, 30),{220,540},{100/2,100/2},1);
                    vectorEnemigos.push_back(enemigo2);
                    Enemigo *enemigo3 = new Enemigo(textenemigonivel1,sf::IntRect(290, 0, 30, 30),{720,550},{100/2,100/2},1);
                    vectorEnemigos.push_back(enemigo3);
                    Enemigo *enemigo4 = new Enemigo(textenemigonivel1,sf::IntRect(290, 0, 30, 30),{420,550},{100/2,100/2},1);
                    vectorEnemigos.push_back(enemigo4);
                    Enemigo *enemigo5 = new Enemigo(textenemigonivel1,sf::IntRect(290, 0, 30, 30),{420,50},{100/2,100/2},1);
                    vectorEnemigos.push_back(enemigo5);
                    enemigo_creado = true;
                 }
            }
        }
        if(getEstadoActual() == EstadoPartida::NIVEL1){
            if(vectorEnemigos.size() == 0){
                enemigo_creado = false;
                level1.stop();
                if(portal == nullptr){
                     portal =  new Portal(textportal,{1000,280});
                 }
                 if(coli->ColisionPersonajePortal(personaje,portal)){
                     delete portal;
                    portal = NULL;
                       std::cout << "PASO A NIVEL RECOMPENSAS" << std::endl;
                     portalsound.play();
                     if(ulti){
                         hud->reiniciarExp(hudT2);
                         ulti = false;
                     }
                     portalsound.play();
                     level1.play();
                    setEstado(EstadoPartida::NIVELRECOMPENSAS);
                    personaje->nuevaX(100);
                 }
                // level1.stop();
                // winnersound.play();
                // ganado = true;
                // estadoP = Partida::getInstancia();
                // juego->CambiarEstado(estadoP);
            }
        }
        if(getEstadoActual() == EstadoPartida::NIVELRECOMPENSAS){
            //Colisiones pocimas y escopeta
            //booleano que indique has cogido algo
            //si has recogido algo ya crear el portal y comprobar si colisiona con portal
            if(vectorpocimas.size() != 0){
                int pos = coli->ColisionPersonajePocima(personaje,vectorpocimas);
                if(pos != -1){
                    masV.play();
                    hud->AumentarVida(hudT0);
                    vectorpocimas.erase(vectorpocimas.begin() + pos);
                    recompensa_recogida = true;
                }
            }
            if(recompensa_recogida){
                if(portal == nullptr){
                    cout << "PORTAL NUEVO" << endl;
                    portal =  new Portal(textportal,{1000,280});
                }
                if(coli->ColisionPersonajePortal(personaje,portal)){
                    delete mapa;
                    mapa = NULL;
                    mapa = new Mapa("resources/infierno2.tmx");
                    level1.stop();
                    std::cout << "PASO A NIVEL FINAL" << std::endl;
                    portalsound.play();
                    finalS.play();
                    delete portal;
                    portal = NULL;
                    setEstado(EstadoPartida::BOSSFINAL);
                    personaje->nuevaX(100);
                    Enemigo *enemigo5 = new Enemigo(boss,sf::IntRect(290, 0, 30, 30),{500,200},{100/2,100/2},2);
                    vectorEnemigos.push_back(enemigo5);
                    enemigo_creado = true;
                }
            }
        }
        if(getEstadoActual() == EstadoPartida::BOSSFINAL){
                delete portal;
                portal = NULL;
            //poner una condicion que compruebe esto
            if(enemigo_creado){
                if(vectorEnemigos[0]->getVidaEnemigo() % 100 == 0 && vectorEnemigos[0]->getVidaEnemigo() != vidaanterior){
                    if(!ulti){

                        hud->AumentarExp(hudT2);
                    }
                    vidaanterior = vectorEnemigos[0]->getVidaEnemigo();
                }
                if(vectorEnemigos.size() == 0){
                    enemigo_creado = false;
                    
                    //  sf::Sprite *bebe = new sf::Sprite();
                    //  bebe->setTexture(textbebe);
                    //  bebe->setTextureRect();
                    //  bebe->setPosition(1000,550);
                    //  bebe->setScale(0.05,0.05);
                }
            }
            if(coli->ColisionBebe(personaje, vectorbebe) && vectorEnemigos.size() == 0){
                    level1.stop();
                    finalS.stop();
                    winnersound.play();
                    ganado = true;
                    estadoP = Partida::getInstancia();
                    juego->CambiarEstado(estadoP);
                    instance = NULL;
            }
        }
        coli->ColisionPersonajeParedes(personaje,mapa->getObstacles());
        if(enemigo_creado){
            for(int i = 0; i < vectorEnemigos.size();i++) {
                if(getEstadoActual() == EstadoPartida::NIVEL0){
                    //CAMBIAR A 0 
                    // juego->motor->MoverEnemigo(vectorEnemigos[i],personaje->getPosicionActual(),tiempotranscurrido,personaje,0);
                    juego->motor->MoverEnemigo(vectorEnemigos[i],personaje->getPosicionActual(),tiempotranscurrido,personaje,0);
                }else if(getEstadoActual() == EstadoPartida::NIVEL1){
                    juego->motor->MoverEnemigo(vectorEnemigos[i],personaje->getPosicionActual(),tiempotranscurrido,personaje,1);
                }
                else {
                    juego->motor->MoverEnemigo(vectorEnemigos[i],personaje->getPosicionActual(),tiempotranscurrido,personaje,2);
                }
                coli->ColisionEnemigoParedes(vectorEnemigos[i],mapa->getObstacles());
                coli->ColisionesPersonajes(personaje,vectorEnemigos[i],mapa->getObstacles(),hud);
            }
        }
        if(hud->getBarraColor().getTextureRect().width == 272){
             std::cout << "ACTIVAR ULTI" << std::endl; 
            ultisound.play();
            ulti = true;
        }
        if(hud->getBarraColor().getTextureRect().width == 0){
            ulti = false;
        }
        if(ulti){
            //crear funcion quitarvida
            hud->quitarExp(hudT2);
        }
        // std::cout << hud->getLongCora() << std::endl;
        
        if(hud->getLongCora() == 0){
            std::cout << "PERDIDO" << std::endl;
            level1.stop();
            gameover.play();
            ganado = false;
            estadoP = Partida::getInstancia();
            juego->CambiarEstado(estadoP);
            instance = nullptr;
        }
        this->time0 += UPDATE_TICK_TIME;
        numLoops++;
        time1 = clock.getElapsedTime().asMilliseconds();
        deltaTime = time1 - this->time0;
        if(portal){
            portal->AumentarFrame();
        }
    }
    if(deltaTime > UPDATE_TICK_TIME){
        this->time0 = time1 - UPDATE_TICK_TIME;
    }
    PercenTick = min(1.f,float(clock.getElapsedTime().asMilliseconds()) / UPDATE_TICK_TIME);
    juego->motor->InterpolarJugador(PercenTick,personaje);
     if((getEstadoActual() == EstadoPartida::NIVEL0 || getEstadoActual() == EstadoPartida::NIVEL1) && enemigo_creado){
         for(int i = 0; i < vectorEnemigos.size();i++) {
             //std::cout << i << std::endl;
             juego->motor->InterpolarEnemigo(PercenTick,vectorEnemigos[i]);
         }
     }
    //  std::cout << getEstadoActual() << std::endl;
}
void Jugando::Render(MotorGrafico *motor){
    motor->getWindow()->clear();
   motor->DrawMapa(motor->getWindow(),mapa->getNumCapas(),mapa->getMap_Width(),mapa->getMap_Height(),mapa->getObstacles(),mapa->getMapa(),mapa->getVectorImagen(),mapa->getRuta());
    if(getEstadoActual() == EstadoPartida::BOSSFINAL){
        motor->DrawBaby(motor->getWindow(),vectorbebe);
    }
    motor->DrawPersonaje(motor->getWindow(), personaje);
    motor->DrawHUD(motor->getWindow(),hud,ulti);
    motor->DrawBalas(motor->getWindow(),balas);
    if((getEstadoActual() == EstadoPartida::NIVEL0 || getEstadoActual() == EstadoPartida::NIVEL1 || getEstadoActual() == EstadoPartida::BOSSFINAL)  && enemigo_creado){
        motor->DrawEnemigo(motor->getWindow(),vectorEnemigos);
    }
    if((getEstadoActual() == EstadoPartida::RESPAWN || getEstadoActual() == EstadoPartida::NIVEL0 || getEstadoActual() == EstadoPartida::NIVEL1 ||
    getEstadoActual() == EstadoPartida::NIVELRECOMPENSAS)  && portal){
        motor->DrawPortal(motor->getWindow(),portal);
    }
    if(getEstadoActual() == EstadoPartida::NIVELRECOMPENSAS){
        motor->DrawPocimas(motor->getWindow(),vectorpocimas);
    }
    motor->getWindow()->display();
}