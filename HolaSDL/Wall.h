#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"
class Wall : public ArkanoidObject
{
private:
	string wallPosition;
public:
	Wall(uint ancho, uint alto, Vector2D coord, Texture * textura, string pos);
	virtual ~Wall();
	bool collides(const SDL_Rect destRect, Vector2D &collVector);
};

