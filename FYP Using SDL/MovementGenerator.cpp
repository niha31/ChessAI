#include "MovementGenerator.h"
MovementGenerator::MovementGenerator()
{
}

MovementGenerator::~MovementGenerator()
{
}

void MovementGenerator::CalculateMoveData()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int north = j;
			int south = 7 - j;
			int west = i;
			int east = 7 - i;

			NumSquaresToEdge[i][j][0] = north;
			NumSquaresToEdge[i][j][1] = south;
			NumSquaresToEdge[i][j][2] = west;
			NumSquaresToEdge[i][j][3] = east;
			NumSquaresToEdge[i][j][4] = min(north, west);
			NumSquaresToEdge[i][j][5] = min(south, east);
			NumSquaresToEdge[i][j][6] = min(north, east);
			NumSquaresToEdge[i][j][7] = min(south, west);
		}
	}
}

vector<Move>* MovementGenerator::GenerateAllMoves(vector<Piece>& piecesCopy, ChessBoard& boardCopy)
{
	allPossibleMoves.clear();

	if (boardCopy.IsColourInCheck(COLOUR::BLACK))
	{
		for (int i = 0; i < piecesCopy.size(); i++)
		{
			SDL_Point kingPos = boardCopy.GetPieceOfType(PIECETYPE::KING, piecesCopy.at(i).GetColour())->GetMapPos();
			vector<Piece> enemyPiecesCopy = *boardCopy.GetPiecesOfColour(InvertColour(piecesCopy.at(i).GetColour()));
			GetCounterCheckMoves(enemyPiecesCopy, (piecesCopy.at(i)), kingPos.y, kingPos.y, boardCopy);

			for (int i = 0; i < movesForCounterCheck.size(); i++)
			{
				allPossibleMoves.push_back(movesForCounterCheck.at(i));
			}
		}	
	}
	else
	{
		for (int i = 0; i < piecesCopy.size(); i++)
		{
			GenerateMovesForPiece(piecesCopy.at(i), boardCopy);
			
			for (int i = 0; i < moves.size(); i++)
			{
				allPossibleMoves.push_back(moves.at(i));
			}
		}
	}

	return &allPossibleMoves;
}



vector<Move>* MovementGenerator::GenerateMovesForPiece(Piece& pieceCopy, ChessBoard& boardCopy)
{
	if (moves.size() > 0)
	{
		moves.clear();
	}

	if (pieceCopy.GetType() == PIECETYPE::BISHOP || pieceCopy.GetType() == PIECETYPE::ROOK || pieceCopy.GetType() == PIECETYPE::QUEEN)
	{
		GenerateSlidingMoves(pieceCopy, boardCopy);
	}
	else if (pieceCopy.GetType() == PIECETYPE::PAWN)
	{
		GeneratePawnMoves(pieceCopy, boardCopy);
	}
	else if(pieceCopy.GetType() == PIECETYPE::KNIGHT)
	{
		GenerateKnightMoves(pieceCopy, boardCopy);
	}
	else if (pieceCopy.GetType() == PIECETYPE::KING)
	{
		GenerateKingMoves(pieceCopy, boardCopy);
	}

	return &moves;
}

void MovementGenerator::GenerateSlidingMoves(Piece& pieceCopy, ChessBoard& boardCopy)
{
	int tileX = pieceCopy.GetMapPos().x;
	int tileY = pieceCopy.GetMapPos().y;

	int startDirection = 0;
	if (pieceCopy.GetType() == PIECETYPE::BISHOP)
	{
		startDirection = 4;
	}
	else
	{
		startDirection = 0;
	}

	int endDirection = 0;
	if (pieceCopy.GetType() == PIECETYPE::ROOK)
	{
		endDirection = 4;
	}
	else
	{
		endDirection = 8;
	}

	for (int direction = startDirection; direction < endDirection; direction++)
	{
		for (int i = 0; i < NumSquaresToEdge[tileX][tileY][direction]; i++)
		{
			int targetSquareX = tileX + DirectionOffsetsX[direction] * (i + 1);
			int targetSquareY = tileY + DirectionOffsetsY[direction] * (i + 1);
			Piece* pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);

			//blocked by friendly
			if (pieceOnTargetSquare != nullptr)
			{
				if (pieceOnTargetSquare->GetColour() == pieceCopy.GetColour())
				{
					break;
				}
				if (pieceOnTargetSquare->GetColour() != pieceCopy.GetColour())
				{
					Move newMove = Move(tileX, tileY, targetSquareX, targetSquareY, GetPieceValue(pieceOnTargetSquare->GetType()));
					moves.push_back(newMove);

					//cant move any further in direction after capture
					break;
				}
			}

			Move newMove = Move(tileX, tileY, targetSquareX, targetSquareY, 0);
			moves.push_back(newMove);
		}
	}
}

