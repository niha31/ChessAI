#include "Piece.h"
Piece::Piece()
{
}

Piece::~Piece()
{
}

void Piece::Render()
{
	texture->Render(GetWorldPos());
}

SDL_Point Piece::GetMapPos()
{
	return mapPos;
}

SDL_Point Piece::GetWorldPos()
{
	return { mapPos.x * scaledTileSize, mapPos.y * scaledTileSize };
}

void Piece::SetPos(int x, int y)
{
	mapPos.x = x;
	mapPos.y = y;
}

PIECETYPE Piece::GetType()
{
	return type;
}

bool Piece::GetSelected()
{
	return selected;
}

void Piece::SetSelected(bool value)
{
	selected = value;
}

COLOUR Piece::GetColour()
{
	return colour;
}

bool Piece::GetIsAlive()
{
	return isAlive;
}

void Piece::SetIsAlive(bool value)
{
	isAlive = value;
}

