/***************************************************************************
                          game.c  -  description
 
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
#include <iostream>
#include "game.hh"
#include "video.hh"
#include "data.hh"
#include "sound.hh"
/** Definitions, etc. */

/** define the player numbers */
#define RED 0
#define BLUE 1


/** Define a type for the animations and movement. */
typedef enum {north = 0, east = 2, south = 1, 
	      west = 3, scan = 5, mine = 6} state;   

struct PlayerInfo {
  int      x;
  int      y;
  int     sqrx;
  int     sqry;
  word     frame;  // What frame was last shown
  // What direction
  state dir;   
  byte     move;   // Is he moving?
  int     delay;
  int     land;
  int     vict;
};

struct SqrInfo {
  int     owner;      // who owns this land?
  int     mine;       // is here a mine?
  int     used;       // is there a player on the field?
  int     infonumber; // the help number
};

struct StarInfo {
  int     x;
  int     y;
  int     z;
};

//                              //
// GLOBAL VARIABLE DECLARATIONS //
//                              //

int GameSpeed = 2, ScanSpeed = 2, MineLevel = 2, VictLevel = 2;

/** argh. C references from 0! This is very lucky to work!
    I add an ektra Player... */
struct PlayerInfo Player[2];    // The player info
/** int owner[10][10]; */
struct SqrInfo  Sqr[12][12];       // The square info
struct StarInfo Star[150];

/** Game relevant stuff */

/* Some sound stuff */
int red_scan_channel = -1;
int blue_scan_channel = -1;

/** ********************************************************************** */
/** void SetUpLand - initializes the land */
void SetUpLand() {
  int loop1,loop2;
  int x,y,mines;
  
  /** Initialize to blank */
  for (loop1 = 0; loop1 < 12; loop1++)
    for (loop2 = 0; loop2 < 12; loop2++) {
      Sqr[loop1][loop2].used = 0;
      Sqr[loop1][loop2].owner = 0;
      Sqr[loop1][loop2].mine = 0;
      Sqr[loop1][loop2].infonumber = 0;
    }
  /** Get the number of mines */
  if (MineLevel == 1)
    mines = 10;
  else if (MineLevel == 2)
    mines = 15;
  else if (MineLevel == 3)
    mines = 20;
  
  /** Place mines almost randomly */
  for (loop1 = 0; loop1 < (mines+1); loop1++) {
    /** The random function should most likely return a number
	[0, 10[ */
    x = random(10);
    x++;
    y = random(10);
    y++;
    /** No mines in the corners it seems. */
    if (((x == 1) && (y == 1)) ||
	((x == 2) && (y == 1)) ||
	((x == 1) && (y == 2)) ||
	((x == 2) && (y == 2)) ||
	((x == 10) && (y == 10)) ||
	((x == 9) && (y == 10)) ||
	((x == 10) && (y == 9)) ||
	((x == 9) && (y == 9)))
      loop1--;
    else
      Sqr[x][y].mine = 1;
  }
  /** Note, how the fact that the board is 12*12 is used... */
  // Assign numbers to Sqr's :)
  for (loop1 = 1; loop1 < 11; loop1++)
    for (loop2 = 1; loop2 < 11; loop2++) {
      x=0;
      if (Sqr[loop1+1][loop2].mine == 1) x++;
      if (Sqr[loop1+1][loop2+1].mine == 1) x++;
      if (Sqr[loop1+1][loop2-1].mine == 1) x++;
      if (Sqr[loop1-1][loop2].mine == 1) x++;
      if (Sqr[loop1-1][loop2+1].mine == 1) x++;
      if (Sqr[loop1-1][loop2-1].mine == 1) x++;
      if (Sqr[loop1][loop2+1].mine == 1) x++;
      if (Sqr[loop1][loop2-1].mine == 1) x++;
      
      Sqr[loop1][loop2].infonumber = x;
    }
}

/** ********************************************************************** */
/** void SetPlayers - Initializes the player info for each round */
void SetPlayers() {
  Player[RED].x = 8;
  Player[RED].y = 8;
  Player[RED].sqrx = 1;
  Player[RED].sqry = 1;
  Player[RED].dir = south;
  Player[RED].frame = 1;
  Player[RED].land = 0;
  Player[RED].delay = 0;
  Player[RED].move = 0;
  Sqr[Player[RED].sqrx][Player[RED].sqry].used = 1;
  
  Player[BLUE].x = 80;
  Player[BLUE].y = 80;
  Player[BLUE].sqrx = 10;
  Player[BLUE].sqry = 10;
  Player[BLUE].dir = north;
  Player[BLUE].frame = 1;
  Player[BLUE].land = 0;
  Player[BLUE].delay = 0;
  Player[BLUE].move = 0;
  Sqr[Player[BLUE].sqrx][Player[BLUE].sqry].used = 1;
}

