#include "ChessBoard.h"

ChessBoard::ChessBoard(SDL_Renderer* gRenderer)
{

	LoadImages(gRenderer);

	PrepareChessBoard();

	SetPiecesAtStart();
}

ChessBoard::~ChessBoard()
{
	whitePieces.clear();
	blackPieces.clear();
}

void ChessBoard::DeleteTexture()
{
	delete mWhiteTile;
	delete mBlackTile;
	delete mWhiteTileSelected;
	delete mBlackTileSelected;

	delete mBlackPawnTexture;
	delete mWhitePawnTexture;

	delete mBlackBishopTexture;
	delete mWhiteBishopTexture;

	delete mBlackRookTexture;
	delete mWhiteRookTexture;

	delete mBlackKnightTexture;
	delete mWhiteKnightTexture;

	delete mBlackKingTexture;
	delete mWhiteKingTexture;

	delete mBlackQueenTexture;
	delete mWhiteQueenTexture;

}

void ChessBoard::PrepareChessBoard()
{
	for (int y = 0; y < 8; y++)
	{
		//y starts with white square
		for (int x = 0; x < 8; x++)
		{
			bool isBlack = true;
			if (x % 2 == 0)
			{
				if (y % 2 == 0)
				{
					isBlack = false;
				}
			}
			else
			{
				if (y % 2 == 1)
				{
					isBlack = false;
				}
			}

			map[x][y].mapPos = { x, y };

			if (isBlack)
			{
				//square will be Black
				map[x][y].colour = COLOUR::BLACK;
				map[x][y].defaultTexture = mBlackTile;
				map[x][y].highlightTexture = mBlackTileSelected;
			}
			else
			{
				//square will be White
				map[x][y].colour = COLOUR::WHITE;
				map[x][y].defaultTexture = mWhiteTile;
				map[x][y].highlightTexture = mWhiteTileSelected;
			}
		}
	}
}

void ChessBoard::RenderChessBoard()
{
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			SDL_Point tileWorldPos = map[i][j].GetWorldPos();
			if (map[i][j].selected == false)
			{
				map[i][j].defaultTexture->Render(tileWorldPos);
			}
			else
			{
				map[i][j].highlightTexture->Render(tileWorldPos);
			}
		}
	}
}

void ChessBoard::SetPiecesAtStart()
{
	whitePieces.clear();
	blackPieces.clear();

	// Black Pawns
	for (int i = 0; i < 8; i++)
	{
		blackPieces.push_back(Pawn(COLOUR::BLACK, { i, 1 }, mBlackPawnTexture));
	}

	// White Pawns
	for (int i = 0; i < 8; i++)
	{
		whitePieces.push_back(Pawn(COLOUR::WHITE, { i, 6 }, mWhitePawnTexture));
	}

	// Black Bishops
	blackPieces.push_back(Bishop(COLOUR::BLACK, { 2, 0 }, mBlackBishopTexture));
	blackPieces.push_back(Bishop(COLOUR::BLACK, { 5, 0 }, mBlackBishopTexture));

	// White Bishop
	whitePieces.push_back(Bishop(COLOUR::WHITE, { 2, 7 }, mWhiteBishopTexture));
	whitePieces.push_back(Bishop(COLOUR::WHITE, { 5, 7 }, mWhiteBishopTexture));

	// Black Knight
	blackPieces.push_back(Knight(COLOUR::BLACK, { 1, 0 }, mBlackKnightTexture));
	blackPieces.push_back(Knight(COLOUR::BLACK, { 6, 0 }, mBlackKnightTexture));

	// White Knight
	whitePieces.push_back(Knight(COLOUR::WHITE, { 1, 7 }, mWhiteKnightTexture));
	whitePieces.push_back(Knight(COLOUR::WHITE, { 6, 7 }, mWhiteKnightTexture));

	// Black Rook
	blackPieces.push_back(Rook(COLOUR::BLACK, { 0, 0 }, mBlackRookTexture));
	blackPieces.push_back(Rook(COLOUR::BLACK, { 7, 0 }, mBlackRookTexture));

	// White Rook
	whitePieces.push_back(Rook(COLOUR::WHITE, { 0, 7 }, mWhiteRookTexture));
	whitePieces.push_back(Rook(COLOUR::WHITE, { 7, 7 }, mWhiteRookTexture));

	// Black Queen
	blackPieces.push_back(Queen(COLOUR::BLACK, { 3, 0 }, mBlackQueenTexture));

	// White Queen
	whitePieces.push_back(Queen(COLOUR::WHITE, { 3, 7 }, mWhiteQueenTexture));

	// Black King
	blackPieces.push_back(King(COLOUR::BLACK, { 4, 0 }, mBlackKingTexture));

	// White King
	whitePieces.push_back(King(COLOUR::WHITE, { 4, 7 }, mWhiteKingTexture));
}

