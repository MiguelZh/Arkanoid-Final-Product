#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "checkML.h"

using namespace std;
class Texture
{
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	int w = 0;
	int h = 0;
	int fw = 0; // Frame width
	int fh = 0; // Frame height
	int numCols = 1;
	int numRows = 1;
public:
	Texture(SDL_Renderer* r) : renderer(r) {};
	Texture(SDL_Renderer* r, string filename, int numRows = 1, int numCols = 1) : renderer(r) { load(filename, numRows, numCols); };
	~Texture();
	void clear();

	int getW() const { return w; };
	int getH() const { return h; };
	int getNumCols() const { return numCols; };
	int getNumRows() const { return numRows; };
	SDL_Texture* getTexture() const { return texture; };

	void load(string filename, int numRows = 1, int numCols = 1);
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

