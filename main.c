#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "print.h"
#include "mover.h"
#include "bitops.h"
#include "positions.h"
#include "commitmove.h"
#include "jumper.h"
#include "commitjump.h"
#include "aialpabeta.h"
#include "aisearch.h"



int main (int argc, const char * argv[]) {
	

	int i;
	int gamesToPlay = 1;
	
	GAME theGame;
	GAME testGame;
	GAME gameHistory[200];
	
	
	int theTime;
	int move;
	int moveCounter = 0;
	int victoryCount = 0;
	int staleMateCount = 40;
	int whiteWins = 0;
	int blackWins = 0;
	int staleWins = 0;
	int turns;
	int h;
	int timeToSearch = 3;
	int newPosition;
	
	int from;
	int to;
	int noPiece;
	
	
	BITBOARD canMove;
	int canMoveLoopInt;
	
	char difficulty;
	char player;

	
	int totalBlackPieces = 12;
	int totalWhitePieces = 12;
	
	srand(time(0));
	
	theTime = time(0);
	
	printf("Welcome to the 'pwn' engine.\n");
	printf("Select your color 'b' or 'w'.\n");
	scanf("%c", &player);
	
	printf("\nSelect the opponents difficulty 'e' or 'h'.\n");

	int   ch;	
	while ((ch = getchar()) != '\n' && ch != EOF);

	scanf("%c", &difficulty);
	
	
	for (i=0;i<gamesToPlay;i++){
		
		//Set pieces count
		totalBlackPieces = 12;
		totalWhitePieces = 12;
		
		//Set move counter
		moveCounter = 0;	
		
		//Prepare a new game
		theGame = newGame();
		cleanUp(&theGame);

		//Set stalemate count
		staleMateCount = 40;
		
		//Find all jumps for the current player
		findJumpersForGame(&theGame);
		
		//If there were no jumps, then find movers instead.
		if (!theGame.canJ) {
			findMoversForGame(&theGame);
		}

		
		
		//If there are no moves, then change the turn again to the previous player.
		if (!theGame.mjCount) {
			changeTurn(&theGame);
		}

		turns = 0;
		
		while (theGame.white && theGame.black && (theGame.mjCount) && staleMateCount > 0) {
		
		
			gameHistory[turns] = theGame;
			turns++;
			
			//Increment our move counter
			moveCounter++;
			
			if (player != theGame.turn) {


		
			//Take the best or next best move
			if (difficulty == 'e') {
				move = rand()%2;	
			}else {
				move = 0;
			}

			

			
			if (theGame.turn == 'w') {
				timeToSearch = 1;
			}else {
				timeToSearch = 1;
			}

			
		
			//Find best jump, and preform it.		
			
				
			if (theGame.mjCount > 1) {
				bestMJab(&theGame, timeToSearch);
			}else {
				move = 0;
			}

				
			
			testGame = theGame;
			
			newPosition = 0;
			
			//Check if gamestate has been there before.
			if ((turns-2)>1) {
				
			
				for (move; move<theGame.mjCount && !newPosition; move++) {
				
					//Asume it is a new game state
					newPosition = 1;
				
					//Excecute move
					if (testGame.canJ) {
						makeJump(move, &testGame);
					}else{
						makeMove(move, &testGame);
					}
				
					//Run through history to se if position has been taken before.
					for (h = 0; h < turns-2; h++) {
						if (gameHistory[h].black == testGame.black && gameHistory[h].white == testGame.white && gameHistory[h].kings == testGame.kings){
							newPosition = 0;
						}
					}
				
					//Compensate for loop increment, if it is a new position
					if (newPosition) {
						move--;
					}
				}
			}
			}else {
				printGame(&theGame);
				
				
				canMove = 0;
				for(canMoveLoopInt = 0; canMoveLoopInt < theGame.mjCount; canMoveLoopInt++){
					canMove = canMove|theGame.mjs[canMoveLoopInt].intermediates[0];
				}
				
				noPiece = 0;
				
				while (!noPiece) {
					printf("select piece to move (0-31)\n");
					while ((ch = getchar()) != '\n' && ch != EOF);
					scanf("%d", &from);
					
					if (canMove & bitboardForRealPosition[from]){
							noPiece = 1;
					}

				}
				
				canMove = 0;
				
				for(canMoveLoopInt = 0; canMoveLoopInt < theGame.mjCount; canMoveLoopInt++){
					if (theGame.mjs[canMoveLoopInt].intermediates[0] & bitboardForRealPosition[from]) {
						if (theGame.mjs[canMoveLoopInt].intermediatePosistions) {
							canMove = canMove|theGame.mjs[canMoveLoopInt].intermediates[theGame.mjs[canMoveLoopInt].intermediatePosistions];
						}else {
							canMove = canMove|theGame.mjs[canMoveLoopInt].intermediates[1];
						}

					}
				}
				printBitboard(canMove);
				
				noPiece = 0;
				while (!noPiece) {
					printf("select where to move to\n");
					while ((ch = getchar()) != '\n' && ch != EOF);
					scanf("%d", &to);
					
					if (canMove & bitboardForRealPosition[to]){
						noPiece = 1;
					}
					if (!noPiece) {
						printf("Piece at position %d cannot move to position %d\n", from, to);
					}
				}
				
				
				for (canMoveLoopInt = 0; canMoveLoopInt < theGame.mjCount; canMoveLoopInt++) {
					if (theGame.mjs[canMoveLoopInt].intermediates[0] & bitboardForRealPosition[from]) {
						if (theGame.mjs[canMoveLoopInt].intermediatePosistions) {
							move = canMoveLoopInt;
						}else {
							move = canMoveLoopInt;
						}
					}
				}
			}
			
			if (theGame.canJ) {
				makeJump(move, &theGame);
			}else {
				makeMove(move, &theGame);
			}

			
			if (theGame.turn == 'b') {
				printf("Black's moved move %d\n", move);
			}else {
				printf("White's moved move %d\n", move);
			}
		
		
			//Stalemate checker
			if (totalBlackPieces == bitsInBitboard(theGame.black) && totalWhitePieces == bitsInBitboard(theGame.white)) {
				staleMateCount--;
			}
			else {
				totalBlackPieces = bitsInBitboard(theGame.black);
				totalWhitePieces = bitsInBitboard(theGame.white);
				staleMateCount = 40;
			}
			
		
		
			//Change the turn and crown pieces.
			changeTurn(&theGame);
			cleanUp(&theGame);

		
		
			//Print all moves, if we are at the last game
			printGame(&theGame);
		
			//Find all jumps for the current player
			findJumpersForGame(&theGame);
			
			//If there were no jumps, then find movers instead.
			if (!theGame.canJ) {
				findMoversForGame(&theGame);
//				printf("moves found\n");
			}else {
//				printf("jumps found\n");
			}
			
//			printGame(&theGame);
		
			//If there are no moves, then change the turn again to the previous player.
			if (!theGame.mjCount) {
				changeTurn(&theGame);
//				printf("no mj's found\n");
			}
			

			
		}
		
		
		//Increment our move counter
		moveCounter++;
		
		//If stalemate count is reached, no one wins	
		if (staleMateCount <= 0) {
			theGame.turn = 'n';
		}
		
		//If black is eliminated, White wins.
		if (theGame.black == 0) {
			whiteWins++;
			victoryCount++;
			theGame.turn = 'W';

		} 
		//If white is eliminated, Black wins	
		if (theGame.white == 0) {
			blackWins++;
			victoryCount--;
			theGame.turn = 'B';
			
		}
		
		
	
		//If black has no more moves, white wins
		if (theGame.turn == 'w' ){
			whiteWins++;
			victoryCount++;
		}
	
		//If white has no more moves, black wins
		if (theGame.turn == 'b' ){
			blackWins++;
			victoryCount--;


		}
		
		//No winner.
		if (theGame.turn == 'n'){
			staleWins++;
	
	
		}
	
		
		
		
		

		printf("%d, games, whiteWins is %d, blackWins is %d, staleWins is %d, games to search: %d\n",i+1, whiteWins, blackWins, staleWins);
		
		
	

	}
	theTime = time(0) - theTime;
	
	
	printf("%d, games in %d seconds, whiteWins is %d, blackWins is %d, staleWins is: %d\n",i-1, theTime, whiteWins, blackWins, staleWins);
	
	return 0;
}



