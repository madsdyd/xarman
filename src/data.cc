/***************************************************************************
                          data.c  -  description
 
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
#include "data.hh"
/** Xarman data file
    Ported to linux g++ by Mads Dydensborg <madsdyd@challenge.dk> 19990604
    Ported to SDL by Mads Dydensborg <madsdyd@challenge.dk> 20020902
*/

#include "surfacemanager.hh"

/* **********************************************************************
 * Load all the data
 * *********************************************************************/

bool data_init() {
  LAND = SurfaceManager->RequireRessource("graphics/LAND.png");
  LAND1 = SurfaceManager->RequireRessource("graphics/LAND1.png");
  LAND2 = SurfaceManager->RequireRessource("graphics/LAND2.png");
  LAND3 = SurfaceManager->RequireRessource("graphics/LAND3.png");

  MINE = SurfaceManager->RequireRessource("graphics/MINE.png");

/** Red player */
  RD1F1 = SurfaceManager->RequireRessource("graphics/RD1F1.png");
  RD1F2 = SurfaceManager->RequireRessource("graphics/RD1F2.png");
  RD1F3 = SurfaceManager->RequireRessource("graphics/RD1F3.png");

  RD2F1 = SurfaceManager->RequireRessource("graphics/RD2F1.png");
  RD2F2 = SurfaceManager->RequireRessource("graphics/RD2F2.png");
  RD2F3 = SurfaceManager->RequireRessource("graphics/RD2F3.png");

  RD3F1 = SurfaceManager->RequireRessource("graphics/RD3F1.png");
  RD3F2 = SurfaceManager->RequireRessource("graphics/RD3F2.png");
  RD3F3 = SurfaceManager->RequireRessource("graphics/RD3F3.png");

  RD4F1 = SurfaceManager->RequireRessource("graphics/RD4F1.png");
  RD4F2 = SurfaceManager->RequireRessource("graphics/RD4F2.png");
  RD4F3 = SurfaceManager->RequireRessource("graphics/RD4F3.png");

  RSCAN1 = SurfaceManager->RequireRessource("graphics/RSCAN1.png");
  RSCAN2 = SurfaceManager->RequireRessource("graphics/RSCAN2.png");
  RSCAN3 = SurfaceManager->RequireRessource("graphics/RSCAN3.png");

/** Blue player */
  BD1F1 = SurfaceManager->RequireRessource("graphics/BD1F1.png");
  BD1F2 = SurfaceManager->RequireRessource("graphics/BD1F2.png");
  BD1F3 = SurfaceManager->RequireRessource("graphics/BD1F3.png");

  BD2F1 = SurfaceManager->RequireRessource("graphics/BD2F1.png");
  BD2F2 = SurfaceManager->RequireRessource("graphics/BD2F2.png");
  BD2F3 = SurfaceManager->RequireRessource("graphics/BD2F3.png");

  BD3F1 = SurfaceManager->RequireRessource("graphics/BD3F1.png");
  BD3F2 = SurfaceManager->RequireRessource("graphics/BD3F2.png");
  BD3F3 = SurfaceManager->RequireRessource("graphics/BD3F3.png");

  BD4F1 = SurfaceManager->RequireRessource("graphics/BD4F1.png");
  BD4F2 = SurfaceManager->RequireRessource("graphics/BD4F2.png");
  BD4F3 = SurfaceManager->RequireRessource("graphics/BD4F3.png");

  BSCAN1 = SurfaceManager->RequireRessource("graphics/BSCAN1.png");
  BSCAN2 = SurfaceManager->RequireRessource("graphics/BSCAN2.png");
  BSCAN3 = SurfaceManager->RequireRessource("graphics/BSCAN3.png");

/** Number (16x16 tiles) */
  N1 = SurfaceManager->RequireRessource("graphics/N1.png");
  N2 = SurfaceManager->RequireRessource("graphics/N2.png");
  N3 = SurfaceManager->RequireRessource("graphics/N3.png");
  N4 = SurfaceManager->RequireRessource("graphics/N4.png");
  N5 = SurfaceManager->RequireRessource("graphics/N5.png");
  N6 = SurfaceManager->RequireRessource("graphics/N6.png");
  N7 = SurfaceManager->RequireRessource("graphics/N7.png");
  N8 = SurfaceManager->RequireRessource("graphics/N8.png");

/** Various */
  int i;
  char ged[50];
  for (i = 0; i < 19; i++) {
    sprintf(ged, "graphics/ICON%i.png", i);
    // sprintf(ged, "graphics/ICON0.png");
    // cout << "Loading -" << ged << "-" << endl;
    ICON[i] = SurfaceManager->RequireRessource(ged); 
  }

// extern SDL_Surface * LETTER[27];
  REDDOT = SurfaceManager->RequireRessource("graphics/REDDOT.png");
  BLUEDOT = SurfaceManager->RequireRessource("graphics/BLUEDOT.png");
  MENU = SurfaceManager->RequireRessource("graphics/MENU.png");
  MENU2 = SurfaceManager->RequireRessource("graphics/MENU2.png");
  REDSIDE = SurfaceManager->RequireRessource("graphics/REDSIDE.png");
  BLUESIDE = SurfaceManager->RequireRessource("graphics/BLUESIDE.png");
  REDKEYS = SurfaceManager->RequireRessource("graphics/REDKEYS.png");
  BLUEKEYS = SurfaceManager->RequireRessource("graphics/BLUEKEYS.png");
  CHECK = SurfaceManager->RequireRessource("graphics/CHECK.png");
  CHECK2 = SurfaceManager->RequireRessource("graphics/CHECK2.png");

  return true;
}

