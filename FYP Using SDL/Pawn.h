#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:

public:
	Pawn(COLOUR colour, SDL_Point mapPos, Texture* texture);
};

