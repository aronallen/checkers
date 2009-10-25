/*
 *  jumper.h
 *  hello
 *
 *  Created by Aron Allen on 31/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

int jumpNorthWest(PGAME game, PJUMP jump);
int jumpNorthEast(PGAME game, PJUMP jump);
int jumpSouthWest(PGAME game, PJUMP jump);
int jumpSouthEast(PGAME game, PJUMP jump);

void findJumpsForPiece(PGAME game, BITBOARD piece);

void findJumpersForGame(PGAME game);
void newJump(PJUMP jump);