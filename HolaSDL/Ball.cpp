#include "Ball.h"
#include "PlayState.h"


Ball::Ball()
{
}

Ball::Ball(uint ancho, uint alto, Vector2D coord, Texture * textura, Vector2D vel, PlayState * p):
	MovingObject(ancho, alto, coord, textura, vel), playstate_(p)
{
	// valores que usaremos para resetear la bola
	iniCoord = coord;
	iniVel = vel;
}


Ball::~Ball()
{
	playstate_ = nullptr;
}

void Ball::update()
{
	Vector2D prevPos = coord;
	Vector2D collVector;
	SDL_Rect destRect = getRect();
	coord = coord + velocidad;
	if (playstate_->collides(destRect, collVector, velocidad)) { // llama al collides del game

		//velocidad.normalize();

		velocidad = velocidad - (collVector * (2 * (velocidad*collVector)));
		coord = prevPos + velocidad;
	}
	if (coord.getY() > 600 + 100 && playstate_->getVidas()> 0) {	// Cambiar valor inmediato o mover bloque a playState
		coord = iniCoord;
		velocidad = iniVel;
		playstate_->pierdeVida();
	}
}


