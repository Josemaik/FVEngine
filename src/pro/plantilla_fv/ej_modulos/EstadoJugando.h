#pragma once
#include <iostream>
#include "SFML/Audio.hpp"
#include "State.h"
#include "Personaje.h"
#include "HUD.h"
#include "Mapa.h"
#include "Bala.h"
#include "Enemigo.h"
#include "Colisiones.h"
#include "Portal.h"
#include "EstadoWinLose.h"
class Partida;
class Jugando: public State {
    
    public:
        Jugando(float width, float height);
        ~Jugando();
        static Jugando* getInstancia();
        void HandleInput(Juego *juego);
        void Update(Juego *juego);
        void Render(MotorGrafico *motor);
        bool getGanado();
    private:
        enum EstadoPartida{
            RESPAWN,NIVEL0,NIVEL1,NIVELRECOMPENSAS,BOSSFINAL
        };
        bool ganado;
        EstadoPartida actual;
        void setEstado(EstadoPartida estado);
        EstadoPartida getEstadoActual() const{return actual;}
        sf::Clock clock;
        float time0, tickTime;
        int maxLoops;
        float PercenTick;
        bool evento = false;
        sf::Texture text,textenemigonivel1, boss;
        sf::Texture textportal;
        sf::Texture textUlti;
        Personaje *personaje;
        // Enemigo *enemigo;
        std::vector<Enemigo*> vectorEnemigos;
        std::vector<sf::Sprite*> vectorpocimas,vectorbebe;
        Colisiones *coli;
        static Jugando *instance;
        int vidaanterior;
        sf::Font hudT4;
        sf::Texture hudT0, hudT1, hudT2, hudT3, hudT5, hudT6,texBala,texlaser,textpocima,textbebe;
        std::vector<Bala*> balas;
        Partida *estadoP;
        HUD *hud; 
        Mapa *mapa;   
        Bala *bala;
        Portal *portal;
         sf::Time tiempo_aparicion; 
         bool enemigo_creado,recompensa_recogida; 
         bool ulti;
        sf::SoundBuffer disparoBuffer;
        sf::Sound disparoSound;
        sf::SoundBuffer inicioBuffer;
        sf::Sound inicio;
        sf::SoundBuffer portalBuffer;
        sf::Sound portalsound;
        sf::SoundBuffer level1Buffer;
        sf::Sound level1;
        sf::SoundBuffer disparonormalBuffer;
        sf::Sound disparonormal;
        sf::SoundBuffer ultiBuffer;
        sf::Sound ultisound;
        sf::SoundBuffer winnerBuffer;
        sf::Sound winnersound;
        sf::SoundBuffer gameoverBuffer;
        sf::Sound gameover;
        sf::SoundBuffer rugidoBuffer;
        sf::Sound rugido;
        sf::SoundBuffer bebeBuffer;
        sf::Sound bebeS;
        sf::SoundBuffer finalBuffer;
        sf::Sound finalS;
        sf::SoundBuffer masVBuffer;
        sf::Sound masV;
};
