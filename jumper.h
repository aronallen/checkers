/*
 *  jumper.h
 *  hello
 *
 *  Created by Aron Allen on 31/7/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

void jumpNorthWest(struct GAME *game, struct JUMP *jump);
void jumpNorthEast(struct GAME *game, struct JUMP *jump);
void jumpSouthWest(struct GAME *game, struct JUMP *jump);
void jumpSouthEast(struct GAME *game, struct JUMP *jump);


void findJumpersForGame(struct GAME *game);
void newJump(struct JUMP *jump);