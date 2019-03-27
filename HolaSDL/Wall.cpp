#include "Wall.h"


Wall::Wall(uint ancho, uint alto, Vector2D coord, Texture * textura, string pos):
	ArkanoidObject(ancho, alto, coord, textura), wallPosition(pos)
{

}

bool Wall::collides(const SDL_Rect destRect, Vector2D & collVector)
{
	if (SDL_HasIntersection(&destRect, &getRect())) {
		if (wallPosition == "Right") {
			collVector = Vector2D(-1, 0);
		}
		if (wallPosition == "Left") {
			collVector = Vector2D(1, 0);
		}
		if (wallPosition == "Top") {
			collVector = Vector2D(0, 1);
		}
		return true;
	}
	return false;
}

Wall::~Wall()
{
}
