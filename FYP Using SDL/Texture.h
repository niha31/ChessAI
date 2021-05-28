#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "Commons.h"

using namespace std;

class Texture
{
public:

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

	SDL_Renderer* gRenderer;

public:
	Texture();
	Texture(SDL_Renderer* gRenderer);
	~Texture();

	bool LoadTexture(string path);
	void Render(const SDL_Point& pos);

	SDL_Texture* GetTexture();

	int GetHeight();
	int GetWidth();

	SDL_Renderer* getRenderer();
};

