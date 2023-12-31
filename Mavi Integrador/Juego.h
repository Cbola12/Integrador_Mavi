

#include <cstdlib>
#include <ctime>
#include "Enemigo.h"
#include "Aliado.h"
#include "Crosshair.h"

#include <iostream>
#include "stdafx.h"
class Juego
{
public:

     Juego();
    void Loop();

    void disparar(std::vector<Enemigo>& enemigos, std::vector<Aliado>& aliados);



private:

    std::vector<Enemigo> enemigos;
    std::vector<Aliado> aliados;

    sf::Clock relojCreacionEntidades;
    bool crearEnemigoEnLugarDeAliado;

    sf::Texture tex_imagenInicial;
    sf::Sprite sprite_imagenInicial;
    float escalaXimagenInicial;
    float escalaYimagenInicial;


    int vidas;
    int puntos;
    
    sf::RenderWindow window;
    sf::Texture tex_enemigo;
    sf::Texture _enemigo;
    sf::Texture _aliado;
    sf::Vector2f ObtenerPosicionAleatoria();

    sf::Vector2f posiciones[7] = {
      sf::Vector2f(30.0f, 450.0f), //izquierda
      sf::Vector2f(360.0f, 380.0f), //ventana grande
      sf::Vector2f(1000.0f, 50.0f), //derecha arriba
      sf::Vector2f(340.0f, 200.0f), //balcon
      sf::Vector2f(1100.0f, 450.0f),//derecha abajo
      sf::Vector2f(635.0f, 370.0f),//ventana frente
      sf::Vector2f(780.0f, 390.0f) //puerta

    };

    sf::Clock relojCreacionEnemigo;
   sf::Clock relojCreacionAliado;


    sf::Font Fuente;

 
    sf::Texture tex_stage;
    sf::Sprite stage;
    float escalaXstage;
    float escalaYstage;

    sf::Texture tex_casa;
    sf::Sprite casa;
    float escalaXcasa;
    float escalaYcasa;

    sf::Text texto_vidas;    
    sf::Text texto_puntaje;
    
    sf::Texture tex_gameOver;
    sf::Sprite sprite_gameOver;
    sf::Texture tex_victoria;
    sf::Sprite sprite_victoria;
    bool juegoIniciado;
    bool juegoTerminado = false;
    bool juegoGanado = false;
    sf::Clock relojGameOver;
    sf::Clock relojVictoria;

    crosshair player;
    

    void Dibujar();
    void InicializarJuego();
    void procesarEventos();
    void actualizar();
    
    void crearAliado();
    void crearEnemigo();
   

};