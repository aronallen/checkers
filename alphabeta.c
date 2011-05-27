//
//  alphabeta.c
//  hello
//
//  Created by Aron Allen on 18/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "alphabeta.h"




int bestMJ(PGAME orgGame, PGAME game, int d, int f){

    int i;
    int bestIndex = 0;
    int bestIndexScore = 0;
    
    
    
    for(i = 0; i < game->mjCount && d > 0; i++){
        
            
        GAME newGame;
        
        memcpy(&newGame, game, sizeof(GAME));
        
        if (newGame.canJ) {
            makeJump(i, &newGame);
        }else{
            makeMove(i, &newGame);
        }
        
        changeTurn(&newGame);
        cleanUp(&newGame);
        
        findJumpersForGame(&newGame);
        
        if (!newGame.canJ) {
            findMoversForGame(&newGame);
        }
        
        
        int tempScore = scoreGames(orgGame, &newGame);
       
        if(tempScore > bestIndexScore){
            bestIndexScore = tempScore;
            bestIndex = i;
            f++;

        }else{
            
            if(tempScore == bestIndexScore){
                if(rand()%2 == 0){
                    bestIndexScore = tempScore;
                    bestIndex = i;
                }
                f++;

            }else{
                f--;

            }
            
        }
        
        
        
        if(f > 0 && d > 0){
            bestMJ(orgGame, &newGame, d-1, f);
        }
        
        
    }

    return bestIndex;
}

int bestMJalt(PGAME orgGame, PGAME game, int d, int f, int returnScore){
    
    int i;
    int bestIndex = 0;
    int bestIndexScore = 0;
    
    
    
    for(i = 0; i < game->mjCount && d > 0; i++){
        
        
        GAME newGame;
        
        memcpy(&newGame, game, sizeof(GAME));
        
        if (newGame.canJ) {
            makeJump(i, &newGame);
        }else{
            makeMove(i, &newGame);
        }
        
        changeTurn(&newGame);
        cleanUp(&newGame);
        
        findJumpersForGame(&newGame);
        
        if (!newGame.canJ) {
            findMoversForGame(&newGame);
        }
        
        
        int tempScore;
                
        if(f > 0 && d > 0){
            tempScore = bestMJalt(orgGame, &newGame, d-1, f, 1);
        }        
        
        if(tempScore > bestIndexScore){
            bestIndexScore = tempScore;
            bestIndex = i;
            
        }else{
            
            if(tempScore == bestIndexScore && returnScore == 0){
                if(rand()%2 == 0){
                    bestIndexScore = tempScore;
                    bestIndex = i;
                }                
            }
            
        }

        
        
    }
    
    
    if(game->turn != orgGame->turn)
    bestIndexScore = -bestIndexScore;
    
    if(returnScore)
    return bestIndexScore;
    
    return bestIndex;
}



GAME heavyGameFromLightGame(LIGHTGAME lg){
	
    GAME hg;
    
	hg.black = lg.black;
	hg.white = lg.white;
	hg.kings = lg.kings;
	hg.turn = lg.turn;
	hg.score = lg.score;
	hg.notOccupied = ~(lg.black|lg.white);
	hg.canJ = 0;
	hg.mjCount = 0;
	hg.blackPieces.piecesCount = bitsInBitboard(hg.black);
	hg.whitePieces.piecesCount = bitsInBitboard(hg.white);
	piecesInGameForActivePlayer(&hg);
	
	return hg;
}

LIGHTGAME lightGameFromHeavyGame(GAME hg){
    
	LIGHTGAME lg;
	
	lg.black = hg.black;
	lg.white = hg.white;
	lg.kings = hg.kings;
	lg.turn = hg.turn;
	lg.score = hg.score;
    
	return lg;
}

int scoreGames(PGAME o, PGAME n){
    
    int score = 0;
    
    
    if(n->turn == 'b'){
        score += bitsInBitboard(n->black);
        score += bitsInBitboard(n->black&LEGAL_NORTH_MOVE);
        score += bitsInBitboard(n->black&(LEGAL_EAST_MOVE|LEGAL_WEST_MOVE));
        score += bitsInBitboard(n->black&n->kings) * 5;


        
    }else{
        score += bitsInBitboard(n->white);
        score += bitsInBitboard(n->white&LEGAL_SOUTH_MOVE);
        score += bitsInBitboard(n->white&(LEGAL_EAST_MOVE|LEGAL_WEST_MOVE));
        score += bitsInBitboard(n->white&n->kings) * 5;


    }
    
    
    
    return score;
    
}
