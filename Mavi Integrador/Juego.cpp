#include "Juego.h"

#include <cstdlib>
#include <ctime>
#include "Enemigo.h"
#include "Aliado.h"
#include "Crosshair.h"
#include <iostream>
#include "stdafx.h"


Juego::Juego() : window(sf::VideoMode(1280, 720), "Dragon shoot Z") {

    

    Fuente.loadFromFile("arial.ttf");

    texto_vidas.setFont(Fuente);
    texto_vidas.setCharacterSize(60);
    texto_vidas.setPosition(300, 630);

    texto_puntaje.setFont(Fuente);
    texto_puntaje.setCharacterSize(60);
    texto_puntaje.setPosition(700, 630);

    tex_stage.loadFromFile("stage.png");
    stage.setTexture(tex_stage);

    sf::Vector2u dimensionesStage = tex_stage.getSize();
    float escalaXstage = 1280.0f / dimensionesStage.x;
    float escalaYstage = 600.0f / dimensionesStage.y;
    stage.setScale(escalaXstage, escalaYstage);

    tex_casa.loadFromFile("casa.png");
    casa.setTexture(tex_casa);
    casa.setPosition(106, -10);

    sf::Vector2u dimensionesCasa = tex_casa.getSize();
    float escalaXcasa = 1000.0f / dimensionesCasa.x;
    float escalaYcasa = 570.0f / dimensionesCasa.y;
    casa.setScale(escalaXcasa, escalaYcasa);



    tex_imagenInicial.loadFromFile("background.png");

    sprite_imagenInicial.setTexture(tex_imagenInicial);
    

    sf::Vector2u dimensionesImagenInicial = tex_imagenInicial.getSize();
    float escalaXimagenInicial = 1280.0f / dimensionesImagenInicial.x;
    float escalaYimagenInicial = 720.0f / dimensionesImagenInicial.y;
    sprite_imagenInicial.setScale(escalaXimagenInicial, escalaYimagenInicial);
   
         
    
   
    
    _enemigo.loadFromFile("freezer.png");
    _aliado.loadFromFile("Krillin.png");

    relojCreacionEntidades.restart();
    crearEnemigoEnLugarDeAliado = true;

        
    juegoTerminado = false;
    juegoGanado = false;
    juegoIniciado = false;

    vidas = 7;
    puntos = 0;
    

    InicializarJuego();


   
}


void Juego::Loop() {

    


    while (window.isOpen()) {
            procesarEventos();
            actualizar();
            Dibujar();
        }
    

    }

void Juego::InicializarJuego() {
    
    if (!tex_enemigo.loadFromFile("freezer.png")) {
        std::cerr << "error al cargar textura" << std::endl;
        
    }

    Enemigo primerEnemigo(tex_enemigo, 0.4f);
    primerEnemigo.SetPosicion(ObtenerPosicionAleatoria());
    enemigos.push_back(primerEnemigo);


}

void Juego::disparar(std::vector<Enemigo>& enemigos, std::vector<Aliado>& aliados) {
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    float mouseX = static_cast<float>(mousePosition.x);
    float mouseY = static_cast<float>(mousePosition.y);
    
    


    for (Enemigo& enemigo : enemigos) {
        if (enemigo.estaVivo() && enemigo.getSprite().getGlobalBounds().contains(mouseX, mouseY)) {
            
            puntos ++;
            
            enemigo.desaparecer(); 
            return;  
        }
    }

    
    for (Aliado& aliado : aliados) {
        if (aliado.estaVivo() && aliado.getSpriteAliado().getGlobalBounds().contains(mouseX, mouseY)) {
            puntos--;
            vidas--;
            aliado.desaparecer();  
            return;  
        }
    }
}
       
       
    
