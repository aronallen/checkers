/*
 *  commitjump.c
 *  hello
 *
 *  Created by Aron Allen on 25/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "main.h"


void makeJump(int jumpNumber, PGAME game){
	
	if ((*game).mjCount == 0 || jumpNumber > (*game).mjCount){
		printf("error, jumpCount: %d passedJump: %d, making random jump instead\n",(*game).mjCount,jumpNumber);
		if ((*game).mjCount) {
			jumpNumber = rand()%(*game).mjCount;
		}else {
			printf("no jumps, something is really wrong\n");
			return;
		}

	}
	
	if ((*game).turn == 'w'){
		
		//Remove King if any
		if ((*game).mjs[jumpNumber].removePieces & (*game).kings & (*game).black){
			(*game).kings = (*game).kings & ~(*game).mjs[jumpNumber].removePieces;
		}
		//Remove Enemy
		(*game).black = (*game).black & ~(*game).mjs[jumpNumber].removePieces;
		
		//Move King, if any
		if ((*game).mjs[jumpNumber].intermediates[0] & (*game).kings & (*game).white){		
			(*game).kings = (*game).kings ^ ((*game).mjs[jumpNumber].intermediates[0] | (*game).mjs[jumpNumber].intermediatePosistions[(*game).mjs[jumpNumber].intermediates]);	
		}
		//Move Piece		
		(*game).white = (*game).white ^ ((*game).mjs[jumpNumber].intermediates[0] | (*game).mjs[jumpNumber].intermediatePosistions[(*game).mjs[jumpNumber].intermediates]);	
		
		
	}

	if ((*game).turn == 'b'){
		
		//Remove King if any
		if ((*game).mjs[jumpNumber].removePieces & (*game).kings & (*game).white){
			(*game).kings = (*game).kings & ~(*game).mjs[jumpNumber].removePieces;
		}
		//Remove Enemy
		(*game).white = (*game).white & ~(*game).mjs[jumpNumber].removePieces;
		
		//Move King, if any
		if ((*game).mjs[jumpNumber].intermediates[0] & (*game).kings & (*game).black){		
			(*game).kings = (*game).kings ^ ((*game).mjs[jumpNumber].intermediates[0] | (*game).mjs[jumpNumber].intermediatePosistions[(*game).mjs[jumpNumber].intermediates]);	
		}
		//Move Piece		
		(*game).black = (*game).black ^ ((*game).mjs[jumpNumber].intermediates[0] | (*game).mjs[jumpNumber].intermediatePosistions[(*game).mjs[jumpNumber].intermediates]);	
		
		
		}
	
	
	


}