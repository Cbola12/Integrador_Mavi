#pragma once
#include "stdafx.h"
using namespace sf;

class Aliado
{
public:

    Aliado(Texture& tex_aliado, float scale); 

    void update();

    void verificarLimitesVentana(sf::RenderWindow& ventana);

    bool estaVivo() const;

    void Dibujar(sf::RenderWindow& window);
    sf::Vector2f ObtenerPosicionAleatoria() const;
    void SetPosicion(const sf::Vector2f& posicion);
    
    void desaparecer();
    sf::Sprite& getSpriteAliado();

private: 

    sf::Sprite spriteAliado;
    bool vivo;
    sf::Clock tiempoVida;
};

