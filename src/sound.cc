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
#include "sound.hh"
#include "soundmanager.hh"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

/* Load all needed sounds */
void sound_init() {
  /** The global sound pointers gets loaded */
  SFX_MENU_MAIN = SoundManager->RequireRessource("sounds/menu.wav");
  SFX_MENU_OPTIONS = SoundManager->RequireRessource("sounds/options.wav");
  SFX_MENU_OPTION_MOVE = SoundManager->RequireRessource("sounds/option.move.wav");
  SFX_MENU_ERROR = SoundManager->RequireRessource("sounds/error.wav");
  SFX_GAME_START = SoundManager->RequireRessource("sounds/gstart.wav");
  SFX_GAME_RED_MOVE = SoundManager->RequireRessource("sounds/rmove.wav");
  SFX_GAME_BLUE_MOVE = SoundManager->RequireRessource("sounds/bmove.wav");
  SFX_GAME_RED_SHOW = SoundManager->RequireRessource("sounds/rshow.wav");
  SFX_GAME_BLUE_SHOW = SoundManager->RequireRessource("sounds/bshow.wav");
  SFX_GAME_RED_SCAN = SoundManager->RequireRessource("sounds/rscan.wav");
  SFX_GAME_BLUE_SCAN = SoundManager->RequireRessource("sounds/bscan.wav");
  SFX_GAME_BOMB = SoundManager->RequireRessource("sounds/bomb.wav");
}

/* Play a sound */
void sound_play(Mix_Chunk * sound) {
  if (sound) {
    // LogLine(LOG_INFO, "Playing sound");
    Mix_PlayChannel(-1, sound, 0);
  } else {
    // LogLine(LOG_ERROR, "sound_play called on NULL sound");
  }
}

int sound_loop(Mix_Chunk * sound) {
  if (sound) {
    // LogLine(LOG_INFO, "Looping sound");
    return Mix_PlayChannel(-1, sound, -1);
  } else {
    // LogLine(LOG_ERROR, "sound_play called on NULL sound");
    return -1;
  }
}

void sound_stop(int sound) {
  Mix_HaltChannel(sound);
}


/** The global sound pointers */
Mix_Chunk * SFX_MENU_MAIN;           /** Zip.wav   / back.raw */
Mix_Chunk * SFX_MENU_OPTIONS;        /** bop.wav   / options.raw*/
Mix_Chunk * SFX_MENU_OPTION_MOVE;    /** bop.wav   / options.raw*/
Mix_Chunk * SFX_MENU_ERROR;          /** bonk.wav  / error.raw */

Mix_Chunk * SFX_GAME_START;          /** Squeaky trumpet / gstart.raw*/
Mix_Chunk * SFX_GAME_RED_MOVE;       /** drip.wav        / rmove.raw */
Mix_Chunk * SFX_GAME_BLUE_MOVE;      /** sqeak.wav       / bmove.raw */
Mix_Chunk * SFX_GAME_RED_SHOW;       /** pop.wav         / rshow.raw */
Mix_Chunk * SFX_GAME_BLUE_SHOW;      /** pop.wav         / bshow.raw */ 
Mix_Chunk * SFX_GAME_RED_SCAN;       /** sonar.wav       / rscan.raw */
Mix_Chunk * SFX_GAME_BLUE_SCAN;      /** medibeep.wav    / bscan.raw */
Mix_Chunk * SFX_GAME_BOMB;           /** Explosion__281_29.wav / bomb.raw */

