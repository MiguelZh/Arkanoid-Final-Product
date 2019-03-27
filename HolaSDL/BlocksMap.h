#pragma once
#include "ArkanoidObject.h"
#include "Block.h"
class PlayState;
class BlocksMap : public ArkanoidObject
{
private:
	Block *** blocks = nullptr;
	uint numBloques,
		puntos = 0,
		puntosAnt = 0;
	int fila = 0,
		columna = 0;
public:
	BlocksMap(uint w, uint h, Texture * t);
	virtual ~BlocksMap();
	void render();

	Block* collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D& collVector);
	bool detectCollision(const SDL_Rect destRect, Vector2D &collVector, const Vector2D &vel, PlayState * p);
	Block* blockAt(const Vector2D& p);
	void LeerFichero(string filename, bool load);
	void ballHitBlock(Block * bloque);
};

