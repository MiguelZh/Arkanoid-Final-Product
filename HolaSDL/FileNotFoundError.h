#pragma once
#include "ArkanoidError.h"
#include <SDL.h>

class FileNotFoundError : public ArkanoidError {
public:
	FileNotFoundError(string s) : ArkanoidError(s) {}
};