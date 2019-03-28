#pragma once

#include "ArkanoidError.h"
#include <SDL.h>

class FileFormatError : public ArkanoidError {
public:
	FileFormatError(string s) : ArkanoidError("Error" + s) {}
};