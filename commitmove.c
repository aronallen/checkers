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



void makeMove(int moveNumber, PGAME game){	
	if ((*game).mjCount == 0 || moveNumber > (*game).mjCount){
		printf("error, movecount:%d passedmove%d, making random move instead\n",(*game).mjCount,moveNumber);
		moveNumber = rand()%(*game).mjCount;
	}
	
	BITBOARD origin = (*game).mjs[moveNumber].intermediates[0];
	BITBOARD destination = (*game).mjs[moveNumber].intermediates[1];
	
	BITBOARD move = origin | destination;
	
		

			
	if ((*game).turn == 'w'){
					
		if ((*game).kings & origin & (*game).white){
			(*game).kings = (*game).kings ^ move;
		}
		(*game).white = (*game).white ^ move;
	
	}
				
	if ((*game).turn == 'b'){
		
		if ((*game).kings & origin & (*game).black){
			(*game).kings = (*game).kings ^ move;
		}
		(*game).black = (*game).black ^ move;
	}
	
	(*game).notOccupied = ~((*game).black|(*game).white);
	return;
}