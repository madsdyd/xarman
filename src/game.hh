/***************************************************************************
                          game.h  -  description
 
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
#ifndef __GAME_H__
#define __GAME_H__
#include "types.hh"

extern int GameSpeed;
extern int ScanSpeed; 
extern int MineLevel;
extern int VictLevel;

/** The game relevant stuff */
void MainGame();

#endif
