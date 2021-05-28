#pragma once
#include "Piece.h"
class Bishop : public Piece
{
private:

public:
	Bishop(COLOUR colour, SDL_Point mapPos, Texture* texture);
};

