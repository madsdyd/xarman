/***************************************************************************
                          xarman.c  -  description
 
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
/** Xarman - by ECC. */

/** Linux conversion to svgalib and /dev/dsp started at 1999.06.04, 
    by Mads Dydensborg <mads@dydensborg.dk> 
 
    The DOS version uses direct hardware access to a VGA board present in the
    machine. The Linux version uses svgalib to access the video hardware
    and read from the keyboard.

    Sound using /dev/dsp has been aadded
    
    All comments by Mads Dydensborg start with slash-star-star.
*/
/* Conversion to SDL, by Mads Bondo Dydensborg, started 20011211 */

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* Include debug and log */
#include "debug.hh"
#include "log.hh"

/* Include stuff that handles ressources */
#include "ressourcemanager.hh"
#include "surfacemanager.hh"
#include "soundmanager.hh"

/** Include common types and global stuff */
#include "types.hh"

/** Sound support - to be able to initialize the sound hardware */

/* Load data */
#include "data.hh"

/** Include the menu */
#include "menu.hh"

/** Include the graphics handling code */
#include "video.hh"

/* And sound code */
#include "sound.hh"

/** Varios other stuff is needed */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>  
#include <string.h>

/** ********************************************************************** */
/** Show usage */
void usage(char * myname) {
  printf("Usage: %s [-s|--nosound] [-f|--fullscreen]\n", myname);
  exit(1);
}

/* **********************************************************************
 * A handler for segmentation errors 
 * *********************************************************************/
void SignalHandler(int signal) {
  cerr << "Received signal " << signal << endl; 
  BackTrace();
  exit(-1);
}

/** ********************************************************************** */
/** MAIN */

int main(int argc, char*argv[]) {

  /* **********************************************************************
   * Scan options
   * *********************************************************************/
  int c;
  int status;

  /** Set default values */
  int SoundOn = TRUE;
  bool fullscreen = false;
  /** Scan all program options */
  while (1)
    {
      int option_index = 0;
      static struct option long_options[] =
      {
	{"nosound", no_argument, 0, 's'},
	{"help", no_argument, 0, 'h'},
	{"fullscreen", no_argument, 0, 'f'},
	{0, 0, 0, 0}
      };
      
      c = getopt_long (argc, argv, "fhsd:",
		       long_options, &option_index);
      if (c == -1)
	break;
      
      switch (c)
	{
	case 's':
	  SoundOn = FALSE;
	  printf("Dropping the sound\n");
	  break;
	case 'f':
	  fullscreen = true;
	  printf("Going fullscreen\n");
	  break;
	  /** Everything else */
	default:
	  usage(argv[0]);
	}
    }
  /** Check for extra arguments */
  if (optind < argc) {
    usage(argv[0]);
  }
                                
  /* **********************************************************************
   * Initialize the logging stuff, if present
   * *********************************************************************/
#ifdef DEBUG
  Log = new TLog();
  Assert(Log != NULL, "Unable to create Log object");
  LogLine(LOG_VERBOSE, "Log object created");
  LogLineExt(LOG_INFO, ("Created object %i", 34));
#endif

  /* **********************************************************************
   * Print our version, and so on.
   * *********************************************************************/
  cout << "Xarman " << VERSION << endl
       << "Copyright (C) 2002 Mads Bondo Dydensborg "
       << "<mads@dydensborg.dk>" << endl 
       << "Parts Copyright (C) ECC" << endl 
       << "Xarman comes with ABSOLUTLY NO WARRANTY." << endl
       << "This is free software, and you are welcome to "
       << "redistribute it" << endl 
       << "under certain conditions. See the file COPYING for details." 
       << endl;

  /* **********************************************************************
   * Initialize the ressource management system
   * *********************************************************************/
  PathManager = new TPathManager();
  Assert(PathManager != NULL, "Unable to create pathmanager");
  LogLine(LOG_VERBOSE, "PathManager created");

  /* Add default datapaths */
  PathManager->AddPath(XARMAN_DATADIR);
  PathManager->AddPath("data");


  /* **********************************************************************
   * Initialize SDL
   * *********************************************************************/
  if (SoundOn) {
    status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  } else {
    status = SDL_Init(SDL_INIT_VIDEO);
  }
  if (0 != status) {
    LogFatal("Unable to initialize SDL: " << SDL_GetError());
  }
  /* Make sure it is shutdown, when we exit */
  Assert(0 == atexit(SDL_Quit), 
	 "Unable to register SDL_Quit with atexit");
  LogLine(LOG_VERBOSE, "SDL initialized");

  /* **********************************************************************
   * Setup the screen
   * *********************************************************************/
  SDL_WM_SetCaption("Xarman", 0);
  
  if (!fullscreen) {
    Screen = SDL_SetVideoMode(320, 200, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
  } else {
    Screen = SDL_SetVideoMode(320, 200, 0, 
			      SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
  }
  Assert(Screen != NULL, "Unable to set video mode");

  /* Remove the cursor */
  SDL_ShowCursor(SDL_DISABLE);

  /* **********************************************************************
   * Setup the Audio
   * *********************************************************************/
  if (SoundOn) {
    SoundOn = (Mix_OpenAudio(11025, AUDIO_U8, 1, 256) >= 0);
    if (!SoundOn) {
      printf("Unable to open audio - no sound\n");
    }
  }
  /* **********************************************************************
   * Initialize the sound manager
   * *********************************************************************/
  SoundManager = new TSoundManager(SoundOn);
  Assert(SoundManager != NULL, "Unable to create SoundManager");
  LogLine(LOG_VERBOSE, "SoundManager Initialized");

  /* **********************************************************************
   * Load the sounds
   * *********************************************************************/
  sound_init();

  /**  randomize(); */
  srand((unsigned int) time(NULL)); /** Sucks, should use time or similar */

  /* **********************************************************************
   * Initialize the surface manager (requires SDL to be initialized and 
   * the video mode to be set!)
   * *********************************************************************/
  SurfaceManager = new TSurfaceManager();
  Assert(PathManager != NULL, "Unable to create SurfaceManager");
  LogLine(LOG_VERBOSE, "SurfaceManager Initialized");

  /* **********************************************************************
   * Load the graphics
   * *********************************************************************/
  data_init();

  /* **********************************************************************
   * Start the game, running from Menu
   * *********************************************************************/
  Menu();  

  /* **********************************************************************
   * Shut down stuff - hmmm. 
   * *********************************************************************/
  LogLine(LOG_TODO, "Shut down properly");
  return 0;
}