/** ********************************************************************** */
void KeyCheck(SDL_Event * event) {
  //  Player red     Dirs     Player blue
  //     w          1          i
  //   a s d      4 2 3      j k l

  /** This could probably be greatly simplified... */

  /* Red Moves */
  if (!Player[RED].delay) {
    if (SDLK_w == event->key.keysym.sym)
      if (!(Player[RED].move)&&(Player[RED].sqry > 1))
	if (Sqr[Player[RED].sqrx][Player[RED].sqry-1].used == 0) {
	  Sqr[Player[RED].sqrx][Player[RED].sqry-1].used = 1;
	  Player[RED].dir = north;
	  Player[RED].move = 1;
	  sound_play(SFX_GAME_RED_MOVE);
	}
    
    if (SDLK_s == event->key.keysym.sym)
      if (!(Player[RED].move)&&(Player[RED].sqry < 10))
	if (Sqr[Player[RED].sqrx][Player[RED].sqry+1].used == 0) {
	  Sqr[Player[RED].sqrx][Player[RED].sqry+1].used = 1;
	  Player[RED].dir = south;
	  Player[RED].move = 1;
	  sound_play(SFX_GAME_RED_MOVE);
	}
    
    if (SDLK_d == event->key.keysym.sym)
      if (!(Player[RED].move)&&(Player[RED].sqrx < 10))
	if (Sqr[Player[RED].sqrx+1][Player[RED].sqry].used == 0) {
	  Sqr[Player[RED].sqrx+1][Player[RED].sqry].used = 1;
	  Player[RED].dir = east;
	  Player[RED].move = 1;
	  sound_play(SFX_GAME_RED_MOVE);
	}
    
    if (SDLK_a == event->key.keysym.sym)
      if (!(Player[RED].move)&&(Player[RED].sqrx > 1))
	if (Sqr[Player[RED].sqrx-1][Player[RED].sqry].used == 0) {
	  Sqr[Player[RED].sqrx-1][Player[RED].sqry].used = 1;
	  Player[RED].dir = west;
	  Player[RED].move = 1;
	  sound_play(SFX_GAME_RED_MOVE);
	}
    if (SDLK_q == event->key.keysym.sym)
      if (!(Player[RED].move)) {
	/** Play a sound */
	if (-1 == red_scan_channel) {
	  red_scan_channel = sound_loop(SFX_GAME_RED_SCAN);
	}
	if (ScanSpeed == 1)
	  Player[RED].delay = 300 * GameSpeed;
	else if (ScanSpeed == 2)
	  Player[RED].delay = 150 * GameSpeed;
	else if (ScanSpeed == 3)
	  Player[RED].delay = 50 * GameSpeed;
	Player[RED].dir = scan;
      }
  } else if (SDLK_q == event->key.keysym.sym) { // if is scanning check for stopping
    /** Stop the sound of red scanning */
    if (-1 != red_scan_channel) {
      sound_stop(red_scan_channel);
      red_scan_channel = -1;
    }
    Player[RED].delay = 0;
    Player[RED].frame = 1;
    Player[RED].dir = north;
  }
  
  /* Blue moves */
  if (!Player[BLUE].delay) {
    if (SDLK_i == event->key.keysym.sym)
      if (!(Player[BLUE].move)&&(Player[BLUE].sqry > 1))
	if (Sqr[Player[BLUE].sqrx][Player[BLUE].sqry-1].used == 0) {
	  Sqr[Player[BLUE].sqrx][Player[BLUE].sqry-1].used = 1;
	  Player[BLUE].dir = north;
	  Player[BLUE].move = 1;
	  sound_play(SFX_GAME_BLUE_MOVE);
	}
    
    if (SDLK_k == event->key.keysym.sym)
      if (!(Player[BLUE].move)&&(Player[BLUE].sqry < 10))
	if (Sqr[Player[BLUE].sqrx][Player[BLUE].sqry+1].used == 0) {
	  Sqr[Player[BLUE].sqrx][Player[BLUE].sqry+1].used = 1;
	  Player[BLUE].dir = south;
	  Player[BLUE].move = 1;
	  sound_play(SFX_GAME_BLUE_MOVE);
	}
    
    if (SDLK_l == event->key.keysym.sym)
      if (!(Player[BLUE].move)&&(Player[BLUE].sqrx < 10))
	if (Sqr[Player[BLUE].sqrx+1][Player[BLUE].sqry].used == 0) {
	  Sqr[Player[BLUE].sqrx+1][Player[BLUE].sqry].used = 1;
	  Player[BLUE].dir = east;
	  Player[BLUE].move = 1;
	  sound_play(SFX_GAME_BLUE_MOVE);
	}
    
    if (SDLK_j == event->key.keysym.sym)
      if (!(Player[BLUE].move)&&(Player[BLUE].sqrx > 1))
	if (Sqr[Player[BLUE].sqrx-1][Player[BLUE].sqry].used == 0) {
	  Sqr[Player[BLUE].sqrx-1][Player[BLUE].sqry].used = 1;
	  Player[BLUE].dir = west;
	  Player[BLUE].move = 1;
	  sound_play(SFX_GAME_BLUE_MOVE);
	}
    
    if (SDLK_u == event->key.keysym.sym)
      if (!(Player[BLUE].move)) {
	/** Play a sound */
	if (-1 == blue_scan_channel) {
 	  blue_scan_channel = sound_loop(SFX_GAME_BLUE_SCAN);
	}
	if (ScanSpeed == 1)
	  Player[BLUE].delay = 300 * GameSpeed;
	else if (ScanSpeed == 2)
	  Player[BLUE].delay = 150 * GameSpeed;
	else if (ScanSpeed == 3)
	  Player[BLUE].delay = 50 * GameSpeed;
	Player[BLUE].dir = scan;
      }
    
  } else if (SDLK_u == event->key.keysym.sym) {
    /** Stop the sound of blue playing */
    if (-1 != blue_scan_channel) {
      sound_stop(blue_scan_channel);
      blue_scan_channel = -1;
    }
    Player[BLUE].delay = 0;
    Player[BLUE].frame = 1;
    Player[BLUE].dir = north;
  }
}

