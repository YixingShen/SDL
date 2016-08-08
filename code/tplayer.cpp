/*
  tplayer.cpp
  A simple multi-threaded program to demonstrate playing raw video using SDL.  Assume that you  
  have a raw video clip named "sample_video.raw" in directory ../data/ and assume that the image
  size is 320 x 240 and is 24 bits/pixel.
  Solution for producer-consumer problem is used to handle interface between "decoder" and player.
  The player acts as a consumer and the "decoder" plays the role of a producer.
  Pressing 'ESC' ends the program. 
  Compile by: g++ -o tplayer tplayer.cpp -I/usr/include -L/usr/local/lib -lSDL
  Execute by: ./tplayer
*/
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

//shared variables
bool quit = false;
char *buf[4];
unsigned long head = 0,  tail = 0;
unsigned int frameSize;

//Consumer
int player ( void *scr )
{
  SDL_Surface *screen = ( SDL_Surface * ) scr;
  Uint32 prev_time, current_time;
  current_time = SDL_GetTicks();//ms since library starts
  prev_time = SDL_GetTicks();   //ms since library starts

  while ( !quit ) {
    if ( head == tail ) {	//buffer empty (data not available yet )
      SDL_Delay ( 30 );		//sleep for 30 ms
      continue;
    }
    //consumes the data
    screen->pixels = buf[head%4];
    current_time = SDL_GetTicks();        //ms since library starts
    if ( current_time - prev_time < 50 )  //20 fps ~ 50 ms / frame
      SDL_Delay ( 50 - (current_time - prev_time) );
    prev_time = current_time;

    SDL_UpdateRect ( screen, 0, 0, 0, 0 );      //update whole screen
    head++;
  } //while
  return 0;
}

//Producer
int decoder ( void *data )
{
  static FILE *fp = NULL;
  long n;

  if ( fp == NULL )
    fp = fopen ( "../data/sample_video.raw", "rb" );	
  if ( fp == NULL ) {
    printf("\nError opeing file\n" );
    quit = true;
    return 1;
  }
  while ( !quit ) {
     if ( tail >= head + 4 ) {	//buffer full
	SDL_Delay ( 30 );	
	continue;
     }
     //produce data
     n = fread ( buf[tail%4], frameSize, 1, fp ); 
     if ( n <= 0 )
	quit = true; 
     else
	tail++;
  } //while
  return 0;
}

int main()
{   
  SDL_Surface *screen;
  frameSize = 320 * 240 * 3;
  SDL_Thread *producer, *consumer;
  SDL_Event event;
  int status;
  char *key;

  //initialize video system
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
  }
  //ensure SDL_Quit is called when the program exits
  atexit(SDL_Quit);
   
  //set video mode of 320 x 240 with 24-bit pixels
  screen = SDL_SetVideoMode(320, 240, 24, SDL_SWSURFACE);
  if ( screen == NULL ) {
        fprintf(stderr, "Unable to set 320x240 video: %s\n", SDL_GetError());
        exit(1);
  }
  //create buffers to hold at most 4 frames of video data
  for ( int i = 0; i < 4; ++i ) {
    buf[i] = ( char * ) malloc ( frameSize );
    assert ( buf[i] );
  }
  consumer = SDL_CreateThread ( player, screen );
  producer = SDL_CreateThread ( decoder, ( void * ) "decdoing" );
  while (!quit)
  {
    status = SDL_WaitEvent(&event);     //wait indefinitely for an event to occur
                                        //event will be removed from event queue
    if ( !status ) {                    //Error has occured while waiting
        printf("SDL_WaitEvent error: %s\n", SDL_GetError());
        quit = true;
        return false;
    }
    switch (event.type) {               //check the event type
      case SDL_KEYDOWN:                 //if a key has been pressed
        key = SDL_GetKeyName(event.key.keysym.sym);
        printf("The %s key was pressed!\n", key );
        if ( event.key.keysym.sym == SDLK_ESCAPE )      //quit if 'ESC' pressed
          quit = true;
        else if ( key[0] == 'q'  )      //quit if 'q'  pressed
          quit = true;                  //same as "if ( event.key.keysym.sym == SDLK_q )"
    }
    SDL_Delay ( 100 );			//give up some CPU time
  }

  SDL_WaitThread ( consumer, NULL );
  SDL_WaitThread ( producer, NULL );
  printf("Video play successful!\n");
  //no need to free buf[i] because SQL_Quit does the job.
  return 0;
}
