/*
 *  main.h
 *  hello
 *
 *  Created by Aron Allen on 30/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

//Definitions
/*
 ###################################
   11  05  31  25     00  01  02  03 
 10  04  30  24     04  05  06  07 
   03  29  23  17	  08  09  10  11
 02  28  22  16     12  13  14  15
   27  21  15  09     16  17  18  19
 26  20  14  08     20  21  22  23
   19  13  07  01     24  25  26  27
 18  12  06  00     28  29  30  31
 ################################### 
 */

#define BITBOARD unsigned
#define MAX_MOVES 20
#define MAX_JUMPS 20

//BitMaskArray
static const BITBOARD bitboardForRealPosition[32] = {
0x00000800,0x00000020,0x80000000,0x02000000,
0x00000400,0x00000010,0x40000000,0x01000000,
0x00000008,0x20000000,0x00800000,0x00020000,
0x00000004,0x10000000,0x00400000,0x00010000,
0x08000000,0x00200000,0x00008000,0x00000200,
0x04000000,0x00100000,0x00004000,0x00000100,
0x00080000,0x00002000,0x00000080,0x00000002,
0x00040000,0x00001000,0x00000040,0x00000001
};


struct JUMP_DIRECTIONS {

	int northWest;
	int northEast;
	int southWest;
	int southEast;

};

struct PIECES {

	int piecesCount;
	int positions[12];
	BITBOARD positionsBitboard[12];

};

struct MOVE {
	BITBOARD origin;
	BITBOARD destination;
};

struct JUMP {
	BITBOARD origin;
	BITBOARD intermediates[12];
	struct JUMP_DIRECTIONS direcetionsForPositions[32];
	
	BITBOARD removePieces;
	int intermediatePosistions;
	int endOfJump;
};


struct GAME {
	BITBOARD notOccupied;
	BITBOARD kings;
	BITBOARD black;
	BITBOARD white;
	char turn;
	int moveCount;
	int jumpCount;
	struct JUMP jumps[MAX_JUMPS];
	struct MOVE moves[MAX_MOVES];
	struct PIECES whitePieces;
	struct PIECES blackPieces;
	int staleMateCount;
};

//Game Functions

struct GAME newGame();
struct GAME game(BITBOARD black, BITBOARD white, BITBOARD kings,char turn);
void changeTurn(struct GAME *game);
void cleanUp (struct GAME *game);

int isPieceFriendly (struct GAME game, BITBOARD position);
struct GAME staleMateChecker (struct GAME oldGame, struct GAME newGame);