/** ********************************************************************** */
/** Stars - I guess it draw stars (into the 0 virtual context) */
#ifdef STARS
void Stars() {
  int loop1, nx, ny, temp, color;
  int Xoff =  160;
  int Yoff =  100;
  int Zoff = -256;
  for (loop1 = 0; loop1 < 150; loop1++)
    if ((Star[loop1].z == 0)) {
      Star[loop1].x = random(320) - 160;
      Star[loop1].y = random(200) - 100;
      Star[loop1].z = 2;
      break;
    }
  for (loop1 = 0; loop1 < 150; loop1++)
    if (Star[loop1].z) {
      Star[loop1].z+=3;
      if (Star[loop1].z > 240) {
	Star[loop1].z = 1;
	Star[loop1].x = random(320) - 160;
	Star[loop1].y = random(200) - 100;
      }
    }

  gl_setcontext(&(VirtualScreen[0]));
  for (loop1 = 0; loop1 < 150; loop1++)
    if (Star[loop1].z) {
      temp = Star[loop1].z + Zoff;
      nx = ((256*Star[loop1].x) / temp) + Xoff;
      ny = ((256*Star[loop1].y) / temp) + Yoff;
      if ((nx < 320)&&(nx > 0)&&(ny < 200)&&(ny > 0)) {
	color = 86;
	if (Star[loop1].z > 40) color = 87;
	if (Star[loop1].z > 80) color = 89;
	if (Star[loop1].z > 120) color = 91;
	if (Star[loop1].z > 160) color = 92;
	if (Star[loop1].z > 200) color = 94;
	if (Star[loop1].z > 240) color = 95;
	/** Putpixel (nx, ny, color, Vaddr1); */
	gl_setpixel(nx, ny, color);
      }
    }
}
#endif
/** ********************************************************************** */
/** This apperently does some calculating of stuff like animation
    frames, bomcs, owner stuff, etc */

