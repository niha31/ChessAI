#include "Evaluation.h"

Evaluation::Evaluation()
{
}

Evaluation::~Evaluation()
{

}

int Evaluation::Evaluate(ChessBoard& boardCopy)
{
	int whiteEvaluation = CountValues(COLOUR::WHITE, boardCopy);
	int blackEvaluation = CountValues(COLOUR::BLACK, boardCopy);

	int evaluation = whiteEvaluation - blackEvaluation;

	
	return evaluation;
}

int Evaluation::CountValues(COLOUR colour, ChessBoard& boardCopy)
{
	int value = 0;

	value += boardCopy.GetPiecesOfType(PIECETYPE::PAWN, colour).size() * pawnValue;
	value += boardCopy.GetPiecesOfType(PIECETYPE::KNIGHT, colour).size() * knightValue;
	value += boardCopy.GetPiecesOfType(PIECETYPE::BISHOP, colour).size() * bishopValue;
	value += boardCopy.GetPiecesOfType(PIECETYPE::ROOK, colour).size() * rookValue;

	if (boardCopy.GetPieceOfType(PIECETYPE::QUEEN, colour) != NULL)
	{
		value += queenValue;

	}

	return value;
}

