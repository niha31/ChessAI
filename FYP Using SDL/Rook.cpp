#include "Rook.h"

Rook::Rook(COLOUR colour, SDL_Point mapPos, Texture* texture)
{
	this->type = PIECETYPE::ROOK;
	this->colour = colour;
	this->mapPos = mapPos;
	this->texture = texture;
	this->isAlive = true;
}
