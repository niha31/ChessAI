#pragma once
#include "Vector.h"
#include <SDL.h>
#include <vector>

static const float Offset = 100.0f;
static const int Scale = 10;
static int TurnNumber = 1;

static const int pawnValue = 1;
static const int knightValue = 3;
static const int bishopValue = 3;
static const int rookValue = 5;
static const int queenValue = 9;
static const int checkValue = 100;

static const int tileTextureSize = 1024;
static const int scaledTileSize = tileTextureSize / Scale;

static int currentMaxDepth = 3;

enum class PIECETYPE
{
	EMPTY,
	PAWN,
	BISHOP,
	KNIGHT,
	ROOK,
	QUEEN,
	KING
};

static int GetPieceValue(PIECETYPE type)
{
	if (type == PIECETYPE::PAWN)
	{
		return 1;
	}
	else if (type == PIECETYPE::KNIGHT || type == PIECETYPE::BISHOP)
	{
		return 3;
	}
	else if (type == PIECETYPE::ROOK)
	{
		return 5;
	}
	else if (type == PIECETYPE::QUEEN)
	{
		return 9;
	}
	else if (type == PIECETYPE::KING)
	{
		return 100;
	}

}

enum class COLOUR
{
	INVALID,
	WHITE,
	BLACK,
};

static COLOUR InvertColour(COLOUR colour)
{
	if (colour == COLOUR::WHITE)
	{
		colour = COLOUR::BLACK;
	}
	else if (colour == COLOUR::BLACK)
	{
		colour = COLOUR::WHITE;
	}

	return colour;
}

class Texture;

struct Tile
{
	Texture* defaultTexture;
	Texture* highlightTexture;

	SDL_Point mapPos;
	COLOUR colour;
	bool selected;

	Tile()
	{
		mapPos.x = 0;
		mapPos.y = 0;
		colour = COLOUR::WHITE;
		selected = false;
	}

	SDL_Point GetWorldPos()
	{
		return { mapPos.x * scaledTileSize, mapPos.y * scaledTileSize };
	}

	SDL_Rect GetWorldRect()
	{
		return { mapPos.x * scaledTileSize, mapPos.y * scaledTileSize, scaledTileSize, scaledTileSize };
	}
};

struct Move
{
	int startSquareX;
	int startSquareY;

	int targetSquareX;
	int targetSquareY;

	int moveValue;

	Move(int startSquareX, int startSquareY, int targetSquareX, int targetSquareY, int moveValue)
	{
		this->startSquareX = startSquareX;
		this->startSquareY = startSquareY;

		this->targetSquareX = targetSquareX;
		this->targetSquareY = targetSquareY;

		this->moveValue = moveValue;
	}

	Move()
	{

	}

	bool operator > (const Move& str) const
	{
		return (moveValue > str.moveValue);
	}
};
