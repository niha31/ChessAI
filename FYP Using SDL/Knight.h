#pragma once
#include "Piece.h"
class Knight : public Piece
{
private:

public:
	Knight(COLOUR colour, SDL_Point mapPos, Texture* texture);
	~Knight();
};

