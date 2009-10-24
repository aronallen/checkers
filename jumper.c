/*
 *  jumper.c
 *  hello
 *
 *  Created by Aron Allen on 31/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>
#include <memory.h>
#include "main.h"
#include "mover.h"
#include "print.h"
#include "bitops.h"
#include "jumper.h"
#include "print.h"
#include "positions.h"


int jumpNorthWest(PGAME game, PJUMP jump){

	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_NORTH_MOVE & LEGAL_WEST_MOVE;
	
	
	enemy = ((*game).turn == 'w') ? (*game).black : (*game).white;
	position = ((*jump).intermediatePosistions == 0) ? (*jump).origin : (*jump).intermediates[(*jump).intermediatePosistions-1];
	
	(*jump).direcetionsForPositions[realPositionForBitboard(position)].northWest = 1;
	
	//checks if the piece we are moving is either a black king, or white soldier.
	if (((*game).white & (*jump).origin) || ((*game).black&(*game).kings&(*jump).origin)){
		
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   northWestRotate(position) & enemy & legalMove & ~((*jump).removePieces)   &&    northWestRotate(northWestRotate(position)) & (*game).notOccupied){
	
			(*jump).intermediates[(*jump).intermediatePosistions] = northWestRotate(northWestRotate(position));
			(*jump).removePieces = (*jump).removePieces | northWestRotate(position);
			(*jump).intermediatePosistions ++;
			(*jump).direcetionsForPositions[realPositionForBitboard(position)].northWest = 2;
			return 1;

			
		}
		
	}

	return 0;
}




int jumpNorthEast(PGAME game, PJUMP jump){
	
	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_NORTH_MOVE & LEGAL_EAST_MOVE;
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = ((*jump).intermediatePosistions == 0) ?(*jump).origin :(*jump).intermediates[(*jump).intermediatePosistions-1];
	
	
	(*jump).direcetionsForPositions[realPositionForBitboard(position)].northEast = 1;

	
	//checks if the piece we are moving is either a black king, or white soldier.
	if (((*game).white & (*jump).origin) || ((*game).black&(*game).kings&(*jump).origin)){
		
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   northEastRotate(position) & enemy & legalMove & ~((*jump).removePieces)   &&    northEastRotate(northEastRotate(position)) & (*game).notOccupied){
			
			(*jump).intermediates[(*jump).intermediatePosistions] = northEastRotate(northEastRotate(position));
			(*jump).removePieces = (*jump).removePieces | northEastRotate(position);
			(*jump).intermediatePosistions ++;
			(*jump).direcetionsForPositions[realPositionForBitboard(position)].northEast = 2;
			return 1;

		}
		
	}
	
	return 0;
}



int jumpSouthWest(PGAME game, PJUMP jump){
	
	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_SOUTH_MOVE & LEGAL_WEST_MOVE;
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = ((*jump).intermediatePosistions == 0) ?(*jump).origin :(*jump).intermediates[(*jump).intermediatePosistions-1];
	
	
	(*jump).direcetionsForPositions[realPositionForBitboard(position)].southWest = 1;

	
	if (((*game).black & (*jump).origin) || ((*game).white&(*game).kings&(*jump).origin)){
		
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   southWestRotate(position) & enemy & legalMove & ~((*jump).removePieces)   &&    southWestRotate(southWestRotate(position)) & (*game).notOccupied){
			
			(*jump).intermediates[(*jump).intermediatePosistions] = southWestRotate(southWestRotate(position));
			(*jump).removePieces = (*jump).removePieces | southWestRotate(position);
			(*jump).intermediatePosistions ++;
			(*jump).direcetionsForPositions[realPositionForBitboard(position)].southWest = 2;
			return 1;

		}
		
	}
	
	return 0;
}


int jumpSouthEast(PGAME game, PJUMP jump){
	
	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_SOUTH_MOVE & LEGAL_EAST_MOVE;
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = ((*jump).intermediatePosistions == 0) ?(*jump).origin : (*jump).intermediates[(*jump).intermediatePosistions-1];
	
	
	(*jump).direcetionsForPositions[realPositionForBitboard(position)].southEast = 1;

	
	if (((*game).black & (*jump).origin) || ((*game).white&(*game).kings&(*jump).origin)){
		
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   southEastRotate(position) & enemy & legalMove & ~((*jump).removePieces)   &&    southEastRotate(southEastRotate(position)) & (*game).notOccupied){
			
			(*jump).intermediates[(*jump).intermediatePosistions] = southEastRotate(southEastRotate(position));
			(*jump).removePieces = (*jump).removePieces | southEastRotate(position);
			(*jump).intermediatePosistions ++;
			(*jump).direcetionsForPositions[realPositionForBitboard(position)].southEast = 2;
			return 1;

		}
		
	}
	
	return 0;
}


void findNextJump(PGAME game, PJUMP jump){

	int jumpSuccses = 0;
	
	PJUMP originalJump = jump;
	
	int currentPosition;
	
	if ((*jump).intermediatePosistions)
		currentPosition = realPositionForBitboard((*jump).intermediates[(*jump).intermediatePosistions]);
	
	int jumpNumber = (*game).jumpCount;
	if ((*game).jumps[(jumpNumber)].direcetionsForPositions[currentPosition].northWest == 2||jumpNorthWest(game, jump)){
		findNextJump(game, jump);
		jumpSuccses = 1;
	}
	
	jump = originalJump;
	
	if ((*game).jumps[(jumpNumber)].direcetionsForPositions[currentPosition].northEast == 2||jumpNorthEast(game, jump)){
		findNextJump(game,jump);
		jumpSuccses = 1;
	}
	
	jump = originalJump;
	
	if ((*game).jumps[(jumpNumber)].direcetionsForPositions[currentPosition].southWest == 2||jumpSouthWest(game, jump)){
		findNextJump(game, jump);
		jumpSuccses = 1;
	}
	
	jump = originalJump;
	
	if ((*game).jumps[(jumpNumber)].direcetionsForPositions[currentPosition].southEast == 2||jumpNorthEast(game, jump)) {
		findNextJump(game, jump);
		jumpSuccses = 1;
	}
	
	if (!jumpSuccses && (*jump).intermediatePosistions){
		(*jump).endOfJump = 1;
		(*game).jumpCount++;
	}

};




void findJumpersForGame(PGAME game){
	
	int i;
	PJUMP jumper;
	newJump(jumper);
	
	if ((*game).turn=='w'){
		
		piecesInGameForActivePlayer(game);
		
		for (i=0;i<(*game).whitePieces.piecesCount;i++){
		
			(*jumper).origin = (*game).whitePieces.positionsBitboard[i];
			findNextJump(game, jumper);
			//Check if some jump was found and add it to the jump stack
			
			
			i++;
		};
	
	}
	if ((*game).turn=='b'){
		
		piecesInGameForActivePlayer(game);
		
		
		for (i=0;i<(*game).blackPieces.piecesCount;i++){
		
			(*jumper).origin = (*game).blackPieces.positionsBitboard[i];
			findNextJump(game, jumper);
			//Check if some jump was found and add it to the jump stack
			
			i++;
		};
			
	}
	
	
	
};
			
			
void newJump(PJUMP jump){
	memset(jump, 0, sizeof(*jump));
}