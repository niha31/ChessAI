#include <SDL.h>
#include <iostream>
#include <list>
#include <iterator>
#include "Texture.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "King.h"
#include "MovementGenerator.h"
#include "Commons.h"
#include "AI.h"

using namespace std;

const int SCREEN_WIDTH = 816;
const int SCREEN_HEIGHT = 816;

bool Init();
void Close();

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

ChessBoard* board;
MovementGenerator* movementGenerator;
vector<Move> moves;
AI* computer; 
int turnNumber = 1;


bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create Renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return success;
}

void Close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = nullptr;
	gRenderer = nullptr;

	//delete image;
	delete board;
	delete movementGenerator;
	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		bool quit = false;

		SDL_Event e;

		board = new ChessBoard(gRenderer);
		movementGenerator = new MovementGenerator();
		movementGenerator->CalculateMoveData();
		computer = new AI(movementGenerator);
		
		bool leftMouseButtonDown = false;
		int mouseY, mouseX, clickOffSetX, clickOffSetY;

		bool canSelectTile = true;
		int selectedTileX, selectedTileY;
		int selectedPieceIdx = -1;
		COLOUR whosTurn = COLOUR::WHITE;
		int turnNumber = 1;

		std::cout << "What difficulty would you like to play against (1 -> 3)" << std::endl;

		std::cin >> currentMaxDepth;
		currentMaxDepth = max(1, min(3, currentMaxDepth));

		std::cout << "Difficulty " << currentMaxDepth << " selected" << std::endl;

		//game loop
		while (!quit)
		{
			SDL_PollEvent(&e);

			switch (e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEMOTION:
					mouseX = e.motion.x;
					mouseY = e.motion.y;
					break;
				case SDL_MOUSEBUTTONUP:
					if (leftMouseButtonDown && e.button.button == SDL_BUTTON_LEFT)
					{
						leftMouseButtonDown = false;
					}
					
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (!leftMouseButtonDown && e.button.button == SDL_BUTTON_LEFT && whosTurn == COLOUR::WHITE)
					{
						leftMouseButtonDown = true;
						
						for (int x = 0; x < 8; x++)
						{
							for (int y = 0; y < 8; y++)
							{
								SDL_Point point = { mouseX, mouseY };
								SDL_Rect hitRect = board->GetTile(x, y)->GetWorldRect();
								if (SDL_PointInRect(&point, &hitRect))
								{
									if (canSelectTile)
									{
										if (board->GetPieceAt(x, y, whosTurn) != nullptr)
										{
											canSelectTile = false;

											board->GetPieceAt(x, y, whosTurn)->SetSelected(true);
											selectedPieceIdx = board->GetIdxOfPieceAt(x, y, whosTurn);
											board->GetTile(x, y)->selected = true;
											selectedTileX = x;
											selectedTileY = y;
											
											if (!board->IsColourInCheck(COLOUR::WHITE)) //not in check
											{
												ChessBoard boardCopy = *board;
												Piece pieceCopy = *boardCopy.GetPieceAt(x, y, whosTurn);
												moves = *(movementGenerator->GenerateMovesForPiece(pieceCopy, boardCopy));

												for (vector<Move>::const_iterator move = moves.begin(); move != moves.end(); ++move)
												{
													board->GetTile(move->targetSquareX, move->targetSquareY)->selected = true;
												}
											}
											else //is in check
											{
												ChessBoard boardCopy = *board;
												Piece pieceCopy = *boardCopy.GetPieceAt(x, y, whosTurn);
												moves = *(movementGenerator->GenerateMovesForPiece(pieceCopy, boardCopy));

												if (board->GetPieceAt(x, y, whosTurn)->GetType() == PIECETYPE::KING)
												{
													vector<Move>::iterator move = moves.begin();
													while (move != moves.end())
													{
														ChessBoard boardCopy = *board;
														vector<Piece> enemyPiecesCopy = *boardCopy.GetPiecesOfColour(InvertColour(whosTurn));
														if (movementGenerator->IsInCheck(move->targetSquareX, move->targetSquareY,enemyPiecesCopy, boardCopy))
														{
															move = moves.erase(move);
														}
														else
														{
															move++;
														}
													}
												}
												else
												{
													ChessBoard boardCopy = *board;
													SDL_Point kingPos = board->GetPieceOfType(PIECETYPE::KING, whosTurn)->GetMapPos();
													vector<Piece> enemyPiecesCopy = *boardCopy.GetPiecesOfColour(InvertColour(whosTurn));
													Piece pieceCopy = *boardCopy.GetPieceAt(x, y, whosTurn);
													moves = *(movementGenerator->GetCounterCheckMoves(enemyPiecesCopy, pieceCopy, kingPos.x, kingPos.y, boardCopy));
												}

												vector<Move>::const_iterator move = moves.begin();
												while ( move != moves.end())
												{
													board->GetTile(move->targetSquareX, move->targetSquareY)->selected = true;
													++move;
												}
												
											}
										}
									}
									else if(!canSelectTile && x == selectedTileX && y == selectedTileY)
									{
										board->GetTile(selectedTileX, selectedTileY)->selected = false;
										board->GetPieceAt(selectedPieceIdx, whosTurn)->SetSelected(false);

										for (vector<Move>::const_iterator move = moves.begin(); move != moves.end(); ++move)
										{
											board->GetTile(move->targetSquareX, move->targetSquareY)->selected = false;
										}

										canSelectTile = true;
										selectedPieceIdx = -1;
										moves.clear();
									}
									else if(!canSelectTile && board->GetTile(x, y)->selected)
									{
										if (board->GetPieceAt(x, y, InvertColour(whosTurn)) != nullptr)
										{
											board->GetPieceAt(x, y, InvertColour(whosTurn))->SetIsAlive(false);
										}

										//move piece
										board->GetPieceAt(selectedPieceIdx, whosTurn)->SetPos(x, y);
										board->GetTile(selectedTileX, selectedTileY)->selected = false;

										selectedPieceIdx = -1;
										canSelectTile = true;

										for (vector<Move>::const_iterator move = moves.begin(); move != moves.end(); ++move)
										{
											board->GetTile(move->targetSquareX, move->targetSquareY)->selected = false;
										}

										moves.clear();

										whosTurn = COLOUR::BLACK;
									}
									
								}
							}
						}
					}
					break;
			}

			//clear screen
			SDL_RenderClear(gRenderer);
			//Render textures to screen
			board->RemoveKilledPieces();
			board->RenderChessBoard();
			board->RenderPieces();
			//update screen
			SDL_RenderPresent(gRenderer);



			//AI turn
			if (whosTurn == COLOUR::BLACK)
			{
				ChessBoard boardCopy = *board;
				Move move; 
				if (turnNumber > 3)
				{
					move = computer->GenerateBestMove(boardCopy);
				}
				else
				{
					move = computer->GenerateRandomAIMove(boardCopy);
				}

				board->MakeMove(move);

				Piece* piece = board->GetPieceAt(move.targetSquareX, move.targetSquareY, InvertColour(whosTurn));
				
				if (piece != NULL)
				{
					piece->SetIsAlive(false);
				}

				whosTurn = COLOUR::WHITE;
				turnNumber++;
				cout << "Turn: " << turnNumber << endl;
			}
			

			ChessBoard boardCopy = *board;

			//Check ForCheck
			//white
			Piece kingPieceCopy = *boardCopy.GetPieceOfType(PIECETYPE::KING, COLOUR::WHITE);
			vector<Piece> piecesCopy = *boardCopy.GetPiecesOfColour(COLOUR::BLACK);
			board->SetCheck(COLOUR::WHITE, movementGenerator->IsInCheck(kingPieceCopy, piecesCopy, boardCopy));
			//black
			kingPieceCopy = *boardCopy.GetPieceOfType(PIECETYPE::KING, COLOUR::BLACK);
			piecesCopy = *boardCopy.GetPiecesOfColour(COLOUR::WHITE);
			board->SetCheck(COLOUR::BLACK, movementGenerator->IsInCheck(kingPieceCopy, piecesCopy, boardCopy));



			//check for checkmate
			bool canCounterWhite = false;
			bool canCounterBlack = false;
			if (whosTurn == COLOUR::WHITE && board->IsColourInCheck(COLOUR::WHITE))
			{				
				Piece kingPieceCopy = *boardCopy.GetPieceOfType(PIECETYPE::KING, COLOUR::WHITE);
				vector<Piece> piecesCopy = *boardCopy.GetPiecesOfColour(COLOUR::WHITE);
				vector<Piece> enemyPiecesCopy = *boardCopy.GetPiecesOfColour(COLOUR::BLACK);
				for (int i = 0; piecesCopy.size(); i++)
				{
					  vector<Move> counterMoves = *movementGenerator->GetCounterCheckMoves(enemyPiecesCopy, piecesCopy.at(i), kingPieceCopy.GetMapPos().x, kingPieceCopy.GetMapPos().y, boardCopy);
					  if (counterMoves.size() != 0)
					  {
						  canCounterWhite = true;
						  break;
					  }
				}

			}
			else if(board->IsColourInCheck(COLOUR::BLACK))
			{
				Piece kingPieceCopy = *boardCopy.GetPieceOfType(PIECETYPE::KING, COLOUR::BLACK);
				vector<Piece> piecesCopy = *boardCopy.GetPiecesOfColour(COLOUR::WHITE);
				vector<Piece> enemyPiecesCopy = *boardCopy.GetPiecesOfColour(COLOUR::WHITE);
				for (int i = 0; piecesCopy.size(); i++)
				{
					vector<Move> counterMoves = *movementGenerator->GetCounterCheckMoves(enemyPiecesCopy, piecesCopy.at(i), kingPieceCopy.GetMapPos().x, kingPieceCopy.GetMapPos().y, boardCopy);
					if (counterMoves.size() != 0)
					{
						canCounterBlack = true;
						break;
					}
				}
			}

			if (canCounterWhite == false && board->IsColourInCheck(COLOUR::WHITE))
			{
				cout << "CheckMate. White Loses" << endl;
				quit = true;
			}
			else if (canCounterBlack == false && board->IsColourInCheck(COLOUR::BLACK))
			{
				cout << "Checkmate. Black Loses" << endl;
				quit = true;
			}

		}
	}

	//Free resources and close SDL
	board->DeleteTexture();
	Close();

	return 0;
}



