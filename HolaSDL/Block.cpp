#include "Block.h"




Block::Block(uint color, uint ancho, uint alto, Vector2D coord, Texture * textura, uint row, uint col) :
	color(color), ArkanoidObject(ancho, alto, coord, textura), row(row), col(col)
{

}

Block::~Block()
{
}

void Block::render()
{
	SDL_Rect destRect;
	destRect.x = coord.getX();
	destRect.y = coord.getY();
	destRect.h = h;
	destRect.w = w;
	uint row, col;
	if (color >= 1 && color <= 3) {
		row = 0;
	}
	else { row = 1; }
	if (color == 1 || color == 4) col = 0;
	else if (color == 2 || color == 5) col = 1;
	else col = 2;

	if (color != 0) {
		if (texture != nullptr) {
			texture->renderFrame(destRect, row, col);
			//renderFrame(row, col); hace lo mismo, no funciona igualmente
		}
	}
}

uint Block::getRow()
{
	return row;
}

uint Block::getCol()
{
	return col;
}

uint Block::getColor()
{
	return color;
}
