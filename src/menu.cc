/***************************************************************************
                          menu.c  -  description
 
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
#include <SDL/SDL.h>
#include "menu.hh"
#include "data.hh"
#include "game.hh"
#include "sound.hh"
/** ********************************************************************** */
/** Some module wide definitions */

int letterno = 2;
int letterx= 0;
int lettersx;
int stringno = 0;


/** ********************************************************************** */
/** MENU STUFF */

/** ********************************************************************** */
/** Display options menu */

void Options() {
  bool exit = false;
  sound_play(SFX_MENU_OPTIONS);
  while(!exit) {
    
    Cls();
    PutPix(77, 50, 166, 99, MENU2);
    
    /** Options sprites. These have fixed places on the screen */
    switch (MineLevel) {
    case 1: PutPix(77+76 ,51, 16, 16, CHECK); break;
    case 2: PutPix(77+92 ,51, 16, 16, CHECK); break;
    case 3: PutPix(77+107,51, 16, 16, CHECK); break;
    }
    
    switch (GameSpeed) {
    case 1: PutPix(77+114,69, 16, 16, CHECK); break;
    case 2: PutPix(77+130,70, 16, 16, CHECK); break;
    case 3: PutPix(77+144,70, 16, 16, CHECK); break;
    }

    switch (ScanSpeed) {
    case 1: PutPix(77+108,87, 16, 16, CHECK); break;
    case 2: PutPix(77+125,87, 16, 16, CHECK); break;
    case 3: PutPix(77+139,87, 16, 16, CHECK); break;
    }

    switch (VictLevel) {
    case 1: PutPix(77+116,107, 16, 16, CHECK); break;
    case 2: PutPix(77+131,107, 16, 16, CHECK); break;
    case 3: PutPix(77+149,107, 16, 16, CHECK); break;
    }

    /* Display on screen */
    Flip();

#define mod4(a) a++; if (a == 4) a = 1

    /** Check for keyboard events, take action */
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
	switch (event.key.keysym.sym) {
	case SDLK_b:
	case SDLK_ESCAPE: {
	  exit = true;
	  break;
	} 
	case SDLK_m: {
	  mod4(MineLevel); 
	  sound_play(SFX_MENU_OPTION_MOVE);
	  break;
	}
	case SDLK_g: {
	  mod4(GameSpeed); 
	  sound_play(SFX_MENU_OPTION_MOVE);
	  break;
	}
	case SDLK_s: {
	  mod4(ScanSpeed); 
	  sound_play(SFX_MENU_OPTION_MOVE);
	  break;
	}
	case SDLK_v: {
	  mod4(VictLevel); 
	  sound_play(SFX_MENU_OPTION_MOVE);
	  break;
	}
	default: {
	  /** Unknown key, play a sfx */
	  sound_play(SFX_MENU_ERROR);
	  break;
	}
	} /* Switch */
      } /* Not keydown */
    } /* No event */
    // TODO: This is ugly, just wait for keyboard events should be better
    SDL_Delay(20);
  } /* While !exit */
}

void display_mainmenu() {
  sound_play(SFX_MENU_MAIN);
  /* Display the menu pic (start, options, exit). */
  Cls();
  PutPix(90, 45, 140, 110, MENU); 
  Flip();
}

/* **********************************************************************
 * An intro
 * *********************************************************************/
void Intro() {
  Cls();
  Text(4);
  Flip();
  SDL_Delay(1000);
  Cls();
  Text(5);
  Flip();
  SDL_Delay(1000);
}


/** ********************************************************************** */
/** THE MENU */

void Menu() {
  int Quit = 0;
  SDL_Event event;

  Intro();

  display_mainmenu();
  
  /* Main game loop */
  while(!Quit) {
      
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
	
	switch (event.key.keysym.sym) {
	case SDLK_s: {
	  /** Call the main game */
	  MainGame();


	  /* Return from game */
	  /** Stop all sounds playing, when returning from the game */
	  sound_stop(-1);
	  
	  /** Empty the char buffer. */
	  // while(0 != vga_getkey());
	  display_mainmenu();
	  break;
	} 
	case SDLK_o: {
	  /** Options */
	  Options();
	  
	  /* Return to main menu */
	  display_mainmenu();
	  break;
	}
	case SDLK_x: {
	  /** End the game */
	  Quit = 1;
	  break;
	}
	default: {
	  /** Unknown key, play a sfx */
	  sound_play(SFX_MENU_ERROR);
	  break;
	}
	} /* Switch */
      } /* Not keydown */
    } /* No event */
  } /* Quit is true */
  sound_play(SFX_GAME_BOMB);
  SDL_Delay(2000);
}
