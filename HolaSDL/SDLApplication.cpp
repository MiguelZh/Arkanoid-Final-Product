#include "SDLApplication.h"



SDLApplication::SDLApplication()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw new SDLError("Error initializing SDL");
	// INITIALIZE SDL
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("ArkanoidLastVersion", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// TEXTURES
	textures[blocksText] = new Texture(renderer);
	textures[blocksText]->load(textureNames[blocksText], 2, 3);
	textures[rewardText] = new Texture(renderer);
	textures[rewardText]->load(textureNames[rewardText], 10, 8);
	for (int i = 2; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer);
		textures[i]->load(textureNames[i]);
	}

	// STATE MACHINE
	stateMachine = new GameStateMachine();
	stateMachine->pushState(new MainMenuState(this));
}


SDLApplication::~SDLApplication()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	delete stateMachine;
	stateMachine = nullptr;

	for (int i = 0; i < NUM_TEXTURES; i++) {
		delete textures[i];
	}
	SDL_Quit();
}

void SDLApplication::run()
{
	while (!exit) {
		handleEvents();
		update();
		render();
		destroy();
	}
}
void SDLApplication::render() {
	if (window == nullptr || renderer == nullptr)
		throw new SDLError("Error loading the SDL window and/or renderer");
	else {
		SDL_RenderClear(renderer);
		//llamo al render de la maquina de estado, render currentState
		stateMachine->getCurrentState()->render();
		SDL_RenderPresent(renderer);
	}
}

void SDLApplication::update()
{
	stateMachine->getCurrentState()->update();
	// controlar el framerate
	int startTime = SDL_GetTicks();
	int frameTime = SDL_GetTicks() - startTime;
	if (frameTime < FRAME_RATE) {
		SDL_Delay(FRAME_RATE - frameTime);
	}
}

void SDLApplication::destroy()
{
	stateMachine->getCurrentState()->destroy();
}

void SDLApplication::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		else {
			stateMachine->getCurrentState()->handleEvents(event);
		}
	}
}
Texture * SDLApplication::getTexture(int num) {
	return textures[num];
}
GameStateMachine * SDLApplication::getStateMachine() {
	return stateMachine;
}

void SDLApplication::setExit(bool set)
{
	exit = set;
}
