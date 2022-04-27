#include <SDL2/SDL_image.h>
#include "components/color.hpp"
#include "components/message.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/size.hpp"
#include "core/config.hpp"
#include "render.hpp"

RenderSystem::RenderSystem(SDL_Renderer *renderer) : renderer(renderer), font(nullptr) {
}

RenderSystem::~RenderSystem() {
	for (const std::pair<Sprite, SDL_Texture *> &texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	SDL_DestroyTexture(font);
}

void RenderSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	entities.each<Position, Size, Renderable>([this](entityx::Entity entity, Position &position, Size &size, Renderable &renderable) {
		SDL_Texture *texture = get_texture(renderable.sprite);

		entityx::ComponentHandle<Color> colorHandle = entity.component<Color>();
		if (colorHandle) {
			Color *color = colorHandle.get();
			SDL_SetTextureColorMod(texture, color->r, color->g, color->b);
		} else {
			SDL_SetTextureColorMod(texture, 255, 255, 255);
		}

		SDL_Rect rect = SDL_Rect();
		rect.x = position.x - size.w / 2;
		rect.y = position.y - size.h / 2;
		rect.w = size.w;
		rect.h = size.h;
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	});

	entities.each<Position, Message>([this](entityx::Entity entity, Position &position, Message &message) {
		if (font == nullptr) {
			font = IMG_LoadTexture(renderer, "assets/font.png");
		}

		static char font_map[GLYPH_WIDTH][GLYPH_HEIGHT] = {
			{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
			{'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
			{'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
			{'Y', 'Z', '0', '1', '2', '3', '4', '5'},
			{'6', '7', '8', '9', ' '}};
		for (int i = 0; i < message.text.size(); i++) {
			SDL_Rect src = {-1, -1, GLYPH_WIDTH, GLYPH_HEIGHT};
			for (int y = 0; y < GLYPH_HEIGHT && src.y < 0; y++) {
				for (int x = 0; x < GLYPH_WIDTH && src.x < 0; x++) {
					if (font_map[y][x] == message.text[i]) {
						src.x = x * GLYPH_WIDTH;
						src.y = y * GLYPH_HEIGHT;
					}
				}
			}
			if (src.x >= 0 && src.y >= 0) {
				entityx::ComponentHandle<Color> colorHandle = entity.component<Color>();
				if (colorHandle) {
					Color *color = colorHandle.get();
					SDL_SetTextureColorMod(font, color->r, color->g, color->b);
				} else {
					SDL_SetTextureColorMod(font, 255, 255, 255);
				}

				SDL_Rect dst = {position.x + i * GLYPH_WIDTH, position.y, GLYPH_WIDTH, GLYPH_HEIGHT};
				SDL_RenderCopy(renderer, font, &src, &dst);
			}
		}
	});

	SDL_RenderPresent(renderer);
}

SDL_Texture *RenderSystem::get_texture(Sprite sprite) {
	std::map<Sprite, SDL_Texture *>::iterator iterator = textures.find(sprite);
	if (iterator != textures.end()) {
		return iterator->second;
	}
	static std::map<Sprite, const char *> assets = {
		{Sprite::Background, "assets/background.png"},
		{Sprite::Ball, "assets/ball.png"},
		{Sprite::Brick, "assets/brick.png"},
		{Sprite::StrongBrick, "assets/strong_brick.png"},
		{Sprite::Paddle, "assets/paddle.png"},
		{Sprite::WallLeft, "assets/wall_left.png"},
		{Sprite::WallRight, "assets/wall_right.png"},
		{Sprite::WallTop, "assets/wall_top.png"},
		{Sprite::WallBottom, "assets/wall_bottom.png"},
	};
	return textures[sprite] = IMG_LoadTexture(renderer, assets[sprite]);
}