/* **********************************************************************
 * And, here they are.
 * *********************************************************************/

SDL_Surface * LAND;
SDL_Surface * LAND1;
SDL_Surface * LAND2;
SDL_Surface * LAND3;

SDL_Surface * MINE;

/** Red player */
SDL_Surface * RD1F1;
SDL_Surface * RD1F2;
SDL_Surface * RD1F3;

SDL_Surface * RD2F1;
SDL_Surface * RD2F2;
SDL_Surface * RD2F3;

SDL_Surface * RD3F1;
SDL_Surface * RD3F2;
SDL_Surface * RD3F3;

SDL_Surface * RD4F1;
SDL_Surface * RD4F2;
SDL_Surface * RD4F3;

SDL_Surface * RSCAN1;
SDL_Surface * RSCAN2;
SDL_Surface * RSCAN3;

/** Blue player */
SDL_Surface * BD1F1;
SDL_Surface * BD1F2;
SDL_Surface * BD1F3;

SDL_Surface * BD2F1;
SDL_Surface * BD2F2;
SDL_Surface * BD2F3;

SDL_Surface * BD3F1;
SDL_Surface * BD3F2;
SDL_Surface * BD3F3;

SDL_Surface * BD4F1;
SDL_Surface * BD4F2;
SDL_Surface * BD4F3;

SDL_Surface * BSCAN1;
SDL_Surface * BSCAN2;
SDL_Surface * BSCAN3;

/** Number (16x16 tiles) */
SDL_Surface * N1;
SDL_Surface * N2;
SDL_Surface * N3;
SDL_Surface * N4;
SDL_Surface * N5;
SDL_Surface * N6;
SDL_Surface * N7;
SDL_Surface * N8;

/** Various */
SDL_Surface * ICON[19];
// SDL_Surface * LETTER[27];
SDL_Surface * REDDOT;
SDL_Surface * BLUEDOT;
SDL_Surface * MENU;
SDL_Surface * MENU2;
SDL_Surface * REDSIDE;
SDL_Surface * BLUESIDE;
SDL_Surface * REDKEYS;
SDL_Surface * BLUEKEYS;
SDL_Surface * CHECK;
SDL_Surface * CHECK2;

/* **********************************************************************
 * Some texts that goes onto the screen.
 * *********************************************************************/
