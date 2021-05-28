#include "AI.h"
AI::AI(MovementGenerator* moveGenerator)
{
	this->moveGenerator = moveGenerator;
	evaluation = new Evaluation();
}

AI::~AI()
{

}

Move AI::GenerateRandomAIMove(ChessBoard& boardCopy)
{
	vector<Piece>* pieces = boardCopy.GetPiecesOfColour(COLOUR::BLACK);

	vector<Move>* moves = nullptr;

	do
	{
		int random = rand() % pieces->size();
		moves = moveGenerator->GenerateMovesForPiece((pieces->at(random)), boardCopy);
	} while (moves->size() == 0);


	int random = rand() % moves->size();
	
	move = moves->at(random);

	return move;
}

Move AI::GenerateBestMove(ChessBoard& boardCopy)
{
	COLOUR playerColour = COLOUR::BLACK;

	vector<Piece> pieces = *boardCopy.GetPiecesOfColour(playerColour);
	vector<Move> moves = *(moveGenerator->GenerateAllMoves(pieces, boardCopy));
	sort(moves.begin(), moves.end(), greater<Move>());

	int alpha = -INT_MIN;
	int beta = INT_MAX;
	int bestMoveValue = INT_MIN;

	bestFirstMove = Move(0, 0, 0, 0, 0);
	int noOfBranches = 0;

	if (moves.size() == 0)
	{
		return bestFirstMove;
	}

	for (int i = 0; i < moves.size(); i++)
	{
		boardCopy.MakeMove(moves.at(i));
		int value = -Search(currentMaxDepth, InvertColour(playerColour), -beta, -alpha, boardCopy);
		boardCopy.UndoMove(moves.at(i));
		
		if (value > bestMoveValue)
		{
			bestMoveValue = value;
			bestFirstMove = moves.at(i);
		}

		if (bestMoveValue > alpha)
		{
			alpha = bestMoveValue;
		}

		if (alpha >= beta)
		{
			break;
		}
	}

	
	
	return bestFirstMove;
}

int AI::Search(int depth, COLOUR whosTurn, int alpha, int beta, ChessBoard& boardCopy)
{
	int offSet = 0;
	COLOUR colour = whosTurn;

	if (aiColour == whosTurn)
	{
		offSet == 1;
	}
	else
	{
		offSet == -1;
	}

	if (depth == 0)
	{
		return offSet * evaluation->Evaluate(boardCopy);
	}

	int val = INT_MIN;
	
	vector<Move> moves = *(moveGenerator->GenerateAllMoves(*boardCopy.GetPiecesOfColour(whosTurn), boardCopy));

	sort(moves.begin(), moves.end(), greater<Move>());


	for (int i = 0; i < moves.size(); i++)
	{
		boardCopy.MakeMove(moves.at(i));
		int value = -Search(depth - 1, InvertColour(whosTurn), -beta, -alpha, boardCopy);
		boardCopy.UndoMove(moves.at(i));

		val = max(val, value);
		alpha = max(alpha, val);

		if (alpha >= beta)
		{
			break;
		}
	}

	return val;

}

