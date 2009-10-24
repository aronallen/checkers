/*
 *  positions.c
 *  hello
 *
 *  Created by Aron Allen on 2/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "main.h"
#include "print.h"
#include "mover.h"
#include "positions.h"


void piecesInGameForActivePlayer(PGAME game){

	PIECES pieces;
	int i = 0;
	
	pieces.piecesCount = 0;
	
	
	
	
	if ((*game).turn == 'w'){
		
		i = 31;
		
		while (i >= 0 && pieces.piecesCount <= (*game).whitePieces.piecesCount){
		
			if (bitboardForRealPosition[i]&(*game).white){
				pieces.piecesCount++;
				pieces.positionsBitboard[pieces.piecesCount -1] = bitboardForRealPosition[i];
				pieces.positions[pieces.piecesCount -1] = i;
			}
		
			i--;
		
		
		}
		
		(*game).whitePieces = pieces;
	
	}
	if ((*game).turn == 'b'){
	
		i = 0;
		
		while (i < 32 && pieces.piecesCount <= (*game).blackPieces.piecesCount) {
			
			if (bitboardForRealPosition[i]&(*game).black){
				pieces.piecesCount++;
				pieces.positionsBitboard[pieces.piecesCount - 1] = bitboardForRealPosition[i];
				pieces.positions[pieces.piecesCount - 1] = i;
			}
			
			i++;
		}
	
		(*game).blackPieces = pieces;
	}

	
	
	return;
}

void piecesInGameForPlayer(PGAME game, char player){
	
	PIECES pieces;
	int i = 0;
	
	pieces.piecesCount = 0;
	
	
	
	
	if (player == 'w'){
		
		i = 31;
		
		while (i >= 0 && pieces.piecesCount <= (*game).whitePieces.piecesCount){
			
			if (bitboardForRealPosition[i]&(*game).white){
				pieces.piecesCount++;
				pieces.positionsBitboard[pieces.piecesCount -1] = bitboardForRealPosition[i];
				pieces.positions[pieces.piecesCount -1] = i;
			}
			
			i--;
			
			
		}

		(*game).whitePieces = pieces;

	}
	if (player == 'b'){
		
		i = 0;
		
		while (i < 32 && pieces.piecesCount <= (*game).blackPieces.piecesCount) {
			
			if (bitboardForRealPosition[i]&(*game).black){
				pieces.piecesCount++;
				pieces.positionsBitboard[pieces.piecesCount - 1] = bitboardForRealPosition[i];
				pieces.positions[pieces.piecesCount - 1] = i;
			}
			
			i++;
		}
		
		
		(*game).blackPieces = pieces;
	}
	
	
	
	return;
}



