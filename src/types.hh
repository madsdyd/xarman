/***************************************************************************
                          types.h  -  description
 
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
#ifndef __TYPES_HH__
#define __TYPES_HH__


/**
   Global constant, etc. for xarman
 */

#include <stdlib.h> /** random */

typedef unsigned char byte;
typedef unsigned int  word;

#define TRUE 1
#define FALSE 0

/** A macro to define random - this one gives a number between 0 and a */
#define random(q) ((int) ((1.0*q)*rand()/(RAND_MAX+1.0)))
#endif



