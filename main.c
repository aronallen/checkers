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
	int j;
	int gamesToPlay = 1000;
	
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
	int timeToSearch = 1;
	int newPosition;
	int blackPlyNodeLimit = 10000;
	int whitePlyNodeLimit = 10000;
	int plyLimit = blackPlyNodeLimit;
	
	
	char difficulty;
	char player;
	char startNewGame = 0;
	int  ch;	

	
	int totalBlackPieces = 12;
	int totalWhitePieces = 12;
	int totalKings = 0;
	
	srand(time(0));
	
	theTime = time(0);
	
	printf("Welcome to the 'pwn' engine.\n");
	printf("Select your color 'b' or 'w'. (select anything else to start a computer vs. computer game)\n");
	scanf("%c", &player);
	
	if (player == 'b') {
		printf("you selected black\n");
	}else if(player == 'w'){
		printf("you selected white\n");
	}else {
		printf("you selected a computer vs. computer game\n");
	}
	
	printf("\nSelect the opponents difficulty 'e' or 'h'.\n");
	while ((ch = getchar()) != '\n' && ch != EOF);
	scanf("%c", &difficulty);
	
	if(difficulty == 'h'){
		timeToSearch = 5;
		printf("you selected hard\n");
	}else {
		printf("you selected easy\n");
	}



	
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
			
			if (theGame.turn == 'w') {
				plyLimit = whitePlyNodeLimit;
			}else {
				plyLimit = blackPlyNodeLimit;
			}

		
		
			gameHistory[turns] = theGame;
			turns++;
			
			//Increment our move counter
			moveCounter++;
			
			if (player != theGame.turn) {


		
			//Take the best or next best move
			if (difficulty == 'e') {
				move = 0;	
			}else {
				move = 0;
			}

			
			
		
			//Find best jump, and preform it.		
			
				
			if (theGame.mjCount > 1) {
				bestMJab(&theGame, timeToSearch, plyLimit);
				move = 0;
				for (j = 0; j < theGame.mjCount; j++) {
					if (theGame.mjs[0].score == theGame.mjs[j+1].score) {
						move++;
					}else {
					}


				}
				
				printf("%d moves of %d are	equal", move, theGame.mjCount);
				if (move){
					move = rand() % move;
				}
			}else {
				move = 0;
			}

				
				
			
			testGame = theGame;
			
			newPosition = 0;
			
			//Check if gamestate has been there before.
			if ((turns-2)>1) {
				
			
				for (move; move<theGame.mjCount && !newPosition; move++) {
				
					//Max gamestate reocurrance
					newPosition = 3;
				
					//Excecute move
					if (testGame.canJ) {
						makeJump(move, &testGame);
					}else{
						makeMove(move, &testGame);
					}
				
					//Run through history to se if position has been taken before.
					for (h = 0; h < turns-2; h++) {
						if (gameHistory[h].black == testGame.black && gameHistory[h].white == testGame.white && gameHistory[h].kings == testGame.kings){
							newPosition--;
						}
					}
				
					//Compensate for loop increment, if it is a new position
					if (newPosition) {
						move--;
					}
				}
			}
			}else{
				move = askPlayerForMove(&theGame);
			}
			
			if (theGame.canJ) {
				makeJump(move, &theGame);
			}else {
				makeMove(move, &theGame);
			}

		
		
			//Stalemate checker
			if (totalBlackPieces == bitsInBitboard(theGame.black) && totalWhitePieces == bitsInBitboard(theGame.white) && totalKings == bitsInBitboard(theGame.kings)) {
				staleMateCount--;
			}
			else {
				totalBlackPieces = bitsInBitboard(theGame.black);
				totalWhitePieces = bitsInBitboard(theGame.white);
				totalKings = bitsInBitboard(theGame.kings);
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
			plyLimit = whitePlyNodeLimit;
			whitePlyNodeLimit = blackPlyNodeLimit;
			blackPlyNodeLimit = plyLimit;
		}
		
		//If black is eliminated, White wins.
		if (theGame.black == 0) {
			whiteWins++;
			victoryCount++;
			blackPlyNodeLimit -= 10;
			theGame.turn = 'W';

		} 
		//If white is eliminated, Black wins	
		if (theGame.white == 0) {
			blackWins++;
			victoryCount--;
			whitePlyNodeLimit -= 10;

			theGame.turn = 'B';
			
		}
		
		
	
		//If black has no more moves, white wins
		if (theGame.turn == 'w' ){
			whiteWins++;
			victoryCount++;
			blackPlyNodeLimit -= 10;

		}
	
		//If white has no more moves, black wins
		if (theGame.turn == 'b' ){
			blackWins++;
			victoryCount--;
			whitePlyNodeLimit -= 10;


		}
		
		//No winner.
		if (theGame.turn == 'n'){
			staleWins++;
			plyLimit = whitePlyNodeLimit;
			whitePlyNodeLimit = blackPlyNodeLimit;
			blackPlyNodeLimit = plyLimit;
	
		}
	
		
		
		
		

		printf("%d, games, whiteWins is %d, blackWins is %d, staleWins is %d, games to search: %d\n",i+1, whiteWins, blackWins, staleWins);
		
		printf("\n\nwhitePly: %d, blackPly %d\n", whitePlyNodeLimit, blackPlyNodeLimit);
		/*
		
		printf("New game 'y' or 'n'\?\n");
		while ((ch = getchar()) != '\n' && ch != EOF);
		scanf("%c", &startNewGame);
		if (startNewGame == 'y') {
			gamesToPlay++;
		}
		*/

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

int askPlayerForMove(PGAME playerGame){
	
	GAME theGame = (*playerGame);
	int move = 0;
	
	printGame(&theGame);
	int from;
	int to;
	int noPiece;
	int ch;
	
	
	BITBOARD canMove;
	int canMoveLoopInt;
	
	
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
		}else {
			printf("piece %d can not move.", from);
			if (theGame.canJ) {
				printf(" (you are forced to jump)");
			}
			printf("\n");
		}
		
		
	}
	
	canMove = 0;
	
	for(canMoveLoopInt = 0; canMoveLoopInt < theGame.mjCount; canMoveLoopInt++){
		if (theGame.mjs[canMoveLoopInt].intermediates[0] & bitboardForRealPosition[from]) {
			if (theGame.mjs[canMoveLoopInt].intermediatePosistions) {
				printf("intermediate positions %d\n", theGame.mjs[canMoveLoopInt].intermediatePosistions);
				canMove = canMove|theGame.mjs[canMoveLoopInt].intermediates[theGame.mjs[canMoveLoopInt].intermediatePosistions];
			}else{
				canMove = canMove|theGame.mjs[canMoveLoopInt].intermediates[1];
			}
			
		}
	}
	
	printf("you can move to the following positions\n");
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
				if (bitboardForRealPosition[to]& theGame.mjs[canMoveLoopInt].intermediates[theGame.mjs[canMoveLoopInt].intermediatePosistions]) {
					move = canMoveLoopInt;
				}
			}else{
				if (bitboardForRealPosition[to]& theGame.mjs[canMoveLoopInt].intermediates[1]) {
					move = canMoveLoopInt;
				}
			}
		}
	}
	return move;
}

