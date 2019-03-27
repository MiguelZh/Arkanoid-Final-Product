#pragma once
#include "MovingObject.h"
#include "Paddle.h"
class PlayState;
class Reward : public MovingObject
{
protected:
	uint rewardType;
	int animationFrame = 0;
	int lastAnimationTime;
	float velocidadAnim = 100;
	PlayState* playState_ = nullptr;
	Paddle* paddle_ = nullptr;
public:
	Reward(uint width, uint height, Vector2D coord, Texture * t, Vector2D vel, uint type, PlayState *p, Paddle * paddle);
	virtual ~Reward();
	void render();
	void update();
	void tipoRecompensa();
};