void CalcPP(byte number) {
  /** Cycle the scan animation */
  if (Player[number].delay) {
    Player[number].delay--;
    Player[number].frame++;
    if (Player[number].frame == 13)
      Player[number].frame = 1;
  }
  
  /** If last frame in scan, mark found mines */
  if (Player[number].delay == 1) {
    /** Since a player has stopped scanning, stop the scan sound, if present */
    if (number == BLUE) {
      if (-1 != blue_scan_channel) {
	sound_stop(blue_scan_channel);
	blue_scan_channel = -1;
      } 
    } else {
      if (-1 != red_scan_channel) {
	sound_stop(red_scan_channel);
	red_scan_channel = -1;
      } 
    } 
    if (Sqr[Player[number].sqrx+1][Player[number].sqry+1].mine) {
      Sqr[Player[number].sqrx+1][Player[number].sqry+1].owner = 3;
      Player[number].land++; }
    if (Sqr[Player[number].sqrx+1][Player[number].sqry-1].mine) {
      Sqr[Player[number].sqrx+1][Player[number].sqry-1].owner = 3;
      Player[number].land++; }
    if (Sqr[Player[number].sqrx+1][Player[number].sqry].mine) {
      Sqr[Player[number].sqrx+1][Player[number].sqry].owner = 3;
      Player[number].land++; }
    if (Sqr[Player[number].sqrx-1][Player[number].sqry+1].mine) {
      Sqr[Player[number].sqrx-1][Player[number].sqry+1].owner = 3;
      Player[number].land++; }
    if (Sqr[Player[number].sqrx-1][Player[number].sqry-1].mine) {
      Sqr[Player[number].sqrx-1][Player[number].sqry-1].owner = 3;
      Player[number].land++; }
    if (Sqr[Player[number].sqrx-1][Player[number].sqry].mine) {
      Sqr[Player[number].sqrx-1][Player[number].sqry].owner = 3;
      Player[number].land++; }
    if (Sqr[Player[number].sqrx][Player[number].sqry-1].mine) {
      Sqr[Player[number].sqrx][Player[number].sqry-1].owner = 3;
      Player[number].land++; }
    if (Sqr[Player[number].sqrx][Player[number].sqry+1].mine) {
      Sqr[Player[number].sqrx][Player[number].sqry+1].owner = 3;
      Player[number].land++; }
    // Setup old data (we dont save the old, so we just make so up)
    Player[number].delay = 0;
    Player[number].frame = 1;
    Player[number].dir = south;
  }
  
  if (!(Player[number].move))
    return;
  
  Player[number].frame++;
  
  switch(Player[number].dir) {
  case north:Player[number].y--; break;
  case south:Player[number].y++; break;
  case east:Player[number].x++; break;
  case west:Player[number].x--; break;
  default: break;
  }

  if (Player[number].frame == 9) {
    Player[number].move = 0;
    Player[number].frame = 1;
    
    if ((Player[number].dir == north) && (Player[number].sqry > 1)) {
      Sqr[Player[number].sqrx][Player[number].sqry].used = 0;
      Player[number].sqry--;
    }
    
    if ((Player[number].dir == south) && (Player[number].sqry < 10)) {
      Sqr[Player[number].sqrx][Player[number].sqry].used = 0;
      Player[number].sqry++;
    }
    
    if ((Player[number].dir == east) && (Player[number].sqrx < 10)) {
      Sqr[Player[number].sqrx][Player[number].sqry].used = 0;
      Player[number].sqrx++;
    }
    
    if ((Player[number].dir == west) && (Player[number].sqrx > 1)) {
      Sqr[Player[number].sqrx][Player[number].sqry].used = 0;
      Player[number].sqrx--;
    }
  }
}
/** ********************************************************************** */
/** AnimPlayer 
    Draws pictures needed to the virtual buffer 2. */

/** Define some animations as arrays */
SDL_Surface * MoveAnims[2][4][8];
SDL_Surface * ScanAnims[2][12];

