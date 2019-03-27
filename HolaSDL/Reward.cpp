#include "Reward.h"
#include "PlayState.h"
#include "SDLApplication.h"

Reward::Reward(uint width, uint height, Vector2D coord, Texture * t, Vector2D vel, uint type, PlayState * p, Paddle * paddle):
	MovingObject(width,height,coord,t, vel)
{
	rewardType = type;
	playState_ = p;
	paddle_ = paddle;
}

Reward::~Reward()
{
	playState_ = nullptr;
}

void Reward::render()
{
	if (SDL_GetTicks() > lastAnimationTime + velocidadAnim) {
		animationFrame++;
		lastAnimationTime = SDL_GetTicks();
		if (animationFrame == 7) {
			animationFrame = 0;
		}
	}
	renderFrame(rewardType, animationFrame);
}

void Reward::update()
{
	coord = coord + velocidad;
	if (getY() > WIN_HEIGHT + 100 && this != nullptr) {
		playState_->destruyeReward(this);
	}
	else if(getY() < WIN_HEIGHT) {
		if (SDL_HasIntersection(&getRect(), &paddle_->getRect()))
		{
			tipoRecompensa();
			playState_->destruyeReward(this);
		}
	}
}

void Reward::tipoRecompensa()
{
	switch (rewardType)
	{
	case 0: // nuevo nv
		playState_->pasaNivel();
		break;
	case 1: // alargar
		playState_->alargarPaddle();
		break;
	case 3: // acortar
		playState_->acortarPaddle();
		break;
	case 2: // vida++
		playState_->ganaVida();
		break;
	}
}
