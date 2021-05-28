#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include "ChessBoard.h"
#include "Commons.h"



class MovementGenerator
{
private:
	vector<Move> moves;
	vector<Move> movesForCounterCheck;
	vector<Move> allPossibleMoves;
	
	            // north, south, west, east, NW, SE, NE, SW
	int DirectionOffsetsX[8] = { 0, 0, -1, 1, -1, 1, 1, -1};
	int DirectionOffsetsY[8] = { -1, 1, 0, 0, -1, 1, -1, 1 };

	int allKnightMovementX[8] = {-2, -1, 1, 2, 2, 1,-1,-2};
	int allKnightMovementY[8] = {-1, -2,-2,-1, 1, 2, 2, 1};

	int NumSquaresToEdge[8][8][8];
public:
	MovementGenerator();
	~MovementGenerator();

	void CalculateMoveData();

	vector<Move>* GenerateAllMoves(vector<Piece>& piecesCopy, ChessBoard& boardCopy);
	vector<Move>* GenerateMovesForPiece(Piece& pieceCopy, ChessBoard& boardCopy);
	void GenerateSlidingMoves(Piece& pieceCopy, ChessBoard& boardCopy);
	void GeneratePawnMoves(Piece& pieceCopy, ChessBoard& boardCopy);
	void GenerateKnightMoves(Piece& pieceCopy, ChessBoard& boardCopy);
	void GenerateKingMoves(Piece& pieceCopy, ChessBoard& boardCopy);

	bool IsInCheck(Piece& kingPieceCopy, vector<Piece>& piecesCopy, ChessBoard& boardCopy);
	bool IsInCheck(int kingXpos, int kingYpos, vector<Piece>& piecesCopy, ChessBoard& boardCopy);
	vector<Move>* GetCounterCheckMoves(vector<Piece>& enemyPiecesCopy, Piece& chosenPieceCopy, int kingXpos, int kingYpos, ChessBoard& boardCopy);

	vector<Move>* GetOrderedMoves();
};

