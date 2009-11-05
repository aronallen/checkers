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
	
	
	int gamesToStore = 1000;
	
	//How Deep to search
	int ply = 2;

	GAMESESSION *endGameDatabase = malloc (sizeof (GAMESESSION) * gamesToStore);
	int i;
	
	for (i = 0; i < gamesToStore; i++)
		endGameDatabase[i].moveCount = 0;
	
	GAME theGame;
	int select;
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
	printf("press 1 for new game, press 2 for game to test crowning:");
	scanf("%d",&select);

	
	for (i=0;i<gamesToStore;i++){
	
		
	totalBlackPieces = 12;
	totalWhitePieces = 12;	
	moveCounter = 0;	
		
	if (select == 2)
		theGame = game(0x10400000, 0x208000, 0, 'b');
	else
		theGame = newGame();


	staleMateCount = 80;
	endGameDatabase[i].winner = 'n';
	
	
	cleanUp(&theGame);	
	
	findJumpersForGame(&theGame);
	findMoversForGame(&theGame);	

	
	while (theGame.white && theGame.black && (theGame.mjCount) && staleMateCount > 0) {
		
		endGameDatabase[i].moves[moveCounter].black = theGame.black;
		endGameDatabase[i].moves[moveCounter].white = theGame.white;
		endGameDatabase[i].moves[moveCounter].kings = theGame.kings;

		moveCounter++;
		if (theGame.canJ) {
			if (theGame.mjCount == 1) {
				move = 0;

			}else{
				move = bestMJ(&theGame, endGameDatabase, i, ply);
			}
			makeJump(move, &theGame);
		}else{
			
			if (theGame.mjCount == 1) {
				move = 0;
			}else {
				move = bestMJ(&theGame, endGameDatabase, i, ply);
			}
			makeMove(move, &theGame);
			
		}


		if (totalBlackPieces == bitsInBitboard(theGame.black)) {
			staleMateCount--;
		}
		else {
			totalBlackPieces = bitsInBitboard(theGame.black);
			staleMateCount = 80;
		}
		if (totalWhitePieces == bitsInBitboard(theGame.white)){
			staleMateCount--;

		}else {
			totalWhitePieces = bitsInBitboard(theGame.white);
			staleMateCount = 80;
		}


		cleanUp(&theGame);
		changeTurn(&theGame);
		
		if (i==(gamesToStore-1)) {
			printGame(&theGame);
		}
		
		
		findJumpersForGame(&theGame);
		
		if (theGame.mjCount) {
		}else{
			findMoversForGame(&theGame);
		}
		
		if (!theGame.mjCount) {
			changeTurn(&theGame);
		}
		
	}
	
		
	
	if (theGame.black == 0) {
		endGameDatabase[i].moveCount = moveCounter;
		endGameDatabase[i].winner = 'w';
		whiteWins++;
		victoryCount++;
		theGame.turn = 'W';

	} 
	if (theGame.white == 0) {
		endGameDatabase[i].moveCount = moveCounter;
		endGameDatabase[i].winner = 'b';
		blackWins++;
		victoryCount--;
		theGame.turn = 'B';

	}
	if (staleMateCount <= 0) {
		theGame.turn = 'n';
	}
	
	if (theGame.turn == 'w' ){
		endGameDatabase[i].moveCount = moveCounter;
		endGameDatabase[i].winner = 'w';
		whiteWins++;
		victoryCount++;
	}
	if (theGame.turn == 'b' ){
		endGameDatabase[i].moveCount = moveCounter;
		endGameDatabase[i].winner = 'b';
		blackWins++;
		victoryCount--;


	}
		
	if (theGame.turn == 'n'){
		endGameDatabase[i].moveCount = moveCounter;
		endGameDatabase[i].winner = 'n';
		staleWins++;
	}
	printf("game over, %c wins, %d moves, gameCount %d VV-RESULT-VV\n",theGame.turn, moveCounter, i);
	printGame(&theGame);
	
//	printGame(&theGame);
	
	}
	theTime = time(0) - theTime;
	
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

