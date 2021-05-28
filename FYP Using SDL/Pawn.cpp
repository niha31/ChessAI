#include "Pawn.h"

Pawn::Pawn(COLOUR colour, SDL_Point mapPos, Texture* texture)
{
	this->type = PIECETYPE::PAWN;
	this->colour = colour;
	this->mapPos = mapPos;
	this->texture = texture;
	this->selected = false;
}
