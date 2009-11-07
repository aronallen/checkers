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
#include "ai.h"



int main (int argc, const char * argv[]) {
	
	int gamesToPlay = 100;
	int randomGamesToPlay = 99;
	int lastGamesToShow = 1;
	
	//Size of end game database.
	int gamesToStore = gamesToPlay;
	
	//Must be zero
	int gamesToSearch = 0;
	
	int gameNumber = 0;
	
	

	GAMESESSION *endGameDatabase = malloc (sizeof (GAMESESSION) * gamesToStore);
	int i;
	
	for (i = 0; i < gamesToStore; i++)
		endGameDatabase[i].moveCount = 0;
	
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
			printf("moves found\n");
		}else {
			printf("jumps found\n");
		}

		
		
		//If there are no moves, then change the turn again to the previous player.
		if (!theGame.mjCount) {
			changeTurn(&theGame);
		}

	
		while (theGame.white && theGame.black && (theGame.mjCount) && staleMateCount > 0) {
		
			printf("%d moves, gamenumber is %d, games to search is %d\n", moveCounter, gameNumber, gamesToSearch);
		
			//Store our game in the endgame database,
			endGameDatabase[gameNumber].moves[moveCounter].black = theGame.black;
			endGameDatabase[gameNumber].moves[moveCounter].white = theGame.white;
			endGameDatabase[gameNumber].moves[moveCounter].kings = theGame.kings;
			
			//Random games are lest relevant than analyzed games, this int is multplied with the total score, in the analyzing routine (ai.c)
			endGameDatabase[gameNumber].moves[moveCounter].relevance = (i >= randomGamesToPlay) ?4 :2;

			//Increment our move counter
			moveCounter++;
		
			//Seed random
			srand(time(0));
			//Choose random jump
			move = rand()%theGame.mjCount;
			
		
			//Find best jump, and preform it.		
			if (theGame.canJ) {
				if (i >= randomGamesToPlay) {
			
				
					if (theGame.mjCount == 1) {
						move = 0;

					}
					else{
						move = bestMJ(&theGame, endGameDatabase, gamesToSearch);
					}
				}
				
				makeJump(move, &theGame);
		
			}else{
				if (i >= randomGamesToPlay) {			
						if (theGame.mjCount == 1) {
								move = 0;
						}
						else{
							move = bestMJ(&theGame, endGameDatabase, i);
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
			
		
		
			//Change the turn.
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
		
		//Store the last move in the endgame database,
		endGameDatabase[gameNumber].moves[moveCounter].black = theGame.black;
		endGameDatabase[gameNumber].moves[moveCounter].white = theGame.white;
		endGameDatabase[gameNumber].moves[moveCounter].kings = theGame.kings;
		moveCounter++;
		
		//If stalemate count is reached, no one wins	
		if (staleMateCount <= 0) {
			theGame.turn = 'n';
		}
		
		//If black is eliminated, White wins.
		if (theGame.black == 0) {
			endGameDatabase[i].moveCount = moveCounter;
			endGameDatabase[i].winner = 'w';
			whiteWins++;
			victoryCount++;
			theGame.turn = 'W';

		} 
		//If white is eliminated, Black wins	
		if (theGame.white == 0) {
			endGameDatabase[i].moveCount = moveCounter;
			endGameDatabase[i].winner = 'b';
			blackWins++;
			victoryCount--;
			theGame.turn = 'B';
			
		}
		
		
	
		//If black has no more moves, white wins
		if (theGame.turn == 'w' ){
			endGameDatabase[i].moveCount = moveCounter;
			endGameDatabase[i].winner = 'w';
			whiteWins++;
			victoryCount++;
		}
	
		//If white has no more moves, black wins
		if (theGame.turn == 'b' ){
			endGameDatabase[i].moveCount = moveCounter;
			endGameDatabase[i].winner = 'b';
			blackWins++;
			victoryCount--;


		}
		
		//No winner.
		if (theGame.turn == 'n'){
			endGameDatabase[i].moveCount = moveCounter;
			endGameDatabase[i].winner = 'n';
			staleWins++;
	
	
		}
	
		
		
		if (endGameDatabase[i].moveCount > MAX_MOVES_GAME) {
				printf("PANIC! more moves than can be stored in the game session!\n");
		}
		
		//Move game database counter.
		if (gameNumber >= gamesToStore) {
			gameNumber = 0;
		}else {
			gameNumber++;
		}
		
		if (gamesToSearch >= gamesToStore) {
			gamesToSearch = gamesToStore;
		}else {
			gamesToSearch++;
		}
	

	}
	theTime = time(0) - theTime;
	
	free(endGameDatabase);
	
	printf("%d, games in %d seconds, whiteWins is %d, blackWins is %d, staleWins is %d\n",i-1, theTime, whiteWins, blackWins, staleWins);
	
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
	game.blackPieces.piecesCount = 12;
	game.whitePieces.piecesCount = 12;
	piecesInGameForPlayer(&game, 'b');
	piecesInGameForPlayer(&game, 'w');

	
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

