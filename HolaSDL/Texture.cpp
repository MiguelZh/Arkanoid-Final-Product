#include "Texture.h"



Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = fw = fh = 0;
}

void Texture::clear()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = fw = fh = 0;
}

// Carga la textura desde el archivo de la imagen
void Texture::load(string filename, int nRows, int nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw "Error loading surface from " + filename;
	clear();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw "Error loading texture from " + filename;
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

// Renderiza la textura completa
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

// Renderiza una parte de la textura
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}