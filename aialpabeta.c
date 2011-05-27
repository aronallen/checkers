/*
 *  aialpabeta.c
 *  hello
 *
 *  Created by Aron Allen on 11/11/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "mover.h"
#include "jumper.h"
#include "commitmove.h"
#include "commitjump.h"
#include "bitops.h"
#include "aialpabeta.h"

int bestMJab(PGAME orgGame, int secondsToSearch, int plyNodeLimit){
	
	int i;
	int j;
	int h;
	int l;
	
	int nodes = 0;
	
	int endOfGameCounter = 0;
	int deepnesSearched = 0;
	int startTime = time(0);
	int abAlloc = 4;
	double score = 0.0;
	
	
	int moves;
	
	float piecesJumpedInTurn;
	
	PLIGHTGAME tempMoves;
	
	
	LIGHTGAME lightGame;
	GAME heavyGame;
	GAME heavyMoveGame;
	GAME previousGame;
	
	GAME theGame = (*orgGame);
	
	
	//Allocate array containing game tree
	PALPHABETA alphaBetaStack = calloc( abAlloc,  sizeof(ALPHABETA));
	
	//Initieate the game, and set parrent move to -1
	lightGame = lightGameFromHeavyGame(theGame);	
	lightGame.parrentGame = -1;

	//Allocate game trees children
	for (i=0; i<abAlloc; i++) {
		alphaBetaStack[i].moves = malloc(pow(2,i) * sizeof(LIGHTGAME));	
		alphaBetaStack[i].allocMove = pow(2,i);
	
	}
	
	//Initize game tree
	alphaBetaStack[0].moves[0] = lightGame;
	alphaBetaStack[0].moveCount = 1;
	alphaBetaStack[0].moves[0].score = 0.0;
	
	
	

	
	//Build the stack add scores to the last element of the stack
	//Loop stops when time runs out, or the end of the game is found
	for (i = 0; time(0) < startTime + secondsToSearch && endOfGameCounter < alphaBetaStack[i].moveCount; i++) {
				
		moves = 0;
		h = 0;
		
		//Reallocate space for game tree
		if (i+1 >=abAlloc) {
			
			//Increment allocated space
			abAlloc++;
			alphaBetaStack = realloc(alphaBetaStack, abAlloc * sizeof(ALPHABETA));
			
			//Alocate space for children.
			alphaBetaStack[i+1].moves = malloc(plyNodeLimit * 10  * sizeof(LIGHTGAME));
			alphaBetaStack[i+1].allocMove = plyNodeLimit * 10;
			alphaBetaStack[i+1].moveCount = 0;

			
		}	
		
		//Set movecount to zero
		alphaBetaStack[i+1].moveCount = 0;
		
		//Set the end of game counter to zero
		endOfGameCounter = 0;

		
		for (j = 0; j < alphaBetaStack[i].moveCount && endOfGameCounter < alphaBetaStack[i].moveCount && time(0) < startTime + secondsToSearch; j++){
						
			
			heavyGame = heavyGameFromLightGame(alphaBetaStack[i].moves[j]);
			
			if (i == 0) {
				previousGame = heavyGameFromLightGame(alphaBetaStack[i].moves[0]);
			}else {
				previousGame = heavyGameFromLightGame(alphaBetaStack[i-1].moves[alphaBetaStack[i].moves[j].parrentGame]);
			}


			
			if (goDeeper(&heavyGame, i)) {
			
			

			

				//Prepare a heavy game, from the current lightgame
			
				//Find all the jumpers in the game
				findJumpersForGame(&heavyGame);
			
			
				//If no jumps found find moves
				if (!heavyGame.canJ) {
					findMoversForGame(&heavyGame);
				}

			
				//Increment MoveCount
				alphaBetaStack[i+1].moveCount += heavyGame.mjCount;
			
			
				if (alphaBetaStack[i+1].moveCount >= alphaBetaStack[i+1].allocMove) {
			
					//Reallocate the moves stack for the current AB stack.
					tempMoves = realloc(alphaBetaStack[i+1].moves, sizeof(LIGHTGAME) * (alphaBetaStack[i+1].moveCount * (i+1)));
			
				
				if (!tempMoves) {
					printf("Temp Moves PANIC\n");
				}else {
					alphaBetaStack[i+1].moves = tempMoves;
					alphaBetaStack[i+1].allocMove =  alphaBetaStack[i+1].moveCount * (i+1);
				}
			}
			

			if (heavyGame.mjCount) {
				
				l = 0;	
				//Commit all moves and add results to stack
				for (h; h < alphaBetaStack[i+1].moveCount; h++) {
					

						heavyMoveGame = heavyGame;
					
						if (heavyMoveGame.canJ) {
							piecesJumpedInTurn = bitsInBitboard(heavyGame.mjs[l].removePieces);
							makeJump(l, &heavyMoveGame);
						}else {
							piecesJumpedInTurn = 0;
							makeMove(l, &heavyMoveGame);
						}
						if (l >= heavyMoveGame.mjCount) {
							printf("L is to high\n");
						}
					
						//score game
						heavyMoveGame.score = scoreGame(&heavyMoveGame, &theGame, piecesJumpedInTurn);

					
						nodes++;
					
						heavyMoveGame.parrentGame = j;
					
						alphaBetaStack[i].moves[j].score = 0;
					
				
						changeTurn(&heavyMoveGame);
						cleanUp(&heavyMoveGame);
					
					
					
						alphaBetaStack[i+1].moves[h] = lightGameFromHeavyGame(heavyMoveGame);
						l++;


					}
			}else{
				
				score = 0.0;
					
				if (theGame.turn == 'w') {
					
					if (heavyGame.black == 0) {
						score = 1000.0;
					}else if(heavyGame.white == 0){
						score = -1000.0;
					}

					
				}else{
				
					if (heavyGame.white == 0){
						score = 1000.0;
					}else if (heavyGame.black == 0){
						score = -1000.0;
					}
					
				}
				
				
				if (heavyGame.mjCount == 0 && !score) {
					if (theGame.turn == heavyGame.turn) {
						score = -1000.0;
					}else {
						score = 1000.0;
					}

				}
				
				alphaBetaStack[i].moves[j].score = score;

				
					
				endOfGameCounter++;
				
				}
			}

			
		}
		
		//Sort current ABstack (decending for current turn, acssending for opponent turn)
		if (alphaBetaStack[i].moves[0].turn != (*orgGame).turn) {
			qsort(alphaBetaStack[i+1].moves, alphaBetaStack[i+1].moveCount, sizeof(LIGHTGAME), stackCompare);
		}else{
			qsort(alphaBetaStack[i+1].moves, alphaBetaStack[i+1].moveCount, sizeof(LIGHTGAME), stackCompareInverted);
		}
		
		
		//If we are over the plyNodeLimit, cutoff the rest of the tree.
		if (alphaBetaStack[i+1].moveCount > plyNodeLimit) {
			
			
			tempMoves = calloc(plyNodeLimit, sizeof(LIGHTGAME));
			
			//Relese every result after onehundred
			for (l=0; l<plyNodeLimit; l++) {
				tempMoves[l] = alphaBetaStack[i+1].moves[l];
				
			}
			
			free (alphaBetaStack[i+1].moves);
			
			alphaBetaStack[i+1].moves = tempMoves;
			
			//Set the movecount and alloc count.
			alphaBetaStack[i+1].moveCount = plyNodeLimit;
			alphaBetaStack[i+1].allocMove = plyNodeLimit;
		
			
			/* DEBUGGING CHECKING IF QSORT WORKS RIGHT
			if(alphaBetaStack[i].moves[0].turn != (*orgGame).turn)
			{
			
				printf("My opponents best move has the score of %f\n", alphaBetaStack[i+1].moves[0].score );
				printf("My opponents worst move has the score of %f\n\n", alphaBetaStack[i+1].moves[plyNodeLimit].score );

				
			}
			else 
			{
				printf("My own best move has the score of %f\n", alphaBetaStack[i+1].moves[0].score );
				printf("My own worst move has the score of %f\n\n", alphaBetaStack[i+1].moves[plyNodeLimit].score );

			}
			*/

		}
		
		

		
	}
	
	
	
	
	deepnesSearched = i;
			
	//Iterate through tree, buttom up	
	for (i; i > 0; i--) {
		
			
		h = 0;

		while (h < alphaBetaStack[i].moveCount) {
			
			
			if (!alphaBetaStack[i-1].moves[alphaBetaStack[i].moves[h].parrentGame].score) {
				alphaBetaStack[i-1].moves[alphaBetaStack[i].moves[h].parrentGame].score = alphaBetaStack[i].moves[h].score;
			}

			
			//If the score of the child move is, greater than the current score, then replace it.
			
			if (alphaBetaStack[i].moves[0].turn == (*orgGame).turn) {
				if (alphaBetaStack[i-1].moves[alphaBetaStack[i].moves[h].parrentGame].score > alphaBetaStack[i].moves[h].score)
					alphaBetaStack[i-1].moves[alphaBetaStack[i].moves[h].parrentGame].score = alphaBetaStack[i].moves[h].score;
				
			}else {
				if (alphaBetaStack[i-1].moves[alphaBetaStack[i].moves[h].parrentGame].score < alphaBetaStack[i].moves[h].score)
					alphaBetaStack[i-1].moves[alphaBetaStack[i].moves[h].parrentGame].score = alphaBetaStack[i].moves[h].score;
			}

			
			
			h++;
			
		}
		
		
	}
	

	for (i=0; i < (*orgGame).mjCount; i++) {
		theGame.mjs[i].score = alphaBetaStack[1].moves[i].score;
	}
	
	
	
	
	
	qsort(theGame.mjs, theGame.mjCount, sizeof(MJ), scoreCompare);
	
	
	for (i=0; i < (*orgGame).mjCount; i++) {
		(*orgGame).mjs[i].score = theGame.mjs[i].score;
	}
	
	

	

		
	
	//FREE everything from the memory
	for (i=0; i<abAlloc; i++) {

		free(alphaBetaStack[i].moves);
	
	}
	free(alphaBetaStack);


	printf("Searched %d ply, containing %d nodes\n", deepnesSearched, nodes);
		
	return 0;
}



