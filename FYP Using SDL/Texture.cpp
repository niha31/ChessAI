#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(SDL_Renderer* gRenderer)
{
	this->gRenderer = gRenderer;
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

bool Texture::LoadTexture(string path)
{
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//SDL_SetColorKey(loadedSurface,
		//SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture;
}

void Texture::Render(const SDL_Point& pos)
{
	SDL_Rect renderQuad = { pos.x, pos.y, mWidth / Scale, mHeight / Scale };

	//SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

	SDL_RenderCopy(gRenderer, mTexture, nullptr, &renderQuad);
}

SDL_Texture* Texture::GetTexture()
{
	return mTexture;
}

int Texture::GetHeight()
{
	return mHeight;
}

int Texture::GetWidth()
{
	return mWidth;
}

SDL_Renderer* Texture::getRenderer()
{
	return gRenderer;
}


