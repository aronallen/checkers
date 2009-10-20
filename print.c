/*
 *  print.c
 *  hello
 *
 *  Created by Aron Allen on 30/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdio.h>
#include "main.h"
#include "print.h"
#include "bitops.h"
#include "definitions.h"






void printGame (struct GAME *game){

	printf("\n");
	int i;
	int a = 0;
	int b = 0;
	int row = 0;
	printf("%d%d|",a,b);
	for(i=0;i<32;i++){
		
		if (row == 0 || row % 2 == 0)
			printBlankSquare();
		

		printSquareWithPiece(pieceAtPosition(game, bitboardForRealPosition[i]));
		
		if (row % 2 == 1)
			printBlankSquare();
		
		if ((i+1)%4 == 0){
			b = b +4;
			if (b >= 10) {
				b = b -10;
				a = a + 1;
			}
			
			row++;
			printf("\n");
			
			if (a!=3)
				printf("%d%d|",a,b);
		}
	}
	printf("\n");	
	
}


void printBitboard (unsigned bitboard){
	
	printf("\n");
	int i;
	int a = 0;
	int b = 0;
	printf("%d%d|",a,b);
	for(i=0;i<32;i++){
		
		if (i == 0 || (i)%8==0)
			printf(" ");
		
		if (bitboard & bitboardForRealPosition[i])
			printf("1 ");
		else
			printf("0 ");
		
		
		if ((i+1)%4 == 0){
			b = b +4;
			if (b >= 10) {
				b = b -10;
				a = a + 1;
			}
			

			printf("\n");
			
			if (a!=3)
			printf("%d%d|",a,b);
		}
	}
		printf("\n");
}


void printSquareWithPiece(char piece) {

	printf ("[%c]",piece);
	return;
}

void printBlankSquare(){

	printf("   ");
	return;
}



