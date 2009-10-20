/*
 *  commitmove.c
 *  hello
 *
 *  Created by Aron Allen on 31/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdio.h>
#include "main.h"
#include "print.h"
#include "mover.h"
#include "bitops.h"
#include "commitmove.h"

struct GAME movePieceInGame(int origin, int destination, struct GAME game) {
	
	if (game.moveCount == 0){
		printf("error: no moves calculated for game\n");
		return game;
	}
	
	
	int i;

	
	for (i=0 ; i<game.moveCount;i++){
		
		if (bitboardForRealPosition[origin]==game.moves[i].origin){
			if (bitboardForRealPosition[destination]==game.moves[i].destination){
				
				if (game.turn == 'w'){
				
					game.white = game.white^game.moves[i].origin;
					game.white = game.white^game.moves[i].destination;
					
					if (game.kings & bitboardForRealPosition[origin]){
						game.kings = game.kings^game.moves[i].origin;
						game.kings = game.kings^game.moves[i].destination;
					}
					game.moveCount = 0;
				
				}
								 
				if (game.turn == 'b'){
					game.black = game.black^game.moves[i].origin;
					game.black = game.black^game.moves[i].destination;
					
					if (game.kings & bitboardForRealPosition[origin]){
						game.kings = game.kings^game.moves[i].origin;
						game.kings = game.kings^game.moves[i].destination;
					}
					
					game.moveCount = 0;
				}
			
			}
		}
		
	}

	
	game.notOccupied = ~(game.black|game.white);
	return game;
}

void makeMove(int moveNumber, struct GAME *game){	
	if ((*game).moveCount == 0 || moveNumber > (*game).moveCount){
		printf("error, movecount:%d passedmove%d\n",moveNumber,(*game).moveCount);
		return;
	}
	
	int origin = realPositionForBitboard((*game).moves[moveNumber].origin);
	int destination = realPositionForBitboard((*game).moves[moveNumber].destination);
	
	
		

			
	if ((*game).turn == 'w'){
					
		(*game).white = (*game).white^(*game).moves[moveNumber].origin;
		(*game).white = (*game).white^(*game).moves[moveNumber].destination;
					
		if ((*game).kings & bitboardForRealPosition[origin]){
						(*game).kings = (*game).kings^(*game).moves[moveNumber].origin;
						(*game).kings = (*game).kings^(*game).moves[moveNumber].destination;}
		
		(*game).moveCount = 0;}
				
		if ((*game).turn == 'b'){
		
		(*game).black = (*game).black^(*game).moves[moveNumber].origin;
		(*game).black = (*game).black^(*game).moves[moveNumber].destination;
					
		if ((*game).kings & bitboardForRealPosition[origin]){
						(*game).kings = (*game).kings^(*game).moves[moveNumber].origin;
						(*game).kings = (*game).kings^(*game).moves[moveNumber].destination;}
					
					(*game).moveCount = 0;}
	
	(*game).notOccupied = ~((*game).black|(*game).white);
	return;
}