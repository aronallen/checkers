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

	BITBOARD me;
	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_NORTH_MOVE & LEGAL_WEST_MOVE;
	(*jump).origin = (*jump).intermediates[0];
	
	me = ((*game).turn == 'b') ?(*game).black :(*game).white;
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;



	
	
	//checks if the piece we are moving is either a black king, or white soldier.
	if (((*game).white & (*jump).origin) || ((*game).black&(*game).kings&(*jump).origin)){
				
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   northWestRotate(position) & enemy & legalMove &&    northWestRotate(northWestRotate(position)) & (*game).notOccupied){

//			printf("piece can jump NW \n");					
			(*jump).intermediatePosistions ++;			
			(*jump).intermediates[(*jump).intermediatePosistions] = northWestRotate(northWestRotate(position));
			(*jump).removePieces = (*jump).removePieces | northWestRotate(position);
			return 1;

			
		}
		
	}

	return 0;
}




int jumpNorthEast(PGAME game, PJUMP jump){

	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_NORTH_MOVE & LEGAL_EAST_MOVE;
	(*jump).origin = (*jump).intermediates[0];
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;
	
	//checks if the piece we are moving is either a black king, or white soldier.
	if (((*game).white & (*jump).origin) || ((*game).black&(*game).kings&(*jump).origin)){
		
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   northEastRotate(position) & enemy & legalMove &&    northEastRotate(northEastRotate(position)) & (*game).notOccupied){
//			printf("piece can jump NE \n");					
			(*jump).intermediatePosistions ++;			
			(*jump).intermediates[(*jump).intermediatePosistions] = northEastRotate(northEastRotate(position));
			(*jump).removePieces = (*jump).removePieces | northEastRotate(position);
			return 1;

		}
		
	}
	
	return 0;
}



int jumpSouthWest(PGAME game, PJUMP jump){
	
	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_SOUTH_MOVE & LEGAL_WEST_MOVE;
	(*jump).origin = (*jump).intermediates[0];
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;
	
	
	if (((*game).black & (*jump).origin) || ((*game).white&(*game).kings&(*jump).origin)){
		
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   southWestRotate(position) & enemy & legalMove &&    southWestRotate(southWestRotate(position)) & (*game).notOccupied){
//			printf("piece can jump SW \n");					
			(*jump).intermediatePosistions ++;			
			(*jump).intermediates[(*jump).intermediatePosistions] = southWestRotate(southWestRotate(position));
			(*jump).removePieces = (*jump).removePieces | southWestRotate(position);
			return 1;

		}
		
	}
	
	return 0;
}


int jumpSouthEast(PGAME game, PJUMP jump){



	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_SOUTH_MOVE & LEGAL_EAST_MOVE;
	
	(*jump).origin = (*jump).intermediates[0];
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;
	
	if (((*game).black & (*jump).origin) || ((*game).white&(*game).kings&(*jump).origin)){
		//Cecks if the selected piece can move NW once | checks if the NW field is occupied ny an enemy, and NW is legal from there, and that it is not jumped already | checks if landing spot is empty.
		if (position & legalMove   &&   southEastRotate(position) & enemy & legalMove &&  southEastRotate(southEastRotate(position)) & (*game).notOccupied){
//			printf("piece can jump SE \n");					
			(*jump).intermediatePosistions ++;			
			(*jump).intermediates[(*jump).intermediatePosistions] = southEastRotate(southEastRotate(position));
			(*jump).removePieces = (*jump).removePieces | southEastRotate(position);
			return 1;

		}
		
	}
	
	return 0;
}


void findJumpsForPiece(PGAME game, BITBOARD piece){
	


	int jumpLoop;
	int jumpLoopEnd;
	int jumpGood;
	int jumpFound = 0;

	
	jumpLoop = (*game).mjCount;
	jumpLoopEnd = (*game).mjCount;
	
	JUMP jumpOriginal;
	JUMP jumpAnalyze;
	
	newJump(&jumpOriginal);
	jumpOriginal.intermediates[0]=piece;
	jumpOriginal.origin = piece;
	jumpAnalyze = jumpOriginal;
	
		
	
	for (jumpLoop;jumpLoop <= jumpLoopEnd; jumpLoop++) {
		
		(*game).jumps[jumpLoop].endOfJump = 0;
		
		while (!(*game).jumps[jumpLoop].endOfJump) {
			
		jumpGood = 0;
			
		if (jumpNorthWest(game, &jumpAnalyze)){
			
			
			if (jumpGood){
				jumpLoopEnd++;
				(*game).jumps[jumpLoopEnd] = jumpAnalyze;

			}else{
				(*game).jumps[jumpLoop] = jumpAnalyze;
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
		if (jumpNorthEast(game, &jumpAnalyze)){
			
			
			if (jumpGood){
				jumpLoopEnd++;
				(*game).jumps[jumpLoopEnd] = jumpAnalyze;
				
			}else{
				(*game).jumps[jumpLoop] = jumpAnalyze;
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
		if (jumpSouthWest(game, &jumpAnalyze)){
									
			if (jumpGood){
				jumpLoopEnd++;
				(*game).jumps[jumpLoopEnd] = jumpAnalyze;
				
			}else{
				(*game).jumps[jumpLoop] = jumpAnalyze;
			
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
		if (jumpSouthEast(game, &jumpAnalyze)){				
			
			if (jumpGood){
				jumpLoopEnd++;
				(*game).jumps[jumpLoopEnd] = jumpAnalyze;
				
			}else{
				(*game).jumps[jumpLoop] = jumpAnalyze;
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
			
		if (jumpGood == 0){
			if (jumpFound) {
				(*game).mjCount++;
				(*game).canJ = 1;
			}
			(*game).jumps[jumpLoop].endOfJump = 1;


						
		}else {
			jumpOriginal = (*game).jumps[jumpLoop];
			jumpAnalyze = jumpOriginal;
		}
			

			
			
		}
		
	}
	

};




void findJumpersForGame(PGAME game){
	
	int i;
	
	if ((*game).turn=='w'){

				
		piecesInGameForActivePlayer(game);
		
		for (i=0;i<(*game).whitePieces.piecesCount;i++){
			
						
			(*game).whitePieces.positionsBitboard[i];
			findJumpsForPiece(game, (*game).whitePieces.positionsBitboard[i]);
		};
		
	
	}
	if ((*game).turn=='b'){
		
		piecesInGameForActivePlayer(game);

		
		for (i=0;i<(*game).blackPieces.piecesCount;i++){
		
			
			(*game).blackPieces.positionsBitboard[i];
			findJumpsForPiece(game, (*game).blackPieces.positionsBitboard[i]);
				
		};
			
	}
	
};
			
			
void newJump(PJUMP jump){
	memset(jump, 0, sizeof(*jump));
}