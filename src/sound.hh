/*
    XARMAN
    Copyright (C) 2001 Mads Bondo Dydensborg <mads@dydensborg.dk>
    Please see the file "AUTHORS" for a list of contributers

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef __SOUND_HH__
#define __SOUND_HH__

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

/* Load all needed sounds */
void sound_init();

/* Play a sound */
void sound_play(Mix_Chunk * sound);

/* Loop a sound */
int sound_loop(Mix_Chunk * sound);

/* Stop a sound */
void sound_stop(int sound);

/** The global sound pointers */
extern Mix_Chunk * SFX_MENU_MAIN;           /** Zip.wav   / back.raw */
extern Mix_Chunk * SFX_MENU_OPTIONS;        /** bop.wav   / options.raw*/
extern Mix_Chunk * SFX_MENU_OPTION_MOVE;    /** bop.wav   / options.raw*/
extern Mix_Chunk * SFX_MENU_ERROR;          /** bonk.wav  / error.raw */

extern Mix_Chunk * SFX_GAME_START;          /** Squeaky trumpet / gstart.raw*/
extern Mix_Chunk * SFX_GAME_RED_MOVE;       /** drip.wav        / rmove.raw */
extern Mix_Chunk * SFX_GAME_BLUE_MOVE;      /** sqeak.wav       / bmove.raw */
extern Mix_Chunk * SFX_GAME_RED_SHOW;       /** pop.wav         / rshow.raw */
extern Mix_Chunk * SFX_GAME_BLUE_SHOW;      /** pop.wav         / bshow.raw */ 
extern Mix_Chunk * SFX_GAME_RED_SCAN;       /** sonar.wav       / rscan.raw */
extern Mix_Chunk * SFX_GAME_BLUE_SCAN;      /** medibeep.wav    / bscan.raw */
extern Mix_Chunk * SFX_GAME_BOMB;           /** Explosion__281_29.wav / bomb.raw */

#endif
