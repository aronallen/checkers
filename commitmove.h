/*
 *  commitmove.h
 *  hello
 *
 *  Created by Aron Allen on 31/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

struct GAME movePieceInGame(int origin, int destination, struct GAME game);

void makeMove(int moveNumber, struct GAME *game);