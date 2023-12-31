#include "Juego.h"


using namespace sf;


//Entrada//

int main(int argc, char* argv[])
{


	Juego myJuego;
	myJuego.Loop();

	return 0;

}

//Este es el trabajo integrador, no logre que los personajes spawneen de forma aleatoria, sino que se intercalan enemigos y aliados. 
//Tuve que ayudarme con una IA para que los enemigos y aliados spawneen en distintos lugares predeterminados. Tampoco pude corregir que el primer
//enemigo siempre aparezca en el mismo lugar.