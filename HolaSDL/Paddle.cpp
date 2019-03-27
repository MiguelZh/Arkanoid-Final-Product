#include "Paddle.h"
#include "SDLApplication.h"


Paddle::Paddle()
{
}

Paddle::Paddle(int ancho, int alto, Vector2D coord, Texture * textura, Vector2D vel):
	MovingObject(ancho, alto, coord, textura, vel)
{
	anchoIni = ancho;
}


Paddle::~Paddle()
{
}

bool Paddle::handleEvent(SDL_Event & e)
{
	bool handled = false;
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			paddleSpeed = -3;
			handled = true;
			break;
		case SDLK_RIGHT:
			paddleSpeed = 3;
			handled = true;
			break;
		}
	}

	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			paddleSpeed = 0;
			handled = true;
			break;
		case SDLK_RIGHT:
			paddleSpeed = 0;
			handled = true;
			break;
		}
	}
	return handled;
}

void Paddle::update()
{
	if (coord.getX() > 25 - paddleSpeed && coord.getX() < WIN_WIDTH - w - paddleSpeed - 25) {	// ELIMINAR VALORES ESTATICOS
		coord = {coord.getX() + paddleSpeed, coord.getY()};
	}
}

bool Paddle::collides(const SDL_Rect destRect, Vector2D &collVector) {
	if (SDL_HasIntersection(&destRect, &getRect())) {
		collVector = ballhitPaddle(&destRect);
		return true;
	}
	else return false;
}

Vector2D Paddle::ballhitPaddle(const SDL_Rect * ballrect) {
	Vector2D vectorCol;
	uint BallCenter = ballrect->x + (ballrect->w / 2);
	uint parte = getW() / 6; // paddle dividido en 6 trozos
	if (BallCenter > coord.getX() && BallCenter < coord.getX() + parte) { // 1/6 del paddle izquierda
		vectorCol = Vector2D(4, 10);
	}
	if (BallCenter > coord.getX() + parte && BallCenter < coord.getX() + parte * 2) {
		vectorCol = Vector2D(2, 10);
	}
	if (BallCenter > coord.getX() + parte * 2 && BallCenter < coord.getX() + parte * 4) { // el doble porque cuenta la 
		vectorCol = Vector2D(0, 10);													   //mitad izq y derecha del paddle
	}
	if (BallCenter > coord.getX() + parte * 4 && BallCenter < coord.getX() + parte * 5) { // 5/6 derecha
		vectorCol = Vector2D(-2, 10);
	}
	if (BallCenter > coord.getX() + parte * 5 && BallCenter < coord.getX() + getW()) {
		vectorCol = Vector2D(-4, 10);
	}
	vectorCol.normalize();
	return vectorCol;
}

void Paddle::resetWidth()
{
	w = anchoIni;
}

void Paddle::setWidth(uint ancho)
{
	w = ancho;
}

