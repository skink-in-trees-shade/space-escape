#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <SDL2/SDL.h>

#define WINDOW_TITLE "Space Escape"
#define WINDOW_WIDTH 112
#define WINDOW_HEIGHT 152

class RenderSystem;
class SpawnSystem;

class Window final {
	friend class RenderSystem;
	friend class SpawnSystem;

public:
	Window();
	~Window();
	void poll_events();
	bool is_open();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool open;
};

#endif