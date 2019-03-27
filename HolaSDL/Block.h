#pragma once
#include "ArkanoidObject.h"
class Block : public ArkanoidObject
{
private:
	uint row,
		col;
	uint color;
public:
	Block(uint color, uint ancho, uint alto, Vector2D coord, Texture * textura, uint row, uint col);
	virtual ~Block();
	void render();

	uint getRow();
	uint getCol();
	uint getColor();
};

