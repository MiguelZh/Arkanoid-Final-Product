#pragma once
#include "MovingObject.h"
class Paddle : public MovingObject
{
protected:
	int paddleSpeed; int anchoIni;
public:
	Paddle();
	Paddle(int ancho, int alto, Vector2D coord, Texture * textura, Vector2D vel);
	virtual ~Paddle();
	bool handleEvent(SDL_Event& e);
	void update();

	bool collides(const SDL_Rect destRect, Vector2D &collVector);
	Vector2D ballhitPaddle(const SDL_Rect * ballrect);
	void resetWidth();
	void setWidth(uint ancho);
};

