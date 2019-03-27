#pragma once
#include "MovingObject.h"
#include "Ball.h"
class PlayState;
class Reward : public MovingObject
{
protected:
	uint rewardType;
	int animationFrame = 0;
	int lastAnimationTime;
	float velocidadAnim = 100;
	Ball* ball_ = nullptr;
	PlayState* playState_ = nullptr;
public:
	Reward(uint width, uint height, Vector2D coord, Texture * t, Vector2D vel, uint type, PlayState *p);
	virtual ~Reward();
	void render();
	void tipoRecompensa();
};

