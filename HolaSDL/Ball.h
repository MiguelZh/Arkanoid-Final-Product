#pragma once
#include "MovingObject.h"

class PlayState;
class Ball : public MovingObject
{
private:
	PlayState * playstate_ = nullptr;
	Vector2D iniCoord;
	Vector2D iniVel;
public:
	Ball();
	Ball(uint ancho, uint alto, Vector2D coord, Texture * textura, Vector2D vel, PlayState * p);
	virtual ~Ball();
	void update();
};

