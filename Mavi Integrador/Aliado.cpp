#include "Aliado.h"

using namespace sf;

Aliado::Aliado(sf::Texture& tex_aliado, float scale) {
    spriteAliado.setTexture(tex_aliado);
    spriteAliado.setScale(0.15f, 0.15f);
    
    tiempoVida = Clock();
    vivo = true;
}

void Aliado::SetPosicion(const sf::Vector2f& posicion) {
    spriteAliado.setPosition(posicion);
}

void Aliado::Dibujar(sf::RenderWindow& window) {
    // Dibuja sprite 
    window.draw(spriteAliado);  
}

void Aliado::update() {
    if (vivo && tiempoVida.getElapsedTime().asSeconds() > 0.8f) {
        vivo = false;
    }
}

void Aliado::verificarLimitesVentana(sf::RenderWindow& ventana) {
    sf::Vector2f posicion = spriteAliado.getPosition();


    if (posicion.x < 0) {
        posicion.x = 0;
    }
    else if (posicion.x > ventana.getSize().x) {
        posicion.x = ventana.getSize().x;
    }

    if (posicion.y < 0) {
        posicion.y = 0;
    }
    else if (posicion.y > ventana.getSize().y) {
        posicion.y = ventana.getSize().y;
    }

    spriteAliado.setPosition(posicion);
}

bool Aliado::estaVivo() const {
    return vivo;
}

sf::Sprite& Aliado::getSpriteAliado() {
    return spriteAliado;
}
void Aliado::desaparecer() {
   
    spriteAliado.setPosition(-1000, -1000);  
}