/* Init them - done every game, but so what... */
void InitAnims() {
  /** 2 players, 4 directions, 8 frames */
  SDL_Surface * tmp[2][4][8] = {
    {
      {RD1F1, RD1F2, RD1F1, RD1F3, RD1F1, RD1F2, RD1F1, RD1F3},
      {RD2F1, RD2F2, RD2F1, RD2F3, RD2F1, RD2F2, RD2F1, RD2F3},
      {RD3F1, RD3F2, RD3F1, RD3F3, RD3F1, RD3F2, RD3F1, RD3F3},
      {RD4F1, RD4F2, RD4F1, RD4F3, RD4F1, RD4F2, RD4F1, RD4F3}
    },
    {
      {BD1F1, BD1F2, BD1F1, BD1F3, BD1F1, BD1F2, BD1F1, BD1F3},
      {BD2F1, BD2F2, BD2F1, BD2F3, BD2F1, BD2F2, BD2F1, BD2F3},
      {BD3F1, BD3F2, BD3F1, BD3F3, BD3F1, BD3F2, BD3F1, BD3F3},
      {BD4F1, BD4F2, BD4F1, BD4F3, BD4F1, BD4F2, BD4F1, BD4F3}
    }
  };
  for (int a = 0; a < 2; a++) {
    for (int b = 0; b < 4; b++) {
      for (int c = 0; c < 8; c++) {
	MoveAnims[a][b][c] = tmp[a][b][c];
      }
    }
  }
  
  /** The scan animation is a 12 frame animation */
  SDL_Surface * tmp2[2][12] = {
    {
      RSCAN1, RSCAN1, RSCAN1, RSCAN2, RSCAN2, RSCAN2,  
      RSCAN3, RSCAN3, RSCAN3, RSCAN2, RSCAN2, RSCAN2  
    },
    {
      BSCAN1, BSCAN1, BSCAN1, BSCAN2, BSCAN2, BSCAN2,  
      BSCAN3, BSCAN3, BSCAN3, BSCAN2, BSCAN2, BSCAN2  
    }
  };
  for (int a = 0; a < 2; a++) {
    for (int b = 0; b < 12; b++) {
      ScanAnims[a][b] = tmp2[a][b];
    }
  }
};

void AnimPlayer(int yoffset, int PlayerNum) {
  /** Temp stuff */
  int ArrayFrame;//, PlayerFrame;
  state TmpDir;
  
  /** Just convenient */
  TmpDir = Player[PlayerNum].dir;
  //  PlayerFrame = PlayerNum - 1;
  switch (TmpDir) {
  case south: case north: case east: case west:
    ArrayFrame = (Player[PlayerNum].frame - 1) % 8; /** Make sure 0-7 */
    Puticon(80+(Player[PlayerNum].x * 2)-16, 
	    yoffset+20+(Player[PlayerNum].y * 2)-16, 
	    MoveAnims[PlayerNum][TmpDir][ArrayFrame]); 
    break;
  case scan: 
    ArrayFrame = (Player[PlayerNum].frame - 1) % 12; /** Make sure 0-11 */
    Puticon(80+(Player[PlayerNum].x * 2)-16, 
	    yoffset+20+(Player[PlayerNum].y * 2)-16, 
	    ScanAnims[PlayerNum][ArrayFrame]); 
    break;    
  case mine: 
    Puticon(80+(Player[PlayerNum].x * 2)-16, 
	    yoffset+20+(Player[PlayerNum].y * 2)-16,
	    MINE); 
    break;
  default:
    fprintf(stderr, "AnimPlayers : unknown state\n");
  }
}


/** ********************************************************************** */
/** Make buffer makes the graphics that goes onto the play board */
void Board(int yoffset) {
  
  int loop1,loop2;
  
  /** Draw the land  */
  
  /** Draw the tiles */
  for (loop1 = 1; loop1 < 11; loop1++) {
    for (loop2 = 1; loop2 < 11; loop2++) {
      switch (Sqr[loop1][loop2].owner) {
      case 0: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,LAND); break;
      case 1: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,LAND1); break;
      case 2: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,LAND2); break;
      case 3: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,LAND3); break;
      }
    }
  }

  /** Animate the players */
  AnimPlayer(yoffset, RED);
  AnimPlayer(yoffset, BLUE);
  
  /** Draw those little numbers on the tiles */
  for (loop1 = 1; loop1 < 11; loop1++)
    for (loop2 = 1; loop2 < 11; loop2++) {
      if (Sqr[loop1][loop2].owner)
	if (Sqr[loop1][loop2].owner != 3)
	  switch (Sqr[loop1][loop2].infonumber) {
	  case 0: break;
	  case 1: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N1); break;
	  case 2: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N2); break;
	  case 3: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N3); break;
	  case 4: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N4); break;
	  case 5: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N5); break;
	  case 6: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N6); break;
	  case 7: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N7); break;
	  case 8: Puticon(80+(loop1 * 16)-16,yoffset+20+(loop2 * 16)-16 ,N8); break;
	  }
    }
}

