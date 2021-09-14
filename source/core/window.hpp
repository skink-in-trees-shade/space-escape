#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <SDL.h>

#define WINDOW_TITLE "Space Escape"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class RenderSystem;

class Window final {
	friend class RenderSystem;

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