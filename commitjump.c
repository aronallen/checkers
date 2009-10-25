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


void makeJump(int jumpNumber, PGAME game){
	
	if (jumpNumber < 0) {
		jumpNumber = 0;
	}
	
	if ((*game).turn == 'w'){
	
		(*game).black = (*game).black & ~(*game).jumps[jumpNumber].removePieces;
		(*game).white = (*game).white ^ ((*game).jumps[jumpNumber].intermediates[0] | (*game).jumps[jumpNumber].intermediatePosistions[(*game).jumps[jumpNumber].intermediates]);
	
	}

	if ((*game).turn == 'b'){
	
		(*game).white = (*game).white & ~(*game).jumps[jumpNumber].removePieces;
		(*game).black = (*game).black ^ ((*game).jumps[jumpNumber].intermediates[0] | (*game).jumps[jumpNumber].intermediatePosistions[(*game).jumps[jumpNumber].intermediates]);	
	
	}
	(*game).kings = (*game).kings & ~(*game).jumps[jumpNumber].removePieces;
	
	if (((*game).jumps[jumpNumber].intermediates[0] & (*game).white) || ((*game).jumps[jumpNumber].intermediates[0] & (*game).black) ) {
		(*game).kings = (*game).kings ^ ((*game).jumps[jumpNumber].intermediates[0] | (*game).jumps[jumpNumber].intermediatePosistions[(*game).jumps[jumpNumber].intermediates]);	
	}
	


}