const byte text1[] = {
12,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,13,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0, 8,2,13,0, 0 ,17,0,0,0, 0 ,17,0,0,17, 0 ,8,2,2,18, 0,1,
1,0, 1,0,1,0,  0 ,1,0,0,0,  0 ,1,0,0,1,   0 ,1,0,0,0,  0,1,
1,0, 3,2,6,13, 0 ,1,0,0,0,  0 ,1,0,0,1,   0 ,3,2,18,0, 0,1,
1,0, 1,0,0,1,  0 ,1,0,0,0,  0 ,1,0,0,1,   0 ,1,0,0,0,  0,1,
1,0, 7,2,2,14, 0 ,7,2,2,18, 0 ,11,2,2,14, 0 ,7,2,2,18, 0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0, 17,0,17,0,17, 0 ,16,4,18, 0 ,17,0,0,17, 0 ,12,2,2,18, 0,1,
1,0, 1,0,1,0,1,    0 ,0,1,0,   0 ,3,13,0,1,  0 ,1,0,0,0,   0,1,
1,0, 1,0,1,0,1,    0 ,0,1,0,   0 ,1,11,13,1, 0 ,11,2,2,13, 0,1,
1,0, 11,4,6,4,14,  0 ,0,1,0,   0 ,1,0,11,5,  0 ,0,0,0,1,   0,1,
1,0, 0,15,0,15,0,  0 ,16,6,18, 0 ,15,0,0,15, 0 ,16,2,2,14, 0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
11,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,14
};
const byte text2[] = {
12,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,13,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,0,0, 8,2,2,13,   0 ,8,2,2,18, 0 ,8,2,2,13, 0,0,0,0,1,
1,0,0,0, 1,0,0,1,    0 ,1,0,0,0,  0 ,1,0,0,1,  0,0,0,0,1,
1,0,0,0, 3,4,2,14,   0 ,3,2,18,0, 0 ,1,0,0,1,  0,0,0,0,1,
1,0,0,0, 1,11,13,0,  0 ,1,0,0,0,  0 ,1,0,0,1,  0,0,0,0,1,
1,0,0,0, 15,0,11,18, 0 ,7,2,2,18,  0 ,7,2,2,14, 0,0,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0, 17,0,17,0,17, 0 ,16,4,18, 0 ,17,0,0,17, 0 ,12,2,2,18, 0,1,
1,0, 1,0,1,0,1,    0 ,0,1,0,   0 ,3,13,0,1,  0 ,1,0,0,0,   0,1,
1,0, 1,0,1,0,1,    0 ,0,1,0,   0 ,1,11,13,1, 0 ,11,2,2,13, 0,1,
1,0, 11,4,6,4,14,  0 ,0,1,0,   0 ,1,0,11,5,  0 ,0,0,0,1,   0,1,
1,0, 0,15,0,15,0,  0 ,16,6,18, 0 ,15,0,0,15, 0 ,16,2,2,14, 0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
11,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,14
};

const byte text3[] = {
12,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,13,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0, 12,2,2,13, 0 ,12,2,2,13, 0 ,17,0,0,0,17, 0 ,8,2,2,18, 0,1,
1,0, 1,0,0,15,  0 ,1,0,0,1,   0 ,3,13,0,12,5, 0 ,1,0,0,0,  0,1,
1,0, 1,0,16,9,  0 ,3,2,2,5,   0 ,1,11,4,14,1, 0 ,3,2,18,0, 0,1,
1,0, 1,0,0,1,   0 ,1,0,0,1,   0 ,1,0,15,0,1,  0 ,1,0,0,0,  0,1,
1,0, 11,2,2,14, 0 ,15,0,0,15, 0 ,15,0,0,0,15, 0 ,7,2,2,18, 0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0, 12,2,2,13, 0 ,17,0,0,0,17,   0 ,8,2,2,18, 0 ,8,2,2,13, 0,1,
1,0, 1,0,0,1,   0 ,1,0,0,0,1,     0 ,1,0,0,0,  0 ,1,0,0,1,  0,1,
1,0, 1,0,0,1,   0 ,11,13,0,12,14, 0 ,3,2,18,0, 0 ,3,4,2,14, 0,1,
1,0, 1,0,0,1,   0 ,0,11,4,14,0,   0 ,1,0,0,0,  0 ,1,11,13,0,  0,1,
1,0, 11,2,2,14, 0 ,0,0,15,0,0,    0 ,7,2,2,18, 0 ,15,0,11,18, 0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
11,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,14
};