void MovementGenerator::GeneratePawnMoves(Piece& pieceCopy, ChessBoard& boardCopy)
{
	int tileX = pieceCopy.GetMapPos().x;
	int tileY = pieceCopy.GetMapPos().y;

	int moveDirection;
	Move newMove;

	if (pieceCopy.GetColour() == COLOUR::WHITE)
	{
		moveDirection = 0;
	}
	else
	{
		moveDirection = 1;
	}

	int targetSquareX = tileX + DirectionOffsetsX[moveDirection];
	int targetSquareY = tileY + DirectionOffsetsY[moveDirection];
	Piece* pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);

	//is there piece infront of pawn
	if (pieceOnTargetSquare == nullptr)
	{
		if (targetSquareX < 8 && targetSquareX >= 0 && targetSquareY < 8 && targetSquareY >= 0)
		{
			newMove = Move(tileX, tileY, targetSquareX, targetSquareY, 0);
			moves.push_back(newMove);
		}
	}

	bool canMove2squares = false;
	//can piece move 2 squares
	if (pieceCopy.GetColour() == COLOUR::WHITE && tileY == 6)
	{
		targetSquareX = targetSquareX + DirectionOffsetsX[moveDirection];
		targetSquareY = targetSquareY + DirectionOffsetsY[moveDirection];
		pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);
		canMove2squares = true;
	}
	else if (pieceCopy.GetColour() == COLOUR::BLACK && tileY == 1)
	{
		targetSquareX = targetSquareX + DirectionOffsetsX[moveDirection];
		targetSquareY = targetSquareY + DirectionOffsetsY[moveDirection];
		pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);
		canMove2squares = true;
	}

	//is there piece infront of pawn
	if(canMove2squares && pieceOnTargetSquare == nullptr)
	{
		newMove = Move(tileX, tileY, targetSquareX, targetSquareY, 0);
		moves.push_back(newMove);
	}	

	//can piece attack
	if (pieceCopy.GetColour() == COLOUR::WHITE)
	{
		//is there piece on north west tile
		targetSquareX = tileX + DirectionOffsetsX[4];
		targetSquareY = tileY + DirectionOffsetsY[4];
		pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);
		if (pieceOnTargetSquare != nullptr && pieceOnTargetSquare->GetColour() != pieceCopy.GetColour() && targetSquareX < 8 && targetSquareX >= 0 && targetSquareY < 8 && targetSquareY >=0 )
		{
			newMove = Move(tileX, tileY, targetSquareX, targetSquareY, GetPieceValue(pieceOnTargetSquare->GetType()));
			moves.push_back(newMove);
		}
		//is there pice on north east tile
		targetSquareX = tileX + DirectionOffsetsX[6];
		targetSquareY = tileY + DirectionOffsetsY[6];
		pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);
		if (pieceOnTargetSquare != nullptr && pieceOnTargetSquare->GetColour() != pieceCopy.GetColour() && targetSquareX < 8 && targetSquareX >= 0 && targetSquareY < 8 && targetSquareY >= 0)
		{
			newMove = Move(tileX, tileY, targetSquareX, targetSquareY, GetPieceValue(pieceOnTargetSquare->GetType()));
			moves.push_back(newMove);
		}
	}

	if (pieceCopy.GetColour() == COLOUR::BLACK)
	{
		//is there piece on south west tile
		targetSquareX = tileX + DirectionOffsetsX[5];
		targetSquareY = tileY + DirectionOffsetsY[5];
		pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);
		if (pieceOnTargetSquare != nullptr && pieceOnTargetSquare->GetColour() != pieceCopy.GetColour() && targetSquareX < 8 && targetSquareX >= 0 && targetSquareY < 8 && targetSquareY >= 0)
		{
			Move newMove = Move(tileX, tileY, targetSquareX, targetSquareY, GetPieceValue(pieceOnTargetSquare->GetType()));
			moves.push_back(newMove);
		}
		//is there pice on south east tile
		targetSquareX = tileX + DirectionOffsetsX[7];
		targetSquareY = tileY + DirectionOffsetsY[7];
		pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);
		if (pieceOnTargetSquare != nullptr && pieceOnTargetSquare->GetColour() != pieceCopy.GetColour() && targetSquareX < 8 && targetSquareX >= 0 && targetSquareY < 8 && targetSquareY >= 0)
		{
			newMove = Move(tileX, tileY, targetSquareX, targetSquareY, GetPieceValue(pieceOnTargetSquare->GetType()));
			moves.push_back(newMove);
		}
	}
}

void MovementGenerator::GenerateKnightMoves(Piece& pieceCopy, ChessBoard& boardCopy)
{
	int tileX = pieceCopy.GetMapPos().x;
	int tileY = pieceCopy.GetMapPos().y;

	for (int i = 0; i < 8; i++)
	{
		int targetSquareX = tileX + allKnightMovementX[i];
		int targetSquareY = tileY + allKnightMovementY[i];
		Piece* pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);

		if (targetSquareX >= 0 && targetSquareY >= 0 && targetSquareX < 8 && targetSquareY < 8)
		{
			if (pieceOnTargetSquare != nullptr)
			{
				//capture enemy piece
				if (pieceOnTargetSquare->GetColour() != pieceCopy.GetColour())
				{
					Move newMove = Move(tileX, tileY, targetSquareX, targetSquareY, GetPieceValue(pieceOnTargetSquare->GetType()));
					moves.push_back(newMove);
				}
			}
			else
			{
				Move newMove = Move(tileX, tileY, targetSquareX, targetSquareY, 0);
				moves.push_back(newMove);
			}
		}		
	}
}

