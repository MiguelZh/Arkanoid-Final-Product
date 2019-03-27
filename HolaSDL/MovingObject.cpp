#include "MovingObject.h"



MovingObject::MovingObject()
{
}

MovingObject::MovingObject(uint width, uint height, Vector2D coord, Texture * t, Vector2D vel):
	ArkanoidObject(width, height, coord, t), velocidad(vel)
{
}


MovingObject::~MovingObject()
{
}

void MovingObject::loadFromFile(ifstream& file) {
	int vx, vy;
	file >> vx >> vy;
	velocidad = Vector2D(vx, vy);
	ArkanoidObject::loadFromFile(file);
}

void MovingObject::saveToFile(ofstream& file) {
	file << (int)velocidad.getX() << " ";
	file << (int)velocidad.getY() << " ";
	ArkanoidObject::saveToFile(file);
}