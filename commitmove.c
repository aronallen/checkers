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



void makeMove(int moveNumber, PGAME game){	
	if ((*game).moveCount == 0 || moveNumber > (*game).moveCount){
		printf("error, movecount:%d passedmove%d\n",moveNumber,(*game).moveCount);
		return;
	}
	
	BITBOARD origin = (*game).moves[moveNumber].origin;
	
	BITBOARD move = (*game).moves[moveNumber].origin | (*game).moves[moveNumber].destination;
	
		

			
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
	
	(*game).moveCount = 0;
	(*game).notOccupied = ~((*game).black|(*game).white);
	return;
}