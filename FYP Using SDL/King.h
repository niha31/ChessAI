#pragma once
#include "Piece.h"
class King : public Piece
{
private:
	bool inCheck = false;
public:
	King(COLOUR colour, SDL_Point mapPos, Texture* texture);
	~King();

	 void SetCheck(bool value);
	 bool GetCheck();
};

