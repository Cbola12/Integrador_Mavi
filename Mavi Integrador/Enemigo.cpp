#include "Enemigo.h"
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <SFML/System/Clock.hpp>


// Constructor de la clase Enemigo
Enemigo::Enemigo(sf::Texture& texture, float scale)
	: tex_enemigo(texture)
{
	
	// Configurar la textura del enemigo
	spriteEnemigo.setTexture(tex_enemigo);
	spriteEnemigo.setScale(0.2f, 0.2f);
	std::cout << "Enemigo creado con éxito." << std::endl;


	tiempoVida = sf::Clock();
	vivo = true;

}

void Enemigo::SetPosicion(const sf::Vector2f& posicion) {
	spriteEnemigo.setPosition(posicion);
}

void Enemigo::Dibujar(sf::RenderWindow& window) {
	
	window.draw(spriteEnemigo);  
}



void Enemigo::update() {
	if (vivo && tiempoVida.getElapsedTime().asSeconds() > 0.8f) {
		vivo = false;

	}
}

	void Enemigo::verificarLimitesVentana(sf::RenderWindow & window) {
		// Implementación de la función aquí
		sf::Vector2f posicion = spriteEnemigo.getPosition();

		if (posicion.x < 0) {
			posicion.x = 0;
		}
		else if (posicion.x > window.getSize().x) {
			posicion.x = window.getSize().x;
		}

		if (posicion.y < 0) {
			posicion.y = 0;
		}
		else if (posicion.y > window.getSize().y) {
			posicion.y = window.getSize().y;
		}

		spriteEnemigo.setPosition(posicion);
		
	}

bool Enemigo::estaVivo() const {
		return vivo;
	}

sf::Sprite& Enemigo::getSprite() {
	return spriteEnemigo;
}

void Enemigo::desaparecer() {
	
	spriteEnemigo.setPosition(-1000, -1000);  
	
}