//Setsup a new game.
GAME newGame(){
	BITBOARD white = 0x041C71C3;
	BITBOARD black = 0xE3820C38;
	BITBOARD kings = 0x00000000;
	char turn = 'b';
	return game(black, white, kings, turn);
}

GAME game(BITBOARD black, BITBOARD white, BITBOARD kings, char turn){
	
	GAME game;
	
	if (turn != 'w' && turn !='b')
		turn = 'b';
	
	
	game.black=black;
	game.white=white;
	game.kings=kings;
	game.notOccupied =~(game.white|game.black);
	game.turn=turn;
	game.mjCount=0;
	game.canJ = 0;
	game.score = 0;
	game.parrentGame = 0;
	game.blackPieces.piecesCount = 12;
	game.whitePieces.piecesCount = 12;
	piecesInGameForActivePlayer(&game);

	
	return game;
}

void changeTurn(PGAME game){
	

	if ((*game).turn == 'w')
		(*game).turn = 'b';
	else
		(*game).turn = 'w';
	
	
	if ((*game).black & ~(LEGAL_SOUTH_MOVE)){
		(*game).kings = (*game).kings | ((*game).black & ~(LEGAL_SOUTH_MOVE));
	}
	if ((*game).white & ~(LEGAL_NORTH_MOVE)){
		(*game).kings = (*game).kings | ((*game).white & ~(LEGAL_NORTH_MOVE));
	}
	return;
}

