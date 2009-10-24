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


void jumpNorthWest(struct GAME *game, struct JUMP *jump){

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

			
		}
		
	}

	return;
}




void jumpNorthEast(struct GAME *game, struct JUMP *jump){
	
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

		}
		
	}
	
	return;
}



void jumpSouthWest(struct GAME *game, struct JUMP *jump){
	
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

		}
		
	}
	
	return;
}


void jumpSouthEast(struct GAME *game, struct JUMP *jump){
	
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

		}
		
	}
	
	return;
}



void findJumpersForGame(struct GAME *game){





};
			
			
void newJump(struct JUMP *jump){
	memset(jump, 0, sizeof(*jump));
}