void Juego::procesarEventos() {
    sf::Event evt;
    while (window.pollEvent(evt)) {
        // eventos ventana principal
        if (evt.type == sf::Event::Closed) {
            window.close();
        }
        else if (evt.type == sf::Event::MouseMoved) {
            player.Posicionar(evt.mouseMove.x, evt.mouseMove.y);
        }
        else if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
            
            disparar(enemigos, aliados);
        }
    }
}

    void Juego::crearEnemigo() {

        if (juegoTerminado) {
            // no crear más enemigos
            return;
        }

        if (relojCreacionEnemigo.getElapsedTime() >= sf::seconds(0.02f)) {
            Enemigo enemigo(tex_enemigo, 0.4f);
            enemigo.SetPosicion(ObtenerPosicionAleatoria());
            enemigos.push_back(enemigo);
            relojCreacionEnemigo.restart();
        }
    }

    void Juego::crearAliado() {
        if (juegoTerminado) {
            
            return;
        }
        if (relojCreacionAliado.getElapsedTime() >= sf::seconds(1.0f)) {
            Aliado aliado(_aliado, 0.4f);
            aliado.SetPosicion(ObtenerPosicionAleatoria());
            aliados.push_back(aliado);
            relojCreacionAliado.restart();
        }
    }

    
    void Juego::actualizar() {
        for (Enemigo& enemigo : enemigos) {
            if (enemigo.estaVivo()) {
                enemigo.update();
            }
        }

        for (Aliado& aliado : aliados) {
            if (aliado.estaVivo()) {
                aliado.update();
            }
        }
        
        if (relojCreacionEntidades.getElapsedTime() >= sf::seconds(1.0f)) {
            if (crearEnemigoEnLugarDeAliado) {
                crearEnemigo();
            }
            else {
                crearAliado();
            }

            crearEnemigoEnLugarDeAliado = !crearEnemigoEnLugarDeAliado; 
            relojCreacionEntidades.restart();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            disparar(enemigos, aliados);
        }
        if (juegoTerminado) {
            
            window.clear();
            window.draw(sprite_gameOver);
            window.display();

            
            if (relojGameOver.getElapsedTime().asSeconds() >= 3.0f) {
                window.close();
            }

            return;
        }

        if (vidas <= 0) {
            
            juegoTerminado = true;

            
            if (!tex_gameOver.loadFromFile("gameOver.png")) {
                std::cerr << "Error al cargar la textura de Game Over." << std::endl;
                
            }

            sprite_gameOver.setTexture(tex_gameOver);
                                   
                       
            relojGameOver.restart();
        }

        if (juegoGanado) {

            window.clear();
            window.draw(sprite_victoria);
            window.display();


            if (relojVictoria.getElapsedTime().asSeconds() >= 3.0f) {
                window.close();
            }

            return;
        }


        if (puntos >= 10) {
            
            juegoGanado = true;

            
            if (!tex_victoria.loadFromFile("ganaste.png")) {
                std::cerr << "Error al cargar la textura de Victoria." << std::endl;
            }

            sprite_victoria.setTexture(tex_victoria);

            
            relojVictoria.restart();
        }
        
        
      
    }

void Juego::Dibujar() {

    if (!juegoIniciado) {
        window.clear();
        window.draw(sprite_imagenInicial);
        window.display();

        
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            else if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                juegoIniciado = true;
            }
        }

        return;
    }



    if (juegoTerminado) {
        
        return;
    }

    if (juegoGanado) {

        return;
    }

    texto_vidas.setString("Vidas: " + std::to_string(vidas));
      

    texto_puntaje.setString("Puntaje: " + std::to_string(puntos));
    


    window.clear();
    window.draw(stage);
    
    for (Enemigo& enemigo : enemigos) {
        if (enemigo.estaVivo()) {
            enemigo.Dibujar(window);  
        }
    }

    for (Aliado& aliado : aliados) {
        if (aliado.estaVivo()) {
            aliado.Dibujar(window);  
        }
    }
    
    
    window.draw(casa);

    window.draw(texto_vidas);
    window.draw(texto_puntaje);
    player.Dibujar(window);

    window.display();


    
}

sf::Vector2f Juego::ObtenerPosicionAleatoria() {

    int indice = rand() % 7;
    return posiciones[indice];
}


