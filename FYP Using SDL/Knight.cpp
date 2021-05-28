#include "Knight.h"

Knight::Knight(COLOUR colour, SDL_Point mapPos, Texture* texture)
{
	this->type = PIECETYPE::KNIGHT;
	this->colour = colour;
	this->mapPos = mapPos;
	this->texture = texture;
	this->isAlive = true;
}

Knight::~Knight()
{

}
