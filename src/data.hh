/***************************************************************************
                          data.h  -  description
 
                             -------------------
 
    begin                : Mon Jun 21 00:55:10 CEST 1999
 
    copyright            : (C) 1999 by Mads Bondo Dydensborg
                           (Parts may be (C) ECC)
 
    email                : madsdyd@challenge.dk
 
 ***************************************************************************/
 
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *

***************************************************************************/
#ifndef __DATA_HH__
#define __DATA_HH__

/** Include common types */
#include "types.hh"
#include <SDL/SDL.h>

/** Xarman data file
    Ported to linux g++ by Mads Dydensborg <madsdyd@challenge.dk> 19990604
    Ported to SDL by Mads Dydensborg <madsdyd@challenge.dk> 20020902
*/

bool data_init();

extern SDL_Surface * LAND;
extern SDL_Surface * LAND1;
extern SDL_Surface * LAND2;
extern SDL_Surface * LAND3;

extern SDL_Surface * MINE;

/** Red player */
extern SDL_Surface * RD1F1;
extern SDL_Surface * RD1F2;
extern SDL_Surface * RD1F3;

extern SDL_Surface * RD2F1;
extern SDL_Surface * RD2F2;
extern SDL_Surface * RD2F3;

extern SDL_Surface * RD3F1;
extern SDL_Surface * RD3F2;
extern SDL_Surface * RD3F3;

extern SDL_Surface * RD4F1;
extern SDL_Surface * RD4F2;
extern SDL_Surface * RD4F3;

extern SDL_Surface * RSCAN1;
extern SDL_Surface * RSCAN2;
extern SDL_Surface * RSCAN3;

/** Blue player */
extern SDL_Surface * BD1F1;
extern SDL_Surface * BD1F2;
extern SDL_Surface * BD1F3;

extern SDL_Surface * BD2F1;
extern SDL_Surface * BD2F2;
extern SDL_Surface * BD2F3;

extern SDL_Surface * BD3F1;
extern SDL_Surface * BD3F2;
extern SDL_Surface * BD3F3;

extern SDL_Surface * BD4F1;
extern SDL_Surface * BD4F2;
extern SDL_Surface * BD4F3;

extern SDL_Surface * BSCAN1;
extern SDL_Surface * BSCAN2;
extern SDL_Surface * BSCAN3;

/** Number (16x16 tiles) */
extern SDL_Surface * N1;
extern SDL_Surface * N2;
extern SDL_Surface * N3;
extern SDL_Surface * N4;
extern SDL_Surface * N5;
extern SDL_Surface * N6;
extern SDL_Surface * N7;
extern SDL_Surface * N8;

/** Various */
extern SDL_Surface * ICON[19];
// extern SDL_Surface * LETTER[27];
extern SDL_Surface * REDDOT;
extern SDL_Surface * BLUEDOT;
extern SDL_Surface * MENU;
extern SDL_Surface * MENU2;
extern SDL_Surface * REDSIDE;
extern SDL_Surface * BLUESIDE;
extern SDL_Surface * REDKEYS;
extern SDL_Surface * BLUEKEYS;
extern SDL_Surface * CHECK;
extern SDL_Surface * CHECK2;

/** Text function contants */
extern const byte text1[];
extern const byte text2[];
extern const byte text3[];
extern const byte text4[];
extern const byte text5[];
#endif
