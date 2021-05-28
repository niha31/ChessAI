#pragma once
#include "Commons.h"
#include "MovementGenerator.h"
#include "ChessBoard.h"
#include "Evaluation.h"
#include <math.h>

class AI
{
private:
	MovementGenerator* moveGenerator;
	Evaluation* evaluation;

	Move move;

	Move firstMoveRightNow;
	Move bestFirstMove;

	COLOUR aiColour = COLOUR::BLACK;

public:
	

	AI(MovementGenerator* moveGenerator);
	~AI();

	Move GenerateRandomAIMove(ChessBoard& boardCopy);
	Move GenerateBestMove(ChessBoard& boardCopy);

	int Search(int depth, COLOUR whosTurn, int alpha, int beta, ChessBoard& boardCopy);
};