void MovementGenerator::GenerateKingMoves(Piece& pieceCopy, ChessBoard& boardCopy)
{
	int tileX = pieceCopy.GetMapPos().x;
	int tileY = pieceCopy.GetMapPos().y;

	for (int moveDirection = 0; moveDirection < 8; moveDirection++)
	{
		int targetSquareX = tileX + DirectionOffsetsX[moveDirection];
		int targetSquareY = tileY + DirectionOffsetsY[moveDirection];
		Piece* pieceOnTargetSquare = boardCopy.GetPieceAtPos(targetSquareX, targetSquareY);
		if (targetSquareX >= 0 && targetSquareY >= 0 && targetSquareX < 8 && targetSquareY < 8)
		{
			if (pieceOnTargetSquare != nullptr)
			{
				//capture enemy piece
				if (pieceOnTargetSquare->GetColour() != pieceCopy.GetColour())
				{
					Move newMove = Move(tileX, tileY, targetSquareX, targetSquareY, GetPieceValue(pieceOnTargetSquare->GetType()));
					moves.push_back(newMove);
				}
			}
			else
			{
				Move newMove = Move(tileX, tileY, targetSquareX, targetSquareY, 0);
				moves.push_back(newMove);
			}
		}
	}
}

bool MovementGenerator::IsInCheck(Piece& kingPieceCopy, vector<Piece>& piecesCopy, ChessBoard& boardCopy)
{
	for (int i = 0; i < piecesCopy.size(); i++)
	{
		vector<Move>* newMoves = GenerateMovesForPiece(piecesCopy.at(i), boardCopy);
		
		for (auto newMoves_front = newMoves->begin(); newMoves_front != newMoves->end(); newMoves_front++)
		{
			//check if newMove creates a check
			if (kingPieceCopy.GetMapPos().x == newMoves_front->targetSquareX && kingPieceCopy.GetMapPos().y == newMoves_front->targetSquareY)
			{
				return true;
			}			
		}
	}

	return false;
}

bool MovementGenerator::IsInCheck(int kingXpos, int kingYpos, vector<Piece>& piecesCopy, ChessBoard& boardCopy)
{
	for (int i = 0; i < piecesCopy.size(); i++)
	{
		vector<Move> newMoves = *GenerateMovesForPiece(piecesCopy.at(i), boardCopy);

		for (auto newMoves_front = newMoves.begin(); newMoves_front != newMoves.end(); newMoves_front++)
		{
			//check if newMove creates a check
			if (kingXpos == newMoves_front->targetSquareX && kingYpos == newMoves_front->targetSquareY)
			{
				return true;
			}
		}
	}

	return false;
}

vector<Move>* MovementGenerator::GetCounterCheckMoves(vector<Piece>& enemyPiecesCopy, Piece& chosenPieceCopy, int kingXpos, int kingYpos, ChessBoard& boardCopy)
{
	vector<Move> PieceMovesCopy = *GenerateMovesForPiece(chosenPieceCopy, boardCopy);
	vector<Move> enemyMovesCopy;

	movesForCounterCheck.clear();

	for (int i = 0; i < enemyPiecesCopy.size(); i++)
	{
		enemyMovesCopy = *GenerateMovesForPiece(enemyPiecesCopy.at(i), boardCopy);
		
		vector<Move>::iterator enemnyMovesFrount = enemyMovesCopy.begin();
		//check to see if move does not create a check and remove
		while (enemnyMovesFrount != enemyMovesCopy.end())
		{
			if (kingXpos == enemnyMovesFrount->targetSquareX && kingYpos == enemnyMovesFrount->targetSquareY)
			{
				//will get list of chech moves
				enemnyMovesFrount = enemyMovesCopy.erase(enemnyMovesFrount);
			}
			else
			{
				enemnyMovesFrount++;
			}
		}
		
		enemnyMovesFrount = enemyMovesCopy.begin();
		while (enemnyMovesFrount != enemyMovesCopy.end())
		{
			vector<Move>::iterator PieceMovesFrount = PieceMovesCopy.begin();
			while (PieceMovesFrount != PieceMovesCopy.end())
			{
				if (enemnyMovesFrount->targetSquareX == PieceMovesFrount->targetSquareX && enemnyMovesFrount->targetSquareY == PieceMovesFrount->targetSquareY)
				{
					movesForCounterCheck.push_back(*PieceMovesFrount);
				}

				PieceMovesFrount++;
			}
			enemnyMovesFrount++;
		}

	}

	return &movesForCounterCheck;
}

vector<Move>* MovementGenerator::GetOrderedMoves()
{
	 sort(moves.begin(), moves.end(), greater<Move>());

	 return &moves;
}


