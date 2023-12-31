#pragma once
#include <SFML/Graphics.hpp>

class Enemigo {
public:
    // Constructor de la clase
    Enemigo(sf::Texture& tex_enemigo, float scale);
    void update();
    void verificarLimitesVentana(sf::RenderWindow& window);
    bool estaVivo() const;
    void desaparecer();
    void Dibujar(sf::RenderWindow& window);
    sf::Vector2f ObtenerPosicionAleatoria() const;
    void SetPosicion(const sf::Vector2f& posicion);
    sf::Sprite& getSprite();

private:
    sf::Sprite spriteEnemigo;
    
    sf::Texture& tex_enemigo;
    bool vivo;
    
    sf::Clock tiempoVida;
};
