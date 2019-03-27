#pragma once
#include"GameObject.h"
#include "Texture.h"
#include "Vector2D.h"
#include <iostream>
#include <fstream>
class ArkanoidObject : public GameObject
{
protected:
	Vector2D coord;
	Texture * texture = nullptr;
	uint w = 0, h = 0;
public:
	ArkanoidObject();
	ArkanoidObject(uint width, uint height, Vector2D coord, Texture * t) :
		w(width), h(height), coord(coord), texture(t) {}
	virtual ~ArkanoidObject();

	virtual void render();
	virtual void renderFrame(uint row, uint col);
	virtual void update();
	virtual bool handleEvent(SDL_Event& e);
	SDL_Rect getRect();		

	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream & file);
	uint getW();
	uint getH();
	uint getX();
	uint getY();
};

