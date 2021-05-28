#include "Queen.h"

Queen::Queen(COLOUR colour, SDL_Point mapPos, Texture* texture)
{
	this->type = PIECETYPE::QUEEN;
	this->colour = colour;
	this->mapPos = mapPos;
	this->texture = texture;
	this->isAlive = true;
}

Queen::~Queen()
{

}
