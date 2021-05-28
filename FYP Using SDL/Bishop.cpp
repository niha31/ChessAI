#include "Bishop.h"
Bishop::Bishop(COLOUR colour, SDL_Point mapPos, Texture* texture)
{
	this->type = PIECETYPE::BISHOP;
	this->colour = colour;
	this->mapPos = mapPos;
	this->texture = texture;
	this->isAlive = true;
}
