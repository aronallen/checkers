/*
 *  mover.h
 *  hello
 *
 *  Created by Aron Allen on 30/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

static const BITBOARD LEGAL_NORTH_MOVE = ~(0x82000820);
static const BITBOARD LEGAL_SOUTH_MOVE = ~(0x00041041);
static const BITBOARD LEGAL_EAST_MOVE  = ~(0x02020202);
static const BITBOARD LEGAL_WEST_MOVE  = ~(0x04040404);

BITBOARD moveNorthWest(PGAME game, BITBOARD piece);
BITBOARD moveNorthEast(PGAME game, BITBOARD piece);
BITBOARD moveSouthWest(PGAME game, BITBOARD piece);
BITBOARD moveSouthEast(PGAME game, BITBOARD piece);

void findMoversForGame(PGAME game);