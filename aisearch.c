/*
 *  ai.c
 *  hello
 *
 *  Created by Aron Allen on 25/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#include "main.h"




int bestMJ(PGAME game, PGAMESESSION winsDatabase, int winsDatabaseSessionCounter){
	
	
	
	
	float *moveScore = malloc (sizeof (float) * (*game).mjCount);
	int i;
	int tempScore = 0;
	
	for (i = 0; i < (*game).mjCount; i++)
		moveScore[i] = 0;
	
	
	int *bestMJs = malloc (sizeof (GAMESESSION) * (*game).mjCount);
	
	for (i = 0; i < (*game).mjCount; i++)
		bestMJs[i] = 0;
	
	
	int h;
	int j;
	GAME testGame = (*game);
	
	int bestmj;
	
	
	int enemyPiecesCount;
	int friendlyPiecesCount;

	char enemy;
		
	if ((*game).turn == 'w') {
		enemy = 'b';
		enemyPiecesCount = bitsInBitboard((*game).black);
		friendlyPiecesCount = bitsInBitboard((*game).white);

	}else{
		enemy = 'w';
		enemyPiecesCount = bitsInBitboard((*game).white);
		friendlyPiecesCount = bitsInBitboard((*game).black);
	}	
	
	srand(time(0));
	
	bestmj = (*game).mjCount%rand();
	
	for (h=0; h < (*game).mjCount; h++){
	
	if ((*game).canJ) {
		makeJump(h, &testGame);		
	}else {
		makeMove(h, &testGame);
	}
		
	for (i=0;i < winsDatabaseSessionCounter;i++){
	
			
			for (j=0; j < winsDatabase[i].moveCount; j++){
				
				if (testGame.black == winsDatabase[i].moves[j].black && testGame.white == winsDatabase[i].moves[j].white && testGame.kings == winsDatabase[i].moves[j].kings ) {
					
					tempScore = 0;
				
					if (winsDatabase[i].winner == (*game).turn) {

						tempScore+=3;

					}
				
					if (winsDatabase[i].winner == 'n') {
						tempScore-=2;

					}

					changeTurn(&testGame);
					cleanUp(&testGame);
					
					findJumpersForGame(&testGame);
					
					
					if (winsDatabase[i].winner == (*game).turn) {
						
						tempScore-=3;
					
					}
					
					
					if (enemy == 'w') {
						tempScore = tempScore + (2*(enemyPiecesCount - bitsInBitboard(testGame.white)));

					}
					if (enemy == 'b') {
						tempScore = tempScore + (2*(enemyPiecesCount - bitsInBitboard(testGame.black)));

					}
					
					tempScore *= winsDatabase[i].moves[j].score;
					
					moveScore[h] = tempScore;
					
			
				}
			}
			}
		testGame = (*game);

	}
	
	

	
	
	
	
	
	
	
	
	h = 0;
	
	for (i=0; i < (*game).mjCount; i++) {
		
		if (moveScore[i] > moveScore[bestmj]) {
			bestmj = i;
			h = 0;
		}
		
		if (moveScore[i] == moveScore[bestmj]) {
			h++;
			bestMJs[h] = i;
		}
		
	}
	
	
	bestmj = bestMJs[h%rand()];
	
//	printf("moveScore: %d", moveScore[bestmj]);
	
	
	free(bestMJs);
	free(moveScore);
		
	return bestmj;

}