const byte text4[] = {
0,0,0,0,0,0,0,12,2,2,2,2,2,2,13, 0, 0,0,12,2,2,2,13,0,     0, 0,0,12,2,2,2,13,0,        0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,12,2,2,2,2,13,1, 0, 0,12,14,12,2,13,11,13, 0, 0,12,14,12,2,13,11,13,    0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,0,0,0,0,11,14, 0, 12,14,12,14,0,11,13,1, 0, 12,14,12,14,0,11,13,1,    0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,   0, 1,12,14,0,0,0,11,14,   0, 1,12,14,0,0,0,11,14,      0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,11,2,2,2,13,0,0, 0, 1,1,0,0,0,0,0,0,       0, 1,1,0,0,0,0,0,0,          0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,12,2,2,2,14,0,0, 0, 1,1,0,0,0,0,0,0,       0, 1,1,0,0,0,0,0,0,          0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,   0, 1,11,13,0,0,0,12,13,   0, 1,11,13,0,0,0,12,13,      0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,1,0,0,0,0,12,13, 0, 11,13,11,13,0,12,14,1, 0, 11,13,11,13,0,12,14,1,    0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,11,2,2,2,2,14,1, 0, 0,11,13,11,2,14,12,14, 0, 0,11,13,11,2,14,12,14,    0,0,0,0,0,0,0,
0,0,0,0,0,0,0,11,2,2,2,2,2,2,14, 0, 0,0,11,2,2,2,14,0,     0, 0,0,11,2,2,2,14,0,        0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
8,2,2,13,0, 8,2,2,13,0,  8,2,2,18,0, 12,2,2,18,0, 8,2,2,18,0, 17,0,0,17,0, 16,2,4,2,18,0,12,2,2,18,
1,0,0,1,0,  1,0,0,1,0,   1,0,0,0,0,  1,0,0,0,0,   1,0,0,0,0,  3,13,0,1,0,  0,0,1,0,0,0,  1,0,0,0,
3,2,2,14,0, 3,4,2,14,0, 3,2,18,0,0, 11,2,2,13,0, 3,2,18,0,0, 1,11,13,1,0, 0,0,1,0,0,0,   11,2,2,13,
1,0,0,0,0,  1,11,13,0,0, 1,0,0,0,0,  0,0,0,1,0,   1,0,0,0,0,  1,0,11,5,0,  0,0,1,0,0,0,  0,0,0,1,
15,0,0,0,0, 15,0,11,18,0,7,2,2,18,0, 16,2,2,14,0, 7,2,2,18,0, 15,0,0,15,0, 0,0,15,0,0,0, 16,2,2,14
};

const byte text5[] = {
12,13,0,0,0,0,0,0,12,13,     0, 0,0,12,2,2,13,0,0,       0, 12,2,2,2,2,13,0,0,
1,11,13,0,0,0,0,12,14,1,     0, 0,12,14,12,13,11,13,0,   0, 1,12,2,2,13,11,13,0,
11,13,11,13,0,0,12,14,12,14, 0, 12,14,12,14,11,13,11,13, 0, 1,1,0,0,11,13,11,13,
0,11,13,11,13,12,14,12,14,0, 0, 1,12,14,0,0,11,13,1,     0, 1,1,0,0,0,1,0,1,
0,0,11,13,11,14,12,14,0,0,   0, 1,1,0,0,0,0,1,1,         0, 1,11,2,2,2,14,12,14,
0,0,12,14,12,13,11,13,0,0,   0, 1,11,2,2,2,2,14,1,       0, 1,12,13,12,2,2,14,0,
0,12,14,12,14,11,13,11,13,0, 0, 1,12,2,2,2,2,13,1,       0, 1,1,1,11,13,0,0,0,
12,14,12,14,0,0,11,13,11,13, 0, 1,1,0,0,0,0,1,1,         0, 1,1,11,13,11,13,0,0,
1,12,14,0,0,0,0,11,13,1,     0, 1,1,0,0,0,0,1,1,         0, 1,1,0,11,13,11,13,0,
11,14,0,0,0,0,0,0,11,14,     0, 11,14,0,0,0,0,11,14,     0, 11,14,0,0,11,2,14,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
12,13,0,0,0,0,0,0,12,13,     0, 0,0,12,2,2,13,0,0,       0, 12,13,0,0,0,0,12,13,
1,11,13,0,0,0,0,12,14,1,     0, 0,12,14,12,13,11,13,0,   0, 1,1,0,0,0,0,1,1,
1,0,11,13,0,0,12,14,0,1,     0, 12,14,12,14,11,13,11,13, 0, 1,11,13,0,0,0,1,1,
1,12,13,11,13,12,14,12,13,1, 0, 1,12,14,0,0,11,13,1,     0, 1,0,11,13,0,0,1,1,
1,1,11,13,11,14,12,14,1,1,   0, 1,1,0,0,0,0,1,1,         0, 1,12,13,11,13,0,1,1,
1,1,0,11,13,12,14,0,1,1,     0, 1,11,2,2,2,2,14,1,       0, 1,1,11,13,11,13,1,1,
1,1,0,0,11,14,0,0,1,1,       0, 1,12,2,2,2,2,13,1,       0, 1,1,0,11,13,11,14,1,
1,1,0,0,0,0,0,0,1,1,         0, 1,1,0,0,0,0,1,1,         0, 1,1,0,0,11,13,0,1,
1,1,0,0,0,0,0,0,1,1,         0, 1,1,0,0,0,0,1,1,         0, 1,1,0,0,0,11,13,1,
11,14,0,0,0,0,0,0,11,14,     0, 11,14,0,0,0,0,11,14,     0, 11,14,0,0,0,0,11,14
};
