/*
 *  commitjump.c
 *  hello
 *
 *  Created by Aron Allen on 25/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "main.h"
#include "commitjump.h"
#include "positions.h"
#include "print.h"


void makeJump(int jumpNumber, PGAME game){
	
	
	//Remove Kings	

	
	if ((*game).turn == 'w'){
	
		//Remove Enemy
		(*game).black = (*game).black & ~(*game).jumps[jumpNumber].removePieces;
		
		
		//Move Kings BITBOARD if piece is king
		if ((*game).jumps[jumpNumber].intermediates[0] & (*game).kings & (*game).white){
			(*game).kings = (*game).kings & ~(*game).jumps[jumpNumber].removePieces;
			(*game).kings = (*game).kings ^ ((*game).jumps[jumpNumber].intermediates[0] | (*game).jumps[jumpNumber].intermediatePosistions[(*game).jumps[jumpNumber].intermediates]);	
		}
		
		//Move Piece
		(*game).white = (*game).white ^ ((*game).jumps[jumpNumber].intermediates[0] | (*game).jumps[jumpNumber].intermediatePosistions[(*game).jumps[jumpNumber].intermediates]);
		
		
	}

	if ((*game).turn == 'b'){
	
		//Remove Enemy
		(*game).white = (*game).white & ~(*game).jumps[jumpNumber].removePieces;
		
		//Move Kings BITBOARD if piece is king
		if ((*game).jumps[jumpNumber].intermediates[0] & (*game).kings & (*game).black){
			(*game).kings = (*game).kings & ~(*game).jumps[jumpNumber].removePieces;
			(*game).kings = (*game).kings ^ ((*game).jumps[jumpNumber].intermediates[0] | (*game).jumps[jumpNumber].intermediatePosistions[(*game).jumps[jumpNumber].intermediates]);	
		}
		//Move Piece		
		(*game).black = (*game).black ^ ((*game).jumps[jumpNumber].intermediates[0] | (*game).jumps[jumpNumber].intermediatePosistions[(*game).jumps[jumpNumber].intermediates]);	
		
		
		}
	
	
	


}