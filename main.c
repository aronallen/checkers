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
	GAME theGame;
	int select;
	int theTime;
	int move;
	int moveCounter = 0;
	int i;
	int victoryCount = 0;
//	long long unsigned deepSearch = 1;
//	int searchLevel = 6;
//	int search = 0;
	
	srand(time(0));
	
	theTime = time(0);	
	printf("press 1 for new game, press 2 for game to test crowning:");
	scanf("%d",&select);

	
	for (i=0;i<10000;i++){
	
	
	if (select == 2)
		theGame = game(0x10400000, 0x208000, 0, 'b');
	else
		theGame = newGame();


	
	
	
	cleanUp(&theGame);	
	
	findJumpersForGame(&theGame);
	findMoversForGame(&theGame);	
//	printGame(&theGame);

	
	while (theGame.white && theGame.black && (theGame.moveCount || theGame.jumpCount)) {
//		printf("\n%c turn\n", theGame.turn);
//		srand(time(0));
		if (theGame.jumpCount) {
//			printf("jumps found: %d\n", theGame.jumpCount);
			
//			if (search < searchLevel)
//				deepSearch = theGame.jumpCount*deepSearch;
			
			move = rand() % (theGame.jumpCount);
//			printf("best jump is %d\n", move+1);
			makeJump(move, &theGame);
		}
		if (theGame.moveCount){
			move = rand() % theGame.moveCount;
			
//			if (search < searchLevel)
//				deepSearch = theGame.moveCount*deepSearch;
			
			makeMove(move, &theGame);	
		}
		cleanUp(&theGame);
		changeTurn(&theGame);
		moveCounter++;
//		printGame(&theGame);
//		printf("Move %d\n", moveCounter);		
		
		findJumpersForGame(&theGame);
		
//		search++;

		if (theGame.jumpCount) {
		}else{
			findMoversForGame(&theGame);
		}

	}
	
	if (theGame.white && !theGame.black){
//		printf("white wins\n");
	}
	if (theGame.black && !theGame.white) {
//		printf("black wins\n");
	} 
	if (theGame.moveCount == 0 && theGame.jumpCount == 0){
	
	if (theGame.turn == 'w') {
//			printf("White looses, no more moves\n");
			victoryCount++;
		}else {
//			printf("Black looses, no more moves\n");
			victoryCount--;
		}

	
	}
	
	
//	printGame(&theGame);
	
	}
	theTime = time(0) - theTime;
	
	printf("%d, moves in %d seconds, victoryCount is %d\n",moveCounter, theTime, victoryCount);
	
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
	game.moveCount=0;
	game.jumpCount=0;
	game.blackPieces.piecesCount = 12;
	game.whitePieces.piecesCount = 12;
	piecesInGameForPlayer(&game, 'b');
	piecesInGameForPlayer(&game, 'w');

	
	game.jumpCount = 0;

	
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
	(*game).moveCount = 0;
	(*game).jumpCount = 0;

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

