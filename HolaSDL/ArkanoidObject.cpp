#include "ArkanoidObject.h"



ArkanoidObject::ArkanoidObject()
{

}


ArkanoidObject::~ArkanoidObject()
{
	texture = nullptr;
}

void ArkanoidObject::render()
{
	SDL_Rect destRect = getRect();
	texture->render(destRect, SDL_FLIP_NONE);
}

void ArkanoidObject::renderFrame(uint row, uint col)
{
	SDL_Rect destRect = getRect();
	texture->renderFrame(destRect, row, col);
}

void ArkanoidObject::update()
{

}

bool ArkanoidObject::handleEvent(SDL_Event & e)
{
	return false;
}

SDL_Rect ArkanoidObject::getRect()
{
	SDL_Rect destRect;
	destRect.x = coord.getX();
	destRect.y = coord.getY();
	destRect.h = h;
	destRect.w = w;
	return destRect;
}

void ArkanoidObject::loadFromFile(ifstream & file)
{
	int x, y, width, height;
	file >> x >> y >> width >> height;
	coord = Vector2D(x, y);
	w = width;
	h = height;
}

void ArkanoidObject::saveToFile(ofstream & file)
{
	file << (int)coord.getX() << " ";
	file << (int)coord.getY() << " ";
	file << (int)w << " ";
	file << (int)h << endl;
}

uint ArkanoidObject::getW()
{
	return w;
}

uint ArkanoidObject::getH()
{
	return h;
}

uint ArkanoidObject::getX()
{
	return coord.getX();
}

uint ArkanoidObject::getY()
{
	return coord.getY();
}
