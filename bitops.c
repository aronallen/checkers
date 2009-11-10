/*
 *  bitops.c
 *  hello
 *
 *  Created by Aron Allen on 30/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "main.h"

//Bit Rotations, single bits only!
BITBOARD northWestRotate(BITBOARD bitboard){
	
	if (bitsInBitboard(bitboard)!=1){
	//	printf("\nbitops/northWestRotate: passed bitboard contains more or less than one bit, bitcount:%d\n",bitsInBitboard(bitboard));
		return 32;
	}
	
	
	if (realPositionForBitboard(bitboard) == 16 || realPositionForBitboard(bitboard) == 13 || realPositionForBitboard(bitboard) == 9 || realPositionForBitboard(bitboard) == 6)
		return bitboard >> 25;
	else
		return bitboard << 7;

}
BITBOARD northEastRotate(BITBOARD bitboard){
	
	if (bitsInBitboard(bitboard)!=1){
	//	printf("\nbitops/northEastRotate: passed bitboard contains more or less than one bit, bitcount:%d\n",bitsInBitboard(bitboard));
		return 32;
	}
	
	return bitboard<<1;

}
BITBOARD southEastRotate(BITBOARD bitboard){
	
	if (bitsInBitboard(bitboard)!=1){
	//	printf("\nbitops/southEastRotate: passed bitboard contains more or less than one bit, bitcount:%d\n",bitsInBitboard(bitboard));
		return 32;
	}
	
	if (realPositionForBitboard(bitboard) == 12 || realPositionForBitboard(bitboard) == 8 || realPositionForBitboard(bitboard) == 5 || realPositionForBitboard(bitboard) == 1)
		return bitboard << 25;
	else
		return bitboard >> 7;

}
BITBOARD southWestRotate(BITBOARD bitboard){
	if (bitsInBitboard(bitboard)!=1){
	//	printf("\nbitops/southWestRotate: passed bitboard contains more or less than one bit, bitcount:%d\n",bitsInBitboard(bitboard));
		return 32;
	}
	
	return bitboard>>1;
}


//Bit counting.
int bitsInBitboard(BITBOARD bitboard) {
	
	int i;
	int bitCount = 0;
	
	for	(i=0;i<32;i++){

		if (bitboardForRealPosition[i]&bitboard)
			bitCount++;
			
	}
	
	return bitCount;

}

//!!Only for 1-bit bitboads, opposite of bitboardForRealPosition[i].
int realPositionForBitboard(BITBOARD bitboard){
	int i;
	if (bitsInBitboard(bitboard)!=1){
	//	printf("\nbitops/realPositionForBitboard: passed bitboard contains more or less than one bit, bitcount:%d\n",bitsInBitboard(bitboard));
		return 32;
	}
		
	for (i=0; i<32; i++) {
		if (bitboard == bitboardForRealPosition[i])
			return i;
	}
	return 32;
}

char pieceAtPosition(PGAME game, BITBOARD position){
	
	if (bitsInBitboard(position) == 1){
		
		
		if ((*game).white & (*game).kings & position)
			return 'W';
		if ((*game).black & (*game).kings & position)
			return 'B';
		if ((*game).black & position) 
			return 'b';
		if ((*game).white & position)
			return 'w';
		return ' ';
	}
	
	return 'x';
}