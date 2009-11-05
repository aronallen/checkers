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




int bestMJ(PGAME game, PGAMESESSION winsDatabase, int winsDatabaseSessionCounter, int ply){
	
	
	
	
	int *moveScore = malloc (sizeof (GAMESESSION) * (*game).mjCount);
	int i;
	
	for (i = 0; i < (*game).mjCount; i++)
		moveScore[i] = 0;
	
	int h;
	int j;
	GAME testGame = (*game);
	
	int bestmj;
	
	
	int enemyPiecesCount;
	char enemy;
	
	if ((*game).turn == 'w') {
		enemyPiecesCount = bitsInBitboard((*game).black);
		enemy = 'b';
	}
	if ((*game).turn == 'b') {
		enemyPiecesCount = bitsInBitboard((*game).white);
		enemy = 'w';
	}	
	
	srand(time(0));
	
	bestmj = rand()%(*game).mjCount;
	
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

						moveScore[h]++;
						moveScore[h]++;
						moveScore[h]++;
					}
				
					if (winsDatabase[i].winner == 'n') {
						moveScore[h]--;
						moveScore[h]--;
					}

					changeTurn(&testGame);
					cleanUp(&testGame);
					
					if (winsDatabase[i].winner == (*game).turn) {
						
						moveScore[h]--;
						moveScore[h]--;
						moveScore[h]--;
					
					}
					
					if (ply) {
						ply--;
						findJumpersForGame(&testGame);
						if (testGame.canJ) {
							makeJump( bestMJ(&testGame, winsDatabase, winsDatabaseSessionCounter, ply), &testGame);
						}else if (testGame.mjCount) {
							makeMove( bestMJ(&testGame, winsDatabase, winsDatabaseSessionCounter, ply), &testGame);
						}
					}
					if (testGame.canJ) {
						moveScore[h]--;
					}
					
					if (enemy == 'w') {
						moveScore[h] = moveScore[h] + (2*(enemyPiecesCount - bitsInBitboard(testGame.white)));
						moveScore[h] = moveScore[h] - (2*(enemyPiecesCount - bitsInBitboard(testGame.black)));

					}
					if (enemy == 'b') {
						moveScore[h] = moveScore[h] + (2*(enemyPiecesCount - bitsInBitboard(testGame.black)));
						moveScore[h] = moveScore[h] - (2*(enemyPiecesCount - bitsInBitboard(testGame.white)));

					}
			
				}
			}
			}
		testGame = (*game);

	}
	
	
	h = 0;
	
	for (i=0; i < (*game).mjCount; i++) {
	
		if (moveScore[i] > moveScore[bestmj]) {
			bestmj = i;
		}
	}
	
	

	
	
	return bestmj;

}