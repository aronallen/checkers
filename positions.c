/*
 *  positions.c
 *  hello
 *
 *  Created by Aron Allen on 2/8/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "main.h"


void piecesInGameForActivePlayer(PGAME game){

	PIECES pieces;
	int i = 0;
	
	int blackCount = bitsInBitboard((*game).black);
	int whiteCount = bitsInBitboard((*game).white);
	
	pieces.piecesCount = 0;
	
	
	
	
		
	i = 31;
		
		while (i >= 0 && pieces.piecesCount <= (*game).whitePieces.piecesCount){
		
		if (bitboardForRealPosition[i]&(*game).white){
				pieces.piecesCount++;
				pieces.positionsBitboard[pieces.piecesCount -1] = bitboardForRealPosition[i];
				pieces.positions[pieces.piecesCount -1] = i;
		}
		
		i--;

			
		
	}
	
	
	if (pieces.piecesCount != whiteCount) {
		printf("white piece lost!\n");
	}
		
	(*game).whitePieces = pieces;
	
	pieces.piecesCount = 0;
	
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
	
	if (pieces.piecesCount != blackCount) {
		printf("black piece lost!\n");
	}

	
	
	return;
}


