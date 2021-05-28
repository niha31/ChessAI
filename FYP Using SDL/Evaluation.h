#pragma once
#include "Commons.h"
#include "ChessBoard.h"

class Evaluation
{
private:

public:
	Evaluation();
	~Evaluation();

	int Evaluate(ChessBoard& boardCopy);
	int CountValues(COLOUR colour, ChessBoard& boardCopy);

};

