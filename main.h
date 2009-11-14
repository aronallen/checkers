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


//DEFINES
#define BITBOARD unsigned
#define MAX_MOVES 42
#define MAX_MOVES_GAME 300
#define MAX_INTERMEDIATES 7

static const BITBOARD LEGAL_NORTH_MOVE = ~(0x82000820);
static const BITBOARD LEGAL_SOUTH_MOVE = ~(0x00041041);
static const BITBOARD LEGAL_EAST_MOVE  = ~(0x02020202);
static const BITBOARD LEGAL_WEST_MOVE  = ~(0x04040404);

//BitMaskArray used for locating bits on BITBOARD
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





//PIECES struct, used for containing a count of all pieces for a specific player, including their real and BITBOARD position.
typedef struct _PIECES {

	int piecesCount;
	int positions[12];
	BITBOARD positionsBitboard[12];
	int jumpsForPiece[12];

}PIECES, * PPIECES;


//MJ struct, used for storing jumps and moves.
typedef struct _MJ {
	BITBOARD intermediates[MAX_INTERMEDIATES];
	BITBOARD removePieces;
	int intermediatePosistions;
	int endOfJump;
}MJ, * PMJ;

//GAME struct, containing all pieces, BITBOARDS
typedef struct _GAME {
	
	//a BITBOARD with a bit set for all unocupied squares.
	BITBOARD notOccupied;
	
	//a BITBOARD containing all kings, & with a color, to get all kings for that color.
	BITBOARD kings;
	
	//a BITBOARD containing all black pieces.
	BITBOARD black;
	
	//a BITBOARD containing all white pieces.	
	BITBOARD white;
	
	//Turn indicator, b for black, w for white.
	char turn;
	
	//total available move count or jump count
	int mjCount;
	
	int canJ;
	
	float score;
		

	//total available jump count	
	//Array of all possible JUMPs
	MJ mjs[MAX_MOVES];
	
	//Array of all possible MOVEs
	
	//PIECES struct containing more detailed information of white pieces.
	PIECES whitePieces;

	//PIECES struct containing more detailed information of black pieces.
	PIECES blackPieces;
	
	int parrentGame;

}GAME, *PGAME;



typedef struct _LIGHTGAME {
	
	//a BITBOARD containing all black pieces.
	BITBOARD black;
	
	//a BITBOARD containing all white pieces.	
	BITBOARD white;

	//a BITBOARD containing all kings.	
	BITBOARD kings;
		
	char turn;
	
	float score;
	
	int parrentGame;

		
}LIGHTGAME, *PLIGHTGAME;

typedef struct _GAMESESSION {
	
	int moveCount;
	char winner;
	
	int movesAllocated;
	
	PLIGHTGAME moves;
	
	
}GAMESESSION, * PGAMESESSION;

typedef struct _ALPHABETA{
	
	PLIGHTGAME moves;
	
	int allocMove;
	int moveCount;
	
	
}ALPHABETA, *PALPHABETA;
//Game Functions

//Creates a new game, with a default setup.
GAME newGame();

//Creates a new game, with a specified setup.
GAME game(BITBOARD black, BITBOARD white, BITBOARD kings,char turn);

//changes the turn to the opposite player.
void changeTurn(PGAME game);

//runs through the GAME struct, updating the data throughout the struct, to correspond to recent changes, should be run after every move, and jump.
void cleanUp (PGAME game);

//returns 0 or 1 depending on selection.
int isPieceFriendly (GAME game, BITBOARD position);

void addMoveToEndGameDatabase (PGAMESESSION db, PGAME theGame, int gameNumber);
