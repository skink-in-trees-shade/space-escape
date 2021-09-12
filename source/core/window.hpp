#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include <string>
#include <SDL.h>

class RenderSystem;

class Window final {
	friend class RenderSystem;

public:
	Window(const std::string &title, const int width, const int height);
	~Window();
	void poll_events();
	bool is_open();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool open;
};

#endif