#pragma once
#include "Piece.h"
class Queen : public Piece
{
private:

public:
	Queen(COLOUR colour, SDL_Point mapPos, Texture* texture);
	~Queen();
};

