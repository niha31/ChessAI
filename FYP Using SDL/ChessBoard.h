#pragma once
#include "Commons.h"
#include "Texture.h"
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"


class ChessBoard
{
public:
	ChessBoard(SDL_Renderer* gRenderer);
	~ChessBoard();
	void DeleteTexture();

	void PrepareChessBoard();
	void RenderChessBoard();
	void SetPiecesAtStart();
	void LoadImages(SDL_Renderer* gRenderer);

	void RenderPieces();
	void RemoveKilledPieces();

	Piece* GetPieceAt(int i, COLOUR colour);
	Piece* GetPieceAtPos(int x, int y);

	int GetIdxOfPieceAt(int x, int y, COLOUR colour);
	Piece* GetPieceAt(int x, int y, COLOUR colour = COLOUR::INVALID);
	Piece* GetPieceOfType(PIECETYPE type, COLOUR colour = COLOUR::INVALID);

	vector<Piece> GetPiecesOfType(PIECETYPE type, COLOUR colour = COLOUR::INVALID);
	vector<Piece>* GetPiecesOfColour(COLOUR colour = COLOUR::INVALID);

	bool IsColourInCheck(COLOUR colour);
	void SetCheck(COLOUR colour, bool value);

	void MakeMove(Move move);
	void UndoMove(Move move);

	Tile* GetTile(int x, int y);


private:
	// Tile textures
	Texture* mWhiteTile;
	Texture* mBlackTile;
	Texture* mWhiteTileSelected;
	Texture* mBlackTileSelected;

	// Piece textures
	Texture* mBlackPawnTexture;
	Texture* mWhitePawnTexture;

	Texture* mBlackBishopTexture;
	Texture* mWhiteBishopTexture;

	Texture* mBlackRookTexture;
	Texture* mWhiteRookTexture;

	Texture* mBlackKnightTexture;
	Texture* mWhiteKnightTexture;

	Texture* mBlackKingTexture;
	Texture* mWhiteKingTexture;

	Texture* mBlackQueenTexture;
	Texture* mWhiteQueenTexture;

	Tile map[8][8];

	std::vector<Piece> whitePieces;
	std::vector<Piece> blackPieces;

	bool whiteCheck = false;
	bool blackCheck = false;
};