int stackCompare(const void *a, const void *b){
	
	
	LIGHTGAME *mA = (LIGHTGAME *) a;
	LIGHTGAME *mB = (LIGHTGAME *) b;
	
	if (mA->score > mB->score) {
		return 1;
	}else if(mA->score == mB->score)
	{
		return 0;
	}else if (mA->score < mB->score) {
		return -1;
	}
}

int stackCompareInverted(const void *a, const void *b){
	
	
	LIGHTGAME *mA = (LIGHTGAME *) a;
	LIGHTGAME *mB = (LIGHTGAME *) b;
	
	if (mA->score > mB->score) {
		return -1;
	}else if(mA->score == mB->score)
	{
		return 0;
	}else if (mA->score < mB->score) {
		return 1;
	}
}



int scoreCompareInverted(const void *a, const void *b){
	
	
	MJ *mja = (MJ *) a;
	MJ *mjb = (MJ *) b;
	
	if (mjb->score > mja->score) {
		return -1;
	}else if(mjb->score == mja->score)
	{
		return 0;
	}else if (mjb->score < mja->score) {
		return 1;
	}
}

int scoreCompare(const void *a, const void *b){
	
	
	MJ *mja = (MJ *) a;
	MJ *mjb = (MJ *) b;
	
	if (mjb->score > mja->score) {
		return 1;
	}else if(mjb->score == mja->score)
	{
		return 0;
	}else if (mjb->score < mja->score) {
		return -1;
	}
}