void cleanUp (PGAME game){

	(*game).notOccupied =~((*game).white|(*game).black);
	(*game).mjCount = 0;
	(*game).canJ = 0;

	return;
}

int isPieceFriendly (GAME game, BITBOARD position){

	if (game.turn == 'w'){
		if (pieceAtPosition(&game, position) == 'w' || pieceAtPosition(&game, position) == 'W')
			return 1;
	}
	
	if (game.turn == 'b'){
		if (pieceAtPosition(&game, position) == 'b' || pieceAtPosition(&game, position) == 'B')
			return 1;
		}
	return 0;
}


void addMoveToEndGameDatabase (PGAMESESSION db, PGAME theGame, int gameNumber){
	
	//Expand Array if full.
	if (db[gameNumber].movesAllocated == db[gameNumber].moveCount){
	
		if (db[gameNumber].movesAllocated == 0){
			db[gameNumber].movesAllocated == 10;
		}else {
			db[gameNumber].movesAllocated += 10;
		}
	
	PLIGHTGAME tmp;
	tmp = (PLIGHTGAME) realloc(db[gameNumber].moves, sizeof(LIGHTGAME) * db[gameNumber].movesAllocated);

	if (!tmp) {
		printf("error! panic!\n");
	}
	else {
		db[gameNumber].moves = tmp;
	}
	}
	
	
	//Add current game-state to egDB
	db[gameNumber].moves[db[gameNumber].moveCount].black = (*theGame).black;
	db[gameNumber].moves[db[gameNumber].moveCount].white = (*theGame).white;
	db[gameNumber].moves[db[gameNumber].moveCount].kings = (*theGame).kings;	
	db[gameNumber].moves[db[gameNumber].moveCount].turn = (*theGame).turn;	
	
}

