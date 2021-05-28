#pragma once
#include "Commons.h"
#include "Texture.h"

class Piece
{
public:

protected:
	PIECETYPE type = PIECETYPE::EMPTY;
	COLOUR colour;
	SDL_Point mapPos;
	bool isAlive = true;
	bool selected = false;

	Texture* texture;

public:
	Piece();
	virtual ~Piece();

	void Render();

	SDL_Point GetMapPos();
	SDL_Point GetWorldPos();

	void SetPos(int x, int y);

	PIECETYPE GetType();

	bool GetSelected();
	void SetSelected(bool value);

	COLOUR GetColour();

	bool GetIsAlive();
	void SetIsAlive(bool value);
};