void ChessBoard::RenderPieces()
{
	for (int i = 0; i < whitePieces.size(); i++)
	{
		whitePieces.at(i).Render();	
	}

	for (int i = 0; i < blackPieces.size(); i++)
	{	
		blackPieces.at(i).Render();
	}
}

void ChessBoard::RemoveKilledPieces()
{
	for (int i = 0; i < whitePieces.size(); i++)
	{
		if (!whitePieces.at(i).GetIsAlive())
		{
			whitePieces.erase(whitePieces.begin() + i);
		}
	}

	for (int i = 0; i < blackPieces.size(); i++)
	{
		if (!blackPieces.at(i).GetIsAlive())
		{
			blackPieces.erase(blackPieces.begin() + i);
		}
	}
}

Piece* ChessBoard::GetPieceAt(int i, COLOUR colour)
{
	if (colour == COLOUR::WHITE)
	{
		return &(whitePieces.at(i));
	}
	else
	{
		return &(blackPieces.at(i));
	}
}

Piece* ChessBoard::GetPieceAtPos(int x, int y)
{
	if (x < 0 || y < 0 || x > 7 || y > 7)
	{
		return nullptr;
	}

	for (size_t i = 0; i < whitePieces.size(); i ++)
	{
		if (whitePieces.at(i).GetMapPos().x == x && whitePieces.at(i).GetMapPos().y == y)
		{
			return &(whitePieces.at(i));
		}
	}
	
	for (size_t i = 0; i < blackPieces.size(); i++)
	{
		if (blackPieces.at(i).GetMapPos().x == x && blackPieces.at(i).GetMapPos().y == y)
		{
			return &(blackPieces.at(i));
		}
	}
	return nullptr; 
}

int ChessBoard::GetIdxOfPieceAt(int x, int y, COLOUR colour)
{
	if (x < 0 || y < 0 || x > 8 || y > 8)
	{
		return -1;
	}

	if (colour == COLOUR::BLACK)
	{
		for (int i = 0; i < blackPieces.size(); i++)
		{
			if (blackPieces.at(i).GetMapPos().x == x && blackPieces.at(i).GetMapPos().y == y)
			{
				return i;
			}
		}
	}
	else if (colour == COLOUR::WHITE)
	{
		for (int i = 0; i < whitePieces.size(); i++)
		{
			if (whitePieces.at(i).GetMapPos().x == x && whitePieces.at(i).GetMapPos().y == y)
			{
				return i;
			}
		}
	}
}

Piece* ChessBoard::GetPieceAt(int x, int y, COLOUR colour /* = INVALID */)
{
	if (x < 0 || y < 0 || x > 8 || y > 8)
	{
		return nullptr;
	}

	// If invalid or black
	if (colour != COLOUR::WHITE)
	{
		for (Piece& blackPiece : blackPieces)
		{
			if (blackPiece.GetMapPos().x == x && blackPiece.GetMapPos().y == y)
			{
				return &blackPiece;
			}
		}
	}

	// If invalid or white
	if (colour != COLOUR::BLACK)
	{
		for (Piece& whitePiece : whitePieces)
		{
			if (whitePiece.GetMapPos().x == x && whitePiece.GetMapPos().y == y)
			{
				return &whitePiece;
			}
		}
	}

	return nullptr;
}

Piece* ChessBoard::GetPieceOfType(PIECETYPE type, COLOUR colour /* = INVALID */)
{
	if (colour == COLOUR::BLACK)
	{
		for (int i = 0; i < blackPieces.size(); i++)
		{
			if (blackPieces.at(i).GetType() == type)
			{
				return &blackPieces.at(i);
			}
		}
	}
	else if (colour == COLOUR::WHITE)
	{
		for (int i = 0; i < whitePieces.size(); i++)
		{
			if (whitePieces.at(i).GetType() == type)
			{
				return &whitePieces.at(i);
			}
		}
	}

	
}