/** ********************************************************************** */
/** Draws scores, etc */
void Score() {
  int StartY = 150;
  int player1x = 35;
  int player2x = 280;
  int loop1;
  int a; //counter
  
  /** I reckon this draws a "pole" for the score */
  PutPix(player1x,StartY, 5, 5, ICON[15]);
  for (loop1 = 1; loop1 <= 23; loop1++) {
    PutPix(player1x,StartY - (5*loop1), 5, 5, ICON[1]);
  }
  PutPix(player1x,StartY - 120 , 5, 5, ICON[17]);
  
  PutPix(player2x,StartY, 5, 5, ICON[15]);
  for (loop1 = 1; loop1 <= 23; loop1++)
    PutPix(player2x,StartY - (5*loop1), 5, 5, ICON[1]);
  PutPix(player2x,StartY - 120 , 5, 5, ICON[17]);
  
  /** And this fills the score "pole" */
  PutPix(player1x+1,StartY +1 - (5*(Player[RED].land / 2)), 3, (short) (3+(5*(Player[RED].land / 2))), REDDOT);
  PutPix(player2x+1,StartY +1- (5*(Player[BLUE].land / 2)), 3, (short) (3+(5*(Player[BLUE].land / 2))), BLUEDOT);
  
  //Bigger Pixs
  PutPix(0,20, 34,92, REDSIDE);
  PutPix(286,20, 34,92, BLUESIDE);
  
  PutPix(290,160, 30,20, REDKEYS);
  PutPix(0,160, 30,20, BLUEKEYS);
  
  //Prints victories
  if (Player[RED].vict)
    for (a=0;a<Player[RED].vict;a++)
      PutPix(a*15,182,16,16, CHECK);
  
  if (Player[BLUE].vict)
    for (a=0;a<Player[BLUE].vict;a++)
      PutPix(300-(a*15),182,16,16, CHECK2);
}

/** ********************************************************************** */
/** Function that displays game over screen??? */

void GameOver(int looser) {
  int a,vict;
  SDL_Event event;
  Player[looser].dir = mine;
  /** Stop all sounds */
  sound_stop(-1);
  /** PLay the bomb sound */
  sound_play(SFX_GAME_BOMB);

  /** Give the players a chance to figure out what happened */
  if (GameSpeed == 1)
    a = 50;
  else if (GameSpeed == 2)
    a = 100;

  do {
    if (GameSpeed == 1)
      SDL_Delay(40);
    else if (GameSpeed == 2)
      SDL_Delay(20);
    Cls();
    /** Make a buffer with board in it */
    Board(0);
    
    /** Draw the background stars */
    // Stars();
    
    // Side pics and score bar 
    Score();

    Flip();
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
	if (SDLK_ESCAPE == event.key.keysym.sym) {
	  a = -1;
	}
      }
    }
    a--;
  } while (a > 0);
  
  /** Scroll down the game area while updating */
  for (a=0;a<200;a++) {
    if (GameSpeed == 1)
      SDL_Delay(20);
    else if (GameSpeed == 2)
      SDL_Delay(10);
    Cls();
    // Stars();
    Text(looser);
    Board(a);
    Score();
    Flip();
  }
  
  /* Need this for checking */
  if (VictLevel == 1)
    vict = 2;
  else if (VictLevel == 2)
    vict = 5;
  else if (VictLevel == 3)
    vict = 10;
  
  /** Check if the game is over
      Display a text message and return */
  if ((Player[RED].vict == vict) || (Player[BLUE].vict == vict)) {
    for (a=0;a<100;a++) {
      if (GameSpeed == 1)
	SDL_Delay(40);
      else if (GameSpeed == 2)
	SDL_Delay(20);
      Cls();
      // Stars();
      Text(3);
      Score();
      Flip();
      Cls();
    }
    return;
  }
  
  /** Reset stuff */
  SetUpLand();
  SetPlayers();
  
  /** Scroll up again while updating*/
  for (a=1;a<200;a++) {
    if (GameSpeed == 1)
      SDL_Delay(20);
    else if (GameSpeed == 2)
      SDL_Delay(10);
    // Stars();
    Text(looser);
    Cls();
    Board(200-a);
    Score();
    Flip();
    Cls();
  }
}

