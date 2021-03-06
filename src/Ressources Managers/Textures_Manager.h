#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <string>

class img_struct {
public:
	img_struct(SDL_Texture* t, SDL_Surface* s, std::string n) : texture(t), surface(s), name(n) {}
	void destroy_img_struct() {
		if (texture)
			SDL_DestroyTexture(texture);
		if (surface)
			SDL_FreeSurface(surface);
	}

	SDL_Texture* texture;
	SDL_Surface* surface;
	std::string name;
};

namespace Textures_Manager {
	void init();	//Loads all the images
	void quit();
	void printFrame(); //blits according to the matrix, the textures and the grid

	SDL_Texture* findTexture(std::string name);
	SDL_Surface* findSurface(std::string name);
	int findIndex(std::string name);

	extern bool showInvisibleEnts;
	extern bool showGrid;
	extern std::vector<img_struct> imgList;
};
