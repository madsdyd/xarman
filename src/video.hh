/***************************************************************************
                          video.h  -  description
 
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
#ifndef __VIDEO_HH__
#define __VIDEO_HH__
/** Defines stuff that handles video.
    Sort of */

#include <stdio.h>
#include <SDL/SDL.h>
#include "types.hh"

/* **********************************************************************
 * The screen - very important... 
 * *********************************************************************/
extern SDL_Surface * Screen;

/* **********************************************************************
 * Clear the screen
 * *********************************************************************/
void Cls();

/** ********************************************************************** */
/** Puticon draws a 16x16 sprite at x,y into the current contex... 
    Does not draw color 0*/
void Puticon(short int x, short int y, SDL_Surface * sprt);
void Puticon(int x, int y, SDL_Surface * sprt);

/** ********************************************************************** */
/** Puts a pixmap on the current context, without drawing color 0 */
void PutPix (short int x, short int y, short int width, short int height, SDL_Surface * sprt);
void PutPix (int x, int y, short int width, short int height, SDL_Surface * sprt);

/** ********************************************************************** */
/** Write some text somewhere? */
void Text(int number);

/* **********************************************************************
 * Flip the screen
 * *********************************************************************/
void Flip();



#endif







