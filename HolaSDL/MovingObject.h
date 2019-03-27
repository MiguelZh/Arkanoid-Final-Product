#pragma once
#include "ArkanoidObject.h"
class MovingObject : public ArkanoidObject
{
protected: 
	Vector2D velocidad;
public:
	MovingObject();
	MovingObject(uint width, uint height, Vector2D coord, Texture * t, Vector2D vel);
	virtual ~MovingObject();

	// guardan y cargan velocidad
	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file); 
};