/** ********************************************************************** */
/** MainGame - This function now runs an entire game */

void MainGame() { // MAIN LOOP!
  SDL_Event event; /** Used to read from the SDL event buffer */
  bool exit = false;
  int vict = 3; /** Holds number of victories needed */
  // TODO: Remove int NewRound;

  /* Init animation arrays */
  InitAnims();

  /** How much does it take to win .. */
  if (VictLevel == 1)
    vict = 2;
  else if (VictLevel == 2)
    vict = 5;
  else if (VictLevel == 3)
    vict = 10;
  
  /** No player has yet won */
  Player[RED].vict = 0;
  Player[BLUE].vict = 0;
  
  /** Setup the land and initialize players for a new round.
      Between rounds, this will be done in the GameOver call.*/
  SetUpLand();
  SetPlayers();

  /** Play the game start sfx */
  sound_play(SFX_GAME_START);

  /** While no player has won or escape pressed */
  while (!exit &&  
	 (Player[RED].vict != vict) && (Player[BLUE].vict != vict)) {
    /** TODO: Empty the char buffer - from previous games, and menu */
    // while(0 != vga_getkey());
    
    /* Clear the screen */
    Cls();

    /** Set flag */
    // TODO: Remove NewRound = 0;
    while (!exit) {
      bool breakflag = false;
      int looser = -1;
      /** If player 1 has moved, update his count of tiles, if necc. */
      if (!(Player[RED].move))
	if (Sqr[Player[RED].sqrx][Player[RED].sqry].owner == 0) {
	  sound_play(SFX_GAME_RED_SHOW);
	  Sqr[Player[RED].sqrx][Player[RED].sqry].owner = 1;
	  Player[RED].land++;
	}
      
      /** If player 2 has moved, update his count of tiles, if necc. */
      if (!(Player[BLUE].move))
	if (Sqr[Player[BLUE].sqrx][Player[BLUE].sqry].owner == 0) {
	  sound_play(SFX_GAME_BLUE_SHOW);
	  Sqr[Player[BLUE].sqrx][Player[BLUE].sqry].owner = 2;
	  Player[BLUE].land++;
	}
      /** Get an event from the input queue - check for moves */
      if (SDL_PollEvent(&event)) {
	if (event.type == SDL_KEYDOWN) {
	  if (SDLK_ESCAPE == event.key.keysym.sym) {
	    exit = true;
	  } 
	  else if (SDLK_F11 == event.key.keysym.sym) {
	    /* FullScreenToggle is bound to F11 */
	    SDL_WM_ToggleFullScreen(Screen);
	  } else {
	    KeyCheck(&event);
	  }
	}
      }
      
      /** Update some stuff - not really sure what */
      CalcPP(RED);
      CalcPP(BLUE);
      
      /** Make a buffer with board in it */
      Board(0);
      
      /** Draw the background stars */
      // Stars();
      
      /* Draw side bars and score */
      Score();

      /* Check for a dead red player */
      if (Sqr[Player[RED].sqrx][Player[RED].sqry].mine == 1) {
	// Board(0);;
	Puticon(80+(Player[RED].sqrx * 16) -16,20+(Player[RED].sqry * 16)-16,MINE);
	Player[BLUE].vict++;
	looser = RED;
	breakflag = true;
      }
      /* Check for a dead blue player */
      if (Sqr[Player[BLUE].sqrx][Player[BLUE].sqry].mine == 1) {
	// Board(0);;
	Puticon(80+(Player[BLUE].sqrx * 16) -16,20+(Player[BLUE].sqry * 16)-16 ,MINE);
	Player[RED].vict++;
	looser = BLUE;
	breakflag = true;
      }
      
      if (Player[RED].land >= 48) {
	Player[RED].vict++;
	looser = BLUE;
	breakflag = true;
      }
      if (Player[BLUE].land >= 48) {
	Player[BLUE].vict++;
	looser = RED;
	breakflag = true;
      }

      /* Flip the bufers */
      Flip();
      
      if (breakflag) {
	GameOver(looser);
	break;
      }

      /* Delay the game */
      if (GameSpeed == 1)
	SDL_Delay(40);
      else if (GameSpeed == 2)
	SDL_Delay(20);
      //   else if (GameSpeed == 3)
      //   No delay
   
    } /* While not escape */ 
  } /* While not escape and not victory */ 
}
