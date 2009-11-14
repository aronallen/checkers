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



int main (int argc, const char * argv[]) {
	
	int gamesToPlay = 100;
	int lastGamesToShow = 100;

	int randomGamesToPlay = 0;

	//Size of end game database.
	int gamesToStore = 1000000;
	
	//Must be zero
	int gamesToSearch = 0;
	
	int gameNumber = 0;
	

	PGAMESESSION endGameDatabase = (PGAMESESSION) malloc (sizeof (GAMESESSION) * gamesToStore);
	int i;
	
	for (i = 0; i < gamesToStore; i++){

		endGameDatabase[i].moveCount = 0;
		endGameDatabase[i].movesAllocated = 10;
		endGameDatabase[i].moves = (PLIGHTGAME)malloc(sizeof (LIGHTGAME) * endGameDatabase[gameNumber].movesAllocated);
	
	
	}
	
	GAME theGame;
	int theTime;
	int move;
	int moveCounter = 0;
	int victoryCount = 0;
	int staleMateCount = 40;
	int whiteWins = 0;
	int blackWins = 0;
	int staleWins = 0;

	
	int totalBlackPieces = 12;
	int totalWhitePieces = 12;
	
	srand(time(0));
	
	theTime = time(0);	

	
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

	
		while (theGame.white && theGame.black && (theGame.mjCount) && staleMateCount > 0) {
		
		
			//Store our game in the endgame database,
			//addMoveToEndGameDatabase(endGameDatabase, &theGame, gameNumber);
			//Random games are lest relevant than analyzed games, this int is multplied with the total score, in the analyzing routine (ai.c)
			//endGameDatabase[gameNumber].moves[moveCounter].relevance = (i >= randomGamesToPlay) ?100 :1;

			//Increment our move counter
			moveCounter++;
			//endGameDatabase[gameNumber].moveCount = moveCounter;

		
			//Choose random mjump
			move = rand()%theGame.mjCount;
			
		
			//Find best jump, and preform it.		
			if (theGame.canJ) {
				if (i >= randomGamesToPlay) {
			
				
					if (theGame.mjCount == 1) {
						move = 0;

					}
					else{
						move = bestMJab(theGame);
					}
				}
				
				makeJump(move, &theGame);
		
			}else{
				if (i >= randomGamesToPlay) {			
						if (theGame.mjCount == 1) {
								move = 0;
						}
						else{
							move = bestMJab(theGame);
						}
				}
				
				makeMove(move, &theGame);
				
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
			if (i >=  gamesToPlay-lastGamesToShow) {
				printGame(&theGame);
			}
		
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
		
		//End of game reached, analyzing who won.
		
		//Store our game in the endgame database,
		//addMoveToEndGameDatabase(endGameDatabase, &theGame, gameNumber);
		//Random games are lest relevant than analyzed games, this int is multplied with the total score, in the analyzing routine (ai.c)
		//endGameDatabase[gameNumber].moves[moveCounter].relevance = (i >= randomGamesToPlay) ?100 :1;
		
		//Increment our move counter
		moveCounter++;
		//endGameDatabase[gameNumber].moveCount = moveCounter;
		
		//If stalemate count is reached, no one wins	
		if (staleMateCount <= 0) {
			theGame.turn = 'n';
		}
		
		//If black is eliminated, White wins.
		if (theGame.black == 0) {
			endGameDatabase[gameNumber].moveCount = moveCounter;
			endGameDatabase[gameNumber].winner = 'w';
			whiteWins++;
			victoryCount++;
			theGame.turn = 'W';

		} 
		//If white is eliminated, Black wins	
		if (theGame.white == 0) {
			endGameDatabase[gameNumber].moveCount = moveCounter;
			endGameDatabase[gameNumber].winner = 'b';
			blackWins++;
			victoryCount--;
			theGame.turn = 'B';
			
		}
		
		
	
		//If black has no more moves, white wins
		if (theGame.turn == 'w' ){
			endGameDatabase[gameNumber].moveCount = moveCounter;
			endGameDatabase[gameNumber].winner = 'w';
			whiteWins++;
			victoryCount++;
		}
	
		//If white has no more moves, black wins
		if (theGame.turn == 'b' ){
			endGameDatabase[gameNumber].moveCount = moveCounter;
			endGameDatabase[gameNumber].winner = 'b';
			blackWins++;
			victoryCount--;


		}
		
		//No winner.
		if (theGame.turn == 'n'){
			endGameDatabase[gameNumber].moveCount = moveCounter;
			endGameDatabase[gameNumber].winner = 'n';
			staleWins++;
	
	
		}
	
		
		
		//Move game database counter.
		if (gameNumber >= gamesToStore-1) {
			gameNumber = 0;
		}else {
			gameNumber++;
		}
		
		if (gamesToSearch >= gamesToStore) {
			gamesToSearch = gamesToStore;
		}else {
			gamesToSearch++;
		}

		printf("%d, games, whiteWins is %d, blackWins is %d, staleWins is %d, games to search: %d\n",i+1, whiteWins, blackWins, staleWins, gamesToSearch);
		
		
	

	}
	theTime = time(0) - theTime;
	
	free(endGameDatabase);
	
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

