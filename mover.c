/*
 *  mover.c
 *  hello
 *
 *  Created by Aron Allen on 30/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "main.h"




BITBOARD moveNorthWest(PGAME game, BITBOARD piece){
	
	BITBOARD move = 0;
	
	if (bitsInBitboard(piece)!=1){
		printf("mover/moveNorthWest: passed bitboard (piece) contains more, or less, than one bit. bitcount:%d",bitsInBitboard(piece));
		return move;
	}

	if (piece & LEGAL_NORTH_MOVE & LEGAL_WEST_MOVE){

		if ((((*game).white & piece) || ((*game).black&piece&(*game).kings)) && (northWestRotate(piece) & (*game).notOccupied)){
			
			move = northWestRotate(piece);
		}
	
	}
	
	
	return move;

}

BITBOARD moveNorthEast(PGAME game, BITBOARD piece){
	
	BITBOARD move = 0x0;
	
	if (bitsInBitboard(piece)!=1){
		printf("mover/moveNorthEast: passed bitboard (piece) contains more, or less, than one bit. bitcount:%d",bitsInBitboard(piece));
		return 0;
	}
	
	if (piece & LEGAL_NORTH_MOVE & LEGAL_EAST_MOVE){
		
		if ((((*game).white & piece) || ((*game).black & (*game).kings & piece)) && (northEastRotate(piece) & (*game).notOccupied)){
			
			move = northEastRotate(piece);
		}
				
	}
	
	return move;
}
BITBOARD moveSouthWest(PGAME game, BITBOARD piece){
	BITBOARD move = 0x0;

	if (bitsInBitboard(piece)!=1){
		printf("mover/moveSouthWest: passed bitboard (piece) contains more, or less, than one bit. bitcount:%d",bitsInBitboard(piece));
		return 0;
	}
	
	if (piece & LEGAL_SOUTH_MOVE & LEGAL_WEST_MOVE){
		
		if ((((*game).black & piece) || ((*game).white & (*game).kings & piece)) && (southWestRotate(piece) & (*game).notOccupied)){
			
			move = southWestRotate(piece);
		}
	}
	
	return move;
}


BITBOARD moveSouthEast(PGAME game, BITBOARD piece){

	BITBOARD move = 0;
	
	if (bitsInBitboard(piece)!=1){
		printf("mover/moveSouthEast: passed bitboard (piece) contains more, or less, than one bit. bitcount:%d",bitsInBitboard(piece));
		return 0;
	}
	
	if (piece & LEGAL_SOUTH_MOVE & LEGAL_EAST_MOVE){
		
		if ((((*game).black & piece) || ((*game).white & (*game).kings & piece)) && (southEastRotate(piece) & (*game).notOccupied)){
			move = southEastRotate(piece);
		}
	}
	
	return move;
}

void findMoversForGame(PGAME game){
	
	int i;
	int a = 0;
	
	//find all movers for white
	if ((*game).turn=='w'){
		
		piecesInGameForActivePlayer(game);
		
		for (i=0;i<(*game).whitePieces.piecesCount;i++){
			if ((*game).white&(*game).whitePieces.positionsBitboard[i]){
				if (moveNorthWest(game, (*game).whitePieces.positionsBitboard[i])){
					(*game).mjs[a].intermediates[1] = (moveNorthWest(game, (*game).whitePieces.positionsBitboard[i]));
					(*game).mjs[a].intermediates[0] = (*game).whitePieces.positionsBitboard[i];
					a++;
				}
				
				if (moveNorthEast(game, (*game).whitePieces.positionsBitboard[i])){
					
					(*game).mjs[a].intermediates[1] = (moveNorthEast(game, (*game).whitePieces.positionsBitboard[i]));
					(*game).mjs[a].intermediates[0] = (*game).whitePieces.positionsBitboard[i];
					a++;
				}
			
			}
			
			if ((*game).white&(*game).kings&(*game).whitePieces.positionsBitboard[i]){
			
				if(moveSouthWest(game, (*game).whitePieces.positionsBitboard[i])){
					(*game).mjs[a].intermediates[1] = moveSouthWest(game, (*game).whitePieces.positionsBitboard[i]);
					(*game).mjs[a].intermediates[0] = (*game).whitePieces.positionsBitboard[i];
					a++;
					
				}
				if(moveSouthEast(game,(*game).whitePieces.positionsBitboard[i])){
					(*game).mjs[a].intermediates[1]= moveSouthEast(game,(*game).whitePieces.positionsBitboard[i]);
					(*game).mjs[a].intermediates[0] = (*game).whitePieces.positionsBitboard[i];
					a++;
				}
			

				
			}
		
		}
	}
	
	//find all movers for  black.
	if ((*game).turn=='b'){
		
		piecesInGameForActivePlayer(game);

		
		for (i=0;i<(*game).blackPieces.piecesCount;i++){
		
		
			if ((*game).black&(*game).kings&(*game).blackPieces.positionsBitboard[i]){
				if (moveNorthWest(game,(*game).blackPieces.positionsBitboard[i])){
					(*game).mjs[a].intermediates[1] = (moveNorthWest(game,(*game).blackPieces.positionsBitboard[i]));
					(*game).mjs[a].intermediates[0] = (*game).blackPieces.positionsBitboard[i];
					a++;
				}
				
				if (moveNorthEast(game,(*game).blackPieces.positionsBitboard[i])){
					(*game).mjs[a].intermediates[1] = (moveNorthEast(game,(*game).blackPieces.positionsBitboard[i]));
					(*game).mjs[a].intermediates[0] = (*game).blackPieces.positionsBitboard[i];
					a++;
				}
				
			}
			
			if ((*game).black&(*game).blackPieces.positionsBitboard[i]){
				
				if(moveSouthWest(game,(*game).blackPieces.positionsBitboard[i])){
					(*game).mjs[a].intermediates[1] = moveSouthWest(game,(*game).blackPieces.positionsBitboard[i]);
					(*game).mjs[a].intermediates[0] = (*game).blackPieces.positionsBitboard[i];
					a++;
				}	
				if(moveSouthEast(game,(*game).blackPieces.positionsBitboard[i])){
					(*game).mjs[a].intermediates[1]= moveSouthEast(game,(*game).blackPieces.positionsBitboard[i]);
					(*game).mjs[a].intermediates[0] = (*game).blackPieces.positionsBitboard[i];
					a++;
				}
				

				
			}
			
		}
		}
	
	if (a >= MAX_MOVES) {
		printf("move stack exceeded, panic!\n");
	}
	
	if ((*game).turn != 'w' && (*game).turn !='b') {
		printf("ERROR ERROR ERROR wrong player, %c\n", (*game).turn );
	}
	
	(*game).mjCount = a;
	return;
	}