vector<Piece> ChessBoard::GetPiecesOfType(PIECETYPE type, COLOUR colour /* = INVALID */)
{
	vector<Piece> pieces;
	if (colour == COLOUR::BLACK)
	{
		for (int i = 0; i < blackPieces.size(); i++)
		{
			if (blackPieces.at(i).GetType() == type)
			{
				pieces.push_back(blackPieces.at(i));
			}
		}
	}
	else if (colour == COLOUR::WHITE)
	{
		for (int i = 0; i < whitePieces.size(); i++)
		{
			if (whitePieces.at(i).GetType() == type)
			{
				pieces.push_back(whitePieces.at(i));
			}
		}
	}

	return pieces;
}

vector<Piece>* ChessBoard::GetPiecesOfColour(COLOUR colour /* = INVALID */)
{
	if (colour == COLOUR::WHITE)
	{
		return &whitePieces;
	}
	else
	{
		return &blackPieces;
	}
}

bool ChessBoard::IsColourInCheck(COLOUR colour)
{
	if (colour == COLOUR::WHITE)
	{
		return whiteCheck;
	}
	else
	{
		return blackCheck;
	}
}

void ChessBoard::SetCheck(COLOUR colour, bool value)
{
	if (colour == COLOUR::WHITE)
	{
		whiteCheck = value;
	}
	else
	{
		blackCheck = value;
	}
}

void ChessBoard::LoadImages(SDL_Renderer* gRenderer)
{
	mWhiteTile = new Texture(gRenderer);
	mWhiteTile->LoadTexture("images/ChessBoardLightTile.png");

	mBlackTile = new Texture(gRenderer);
	mBlackTile->LoadTexture("images/ChessBoardDarkTile.png");

	mWhiteTileSelected = new Texture(gRenderer);
	mWhiteTileSelected->LoadTexture("images/HighlightedLightTile.png");

	mBlackTileSelected = new Texture(gRenderer);
	mBlackTileSelected->LoadTexture("images/HighlightedDarkTile.png");

	mBlackPawnTexture = new Texture(gRenderer);
	mBlackPawnTexture->LoadTexture("images/BlackPawn.png");

	mWhitePawnTexture = new Texture(gRenderer);
	mWhitePawnTexture->LoadTexture("images/WhitePawn.png");

	mBlackBishopTexture = new Texture(gRenderer);
	mBlackBishopTexture->LoadTexture("images/BlackBishop.png");

	mWhiteBishopTexture = new Texture(gRenderer);
	mWhiteBishopTexture->LoadTexture("images/WhiteBishop.png");

	mBlackKnightTexture = new Texture(gRenderer);
	mBlackKnightTexture->LoadTexture("images/BlackKnight.png");

	mWhiteKnightTexture = new Texture(gRenderer);
	mWhiteKnightTexture->LoadTexture("images/WhiteKnight.png");

	mBlackRookTexture = new Texture(gRenderer);
	mBlackRookTexture->LoadTexture("images/BlackRook.png");

	mWhiteRookTexture = new Texture(gRenderer);
	mWhiteRookTexture->LoadTexture("images/WhiteRook.png");

	mBlackQueenTexture = new Texture(gRenderer);
	mBlackQueenTexture->LoadTexture("images/BlackQueen.png");

	mWhiteQueenTexture = new Texture(gRenderer);
	mWhiteQueenTexture->LoadTexture("images/WhiteQueen.png");

	mBlackKingTexture = new Texture(gRenderer);
	mBlackKingTexture->LoadTexture("images/BlackKing.png");

	mWhiteKingTexture = new Texture(gRenderer);
	mWhiteKingTexture->LoadTexture("images/WhiteKing.png");

}

Tile* ChessBoard::GetTile(int x, int y)
{
	return &map[x][y];
}

void ChessBoard::MakeMove(Move move)
{
	Piece* piece = GetPieceAtPos(move.startSquareX, move.startSquareY);

	piece->SetPos(move.targetSquareX, move.targetSquareY);
}

void ChessBoard::UndoMove(Move move)
{
	Piece* piece = GetPieceAtPos(move.targetSquareX, move.targetSquareY);

	piece->SetPos(move.startSquareX, move.startSquareY);
}
