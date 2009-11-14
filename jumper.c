/*
 *  jumper.c
 *  hello
 *
 *  Created by Aron Allen on 31/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "main.h"



int jumpNorthWest(PGAME game, PMJ jump){

	BITBOARD me;
	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_NORTH_MOVE & LEGAL_WEST_MOVE;
	BITBOARD origin = (*jump).intermediates[0];
	
	
	me = ((*game).turn == 'b') ?(*game).black :(*game).white;
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;



	
	
	//checks if the piece we are moving is either a black king, or white soldier.
	if (((*game).white & origin) || ((*game).black&(*game).kings&origin)){
				
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




int jumpNorthEast(PGAME game, PMJ jump){

	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_NORTH_MOVE & LEGAL_EAST_MOVE;
	BITBOARD origin = (*jump).intermediates[0];
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;
	
	//checks if the piece we are moving is either a black king, or white soldier.
	if (((*game).white & origin) || ((*game).black&(*game).kings&origin)){
		
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



int jumpSouthWest(PGAME game, PMJ jump){
	
	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_SOUTH_MOVE & LEGAL_WEST_MOVE;
	BITBOARD origin = (*jump).intermediates[0];
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;
	
	
	if (((*game).black & origin || ((*game).white&(*game).kings & origin))){
		
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


int jumpSouthEast(PGAME game, PMJ jump){



	BITBOARD enemy;
	BITBOARD position;
	BITBOARD legalMove = LEGAL_SOUTH_MOVE & LEGAL_EAST_MOVE;
	BITBOARD origin = (*jump).intermediates[0];
	
	enemy = ((*game).turn == 'w') ?(*game).black :(*game).white;
	position = (*jump).intermediates[(*jump).intermediatePosistions];
	enemy = enemy&~(*jump).removePieces;
	
	if (((*game).black & origin) || ((*game).white&(*game).kings&origin)){
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
	
	MJ jumpOriginal;
	MJ jumpAnalyze;
	
	newMJ(&jumpOriginal);
	jumpOriginal.intermediates[0] = piece;
	jumpAnalyze = jumpOriginal;
	
		
	
	for (jumpLoop;jumpLoop <= jumpLoopEnd; jumpLoop++) {
		
		(*game).mjs[jumpLoop].endOfJump = 0;
		
		while (!(*game).mjs[jumpLoop].endOfJump) {
			
		jumpGood = 0;
			
		if (jumpNorthWest(game, &jumpAnalyze)){
			
			
			if (jumpGood){
				jumpLoopEnd++;
				(*game).mjs[jumpLoopEnd] = jumpAnalyze;

			}else{
				(*game).mjs[jumpLoop] = jumpAnalyze;
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
		if (jumpNorthEast(game, &jumpAnalyze)){
			
			
			if (jumpGood){
				jumpLoopEnd++;
				(*game).mjs[jumpLoopEnd] = jumpAnalyze;
				
			}else{
				(*game).mjs[jumpLoop] = jumpAnalyze;
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
		if (jumpSouthWest(game, &jumpAnalyze)){
									
			if (jumpGood){
				jumpLoopEnd++;
				(*game).mjs[jumpLoopEnd] = jumpAnalyze;
				
			}else{
				(*game).mjs[jumpLoop] = jumpAnalyze;
			
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
		if (jumpSouthEast(game, &jumpAnalyze)){				
			
			if (jumpGood){
				jumpLoopEnd++;
				(*game).mjs[jumpLoopEnd] = jumpAnalyze;
				
			}else{
				(*game).mjs[jumpLoop] = jumpAnalyze;
			}
			jumpFound++;
			jumpGood++;
			jumpAnalyze = jumpOriginal;
		}
			
		if (jumpGood == 0){
			if (jumpFound) {
				(*game).mjCount++;
				(*game).canJ = 1;
				if ((*game).mjs[jumpLoop].intermediatePosistions >= MAX_INTERMEDIATES) {
					printf("More intermediates found than jumpstack allows, PANIC!\n");
				}
			}
			(*game).mjs[jumpLoop].endOfJump = 1;


						
		}else {
			jumpOriginal = (*game).mjs[jumpLoop];
			jumpAnalyze = jumpOriginal;
		}
			

			
			
		}
		
	}
	

};




void findJumpersForGame(PGAME game){
	
	int i;

	
	if ((*game).turn != 'w' && (*game).turn !='b') {
		printf("ERROR ERROR ERROR wrong player, %c\n", (*game).turn );
	}
	
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
	
	if ((*game).mjCount >= MAX_MOVES) {
		printf("jump stack exceeded, panic!\n");
	}
	
};
			
			
void newMJ(PMJ jump){
	memset(jump, 0, sizeof(*jump));
}