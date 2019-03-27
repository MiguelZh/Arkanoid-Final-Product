#pragma once
#include "ArkanoidError.h"

class SDLError : public ArkanoidError {
public:
	SDLError(string s) : ArkanoidError(s) {}
};