int goDeeper(PGAME hg, int ply){
	
	return 1;
	if (ply < 2) {
		return 1;
	}
	
	ply = ply/1.5;
	
	if ((*hg).score > -ply && (*hg).score < ply) {
		return 1;
	}
		
	return 0;

}


double scoreGame(PGAME hg, PGAME org, float piecesJumpedInTurn){

	int blackMultiplier;
	int whiteMultiplier;
	BITBOARD sideSafe = !(LEGAL_EAST_MOVE&LEGAL_WEST_MOVE);
	BITBOARD homeBase;
	

	if ((*hg).turn == 'w') {
		blackMultiplier = -1;
		whiteMultiplier = 1;
		homeBase = !LEGAL_SOUTH_MOVE;
	}else{
		blackMultiplier = 1;
		whiteMultiplier = -1;
		homeBase = !LEGAL_NORTH_MOVE;
	}

	
	float score = 0.0;

	score += bitsInBitboard((*hg).black)*blackMultiplier*10;
	score += bitsInBitboard((*hg).white)*whiteMultiplier*10;
	score += bitsInBitboard((*hg).kings&(*hg).black)*blackMultiplier*40;
	score += bitsInBitboard((*hg).kings&(*hg).white)*whiteMultiplier*40;
	score += bitsInBitboard(((*hg).black&!(*hg).kings)&homeBase)*blackMultiplier*3;
	score += bitsInBitboard(((*hg).white&!(*hg).kings)&homeBase)*whiteMultiplier*3;
	score += bitsInBitboard((*hg).white&sideSafe)*whiteMultiplier*1;
	score += bitsInBitboard((*hg).white&sideSafe)*blackMultiplier*1;	
	
	return score;
	
	if (piecesJumpedInTurn > 1) {
		piecesJumpedInTurn = 1 + (0.2*piecesJumpedInTurn);
	}else{
		piecesJumpedInTurn = 1;
	}

	
	BITBOARD orgFriends;
	BITBOARD orgEnemies;
	BITBOARD orgKings = (*org).kings;
	
	BITBOARD friends;
	BITBOARD enemies;
	BITBOARD kings = (*hg).kings;
	
	
	if ((*org).turn == 'w') {
		orgFriends = (*org).white;
		friends = (*hg).white;
		
		orgEnemies = (*org).black;
		enemies = (*hg).black;
				
	}else{
		orgFriends = (*org).black;
		friends = (*hg).black;
		
		orgEnemies = (*org).white;
		enemies = (*hg).white;
		
	}
	
	if ((*org).turn == 'w') {
		homeBase = !LEGAL_SOUTH_MOVE;
	}else {
		homeBase = !LEGAL_NORTH_MOVE;
	}




	
	int enemiesLost = 0;
	int friendsLost = 0;
	int enemyKingsLost = 0;
	int friendlyKingsLost = 0;
	int balance = 0;
	int positionScore = 0;
	
	
	int enemyCount = 0;
	int friendCount = 0;
	int enemyKingCount = 0;
	int friendlyKingCount = 0;
	
	
	//Find out how many frieldly pieces were lost
	friendsLost = bitsInBitboard(orgFriends) - bitsInBitboard(friends); //
	friendlyKingsLost = bitsInBitboard(orgFriends&orgKings) - bitsInBitboard(friends&kings); //
	
	//Find out how many enemy pieces were taken
	enemiesLost = bitsInBitboard(orgEnemies) - bitsInBitboard(enemies); //
	enemyKingsLost = bitsInBitboard(orgEnemies&orgKings) - bitsInBitboard(enemies&kings); //
	

		
	enemyCount = bitsInBitboard(enemies);
	friendCount = bitsInBitboard(friends);
		
	enemyKingCount = bitsInBitboard(enemies&kings);
	friendlyKingCount = bitsInBitboard(friends&kings);
	
	
	positionScore = bitsInBitboard((friends&!kings)&homeBase)*5;
	positionScore += bitsInBitboard(friends&sideSafe)*2;
	
	balance = friendsLost * 10;
	balance += enemiesLost * 10;
	balance += friendlyKingsLost * 30;
	balance += enemyKingsLost * 30;

	balance += positionScore;
	
	
	score = balance * piecesJumpedInTurn;

	return score;

}

