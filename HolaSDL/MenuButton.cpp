#include "MenuButton.h"



MenuButton::MenuButton(int X, int Y, int W, int H, Texture* t, SDLApplication* a, void(*callback)(SDLApplication* app))
	: texture(t), x(X), y(Y), w(W), h(H), app(a), cb(callback) 
{
}


MenuButton::~MenuButton()
{
	cb = nullptr;
	app = nullptr;
	texture = nullptr;
}

void MenuButton::render() {
	SDL_Rect destrect;
	destrect.x = x;
	destrect.y = y;
	destrect.w = w;
	destrect.h = h;
	texture->render(destrect, SDL_FLIP_NONE);
}

bool MenuButton::handleEvent(SDL_Event& e) {
	bool handled = false;
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { e.button.x, e.button.y };
		SDL_Rect r = { x, y, w, h };
		if (SDL_PointInRect(&p, &r)) {
			cb(app);
			handled = true;
		}
	}
	return handled;
}