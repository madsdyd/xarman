/***************************************************************************
                          video.c  -  description
 
                             -------------------
 
    begin                : Mon Jun 21 00:55:10 CEST 1999
 
    copyright            : (C) 1999 by Mads Bondo Dydensborg
                           (Parts may be (C) ECC)
 
    email                : mads@dydensborg.dk
 
 ***************************************************************************/
 
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *

***************************************************************************/
#include <SDL/SDL.h>
#include "log.hh"
#include "video.hh"
#include "data.hh"
/** ********************************************************************** */
/* **********************************************************************
 * The global screen
 * *********************************************************************/
SDL_Surface * Screen = NULL;

/** ********************************************************************** */
/** ********************************************************************** */
/** ********************************************************************** */
/** GENERAL FUNCTIONS */

/** ********************************************************************** */
/** Puts a pixmap on the current context, without drawing color 0 */
void PutPix (short int x, short int y, short int width, short int height, SDL_Surface * sprt) {
  if (!sprt) {
    LogLine(LOG_ERROR, "Null surface passed to PutPix");
    return;
  }
  SDL_Rect dest, src;
  dest.x = x;
  dest.y = y;
  src.x = 0;
  src.y = 0;
  src.w = width;
  src.h = height;
  SDL_BlitSurface(sprt, &src, Screen, &dest); 
}

void PutPix (int x, int y, short width, short height, SDL_Surface * sprt) {
    PutPix( (short) x, (short) y, width, height, sprt );
}


/** ********************************************************************** */
/** Puticon draws a 16x16 sprite at x,y into the current contex... 
    Does not draw color 0*/
void Puticon(short int x, short int y, SDL_Surface * sprt) {
  PutPix(x, y, 16, 16, sprt);
}

void Puticon(int x, int y, SDL_Surface * sprt) {
    Puticon( (short) x, (short) y, sprt );
}


/** ********************************************************************** */
/** void Cls - used to clear by moving, now changes context, and clears */
void Cls() {
  /** Clear it */
  // TODO: Map black to global.
  SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0)); 
}

/** ********************************************************************** */
/** Puts some text on virtual screen 0? */
void Text(int number) {
  short int a,b;
  /** Set up the context */
  // gl_setcontext(&(VirtualScreen[0]));
  
  switch (number) {
  case 0:
    for (a=0;a<15;a++)
      for (b=0;b<23;b++)
          PutPix(100+(b*5), 60+(a*5), 5, 5, ICON[text1[b+(23*a)]]);
    break;
  case 1:
    for (a=0;a<15;a++)
      for (b=0;b<23;b++)
	PutPix(100+(b*5), 60+(a*5), 5, 5, ICON[text2[b+(23*a)]]);
    break;
  case 3:
    for (a=0;a<15;a++)
      for (b=0;b<24;b++)
	PutPix(100+(b*5), 60+(a*5), 5, 5, ICON[text3[b+(24*a)]]);
    break;
  case 4:
    for (a=0;a<17;a++)
      for (b=0;b<40;b++)
	PutPix(57+(b*5), 60+(a*5), 5, 5, ICON[text4[b+(40*a)]]);
    break;
  case 5:
    for (a=0;a<21;a++)
      for (b=0;b<28;b++)
	PutPix(90+(b*5), 50+(a*5), 5, 5, ICON[text5[b+(28*a)]]);
  break;
  }
}

/* **********************************************************************
 * Copy the current screen to the screen passed here 
 * *********************************************************************/
void Flip() {
  SDL_Flip(Screen);
}
