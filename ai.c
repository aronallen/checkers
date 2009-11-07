/*
 *  ai.c
 *  hello
 *
 *  Created by Aron Allen on 25/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "mover.h"
#include "print.h"
#include "bitops.h"
#include "jumper.h"
#include "print.h"
#include "positions.h"
#include "commitjump.h"
#include "commitmove.h"
#include "ai.h"




int bestMJ(PGAME game, PGAMESESSION winsDatabase, int winsDatabaseSessionCounter){
	
	
	
	
	long long unsigned *moveScore = malloc (sizeof (GAMESESSION) * (*game).mjCount);
	int i;
	
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
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	
	if (enemy == 'b') {
		enemyPiecesCount = bitsInBitboard((*game).black);
		friendlyPiecesCount = bitsInBitboard((*game).white);

	}
	if (enemy == 'w') {
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
	winsDatabaseSessionCounter = winsDatabaseSessionCounter - 1;
	
	for (i=0;i < winsDatabaseSessionCounter;i++){
	
			
			for (j=0; j < winsDatabase[i].moveCount; j++){
				
				if (testGame.black == winsDatabase[i].moves[j].black && testGame.white == winsDatabase[i].moves[j].white && testGame.kings == winsDatabase[i].moves[j].kings ) {
					
				
					if (winsDatabase[i].winner == (*game).turn) {

						moveScore[h]+=3;

					}
				
					if (winsDatabase[i].winner == 'n') {
						moveScore[h]-=2;

					}

					changeTurn(&testGame);
					cleanUp(&testGame);
					
					findJumpersForGame(&testGame);
					
					
					if (winsDatabase[i].winner == (*game).turn) {
						
						moveScore[h]-=3;
					
					}
					
					
					if (enemy == 'w') {
						moveScore[h] = moveScore[h] + (2*(enemyPiecesCount - bitsInBitboard(testGame.white)));

					}
					if (enemy == 'b') {
						moveScore[h] = moveScore[h] + (2*(enemyPiecesCount - bitsInBitboard(testGame.black)));

					}
					
					moveScore[h]+= winsDatabase[i].moves[j].relevance;
					
			
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
		
	free(bestMJs);
	free(moveScore);
		
	return bestmj;

}