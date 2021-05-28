#include "King.h"

King::King(COLOUR colour, SDL_Point mapPos, Texture* texture)
{
	this->type = PIECETYPE::KING;
	this->colour = colour;
	this->mapPos = mapPos;
	this->texture = texture;
	this->isAlive = true;
}

King::~King()
{

}

bool King::GetCheck()
{
	return inCheck;
}

void King::SetCheck(bool value)
{
	inCheck = value;
}