/*************************************************************************
	> File Name: waitevent.cpp
	> Author: Mandagod
	> Blog: http://blog.csdn.net/mandagod
	> Mail: manda2003@163.com
	> Created Time: 2016年08月07日 星期日 15时16分31秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
using namespace std;

extern "C" {
#include<SDL/SDL.h>
}

bool wait_for_events();

int main(int argc, char* argv[]) {
    SDL_Surface *screen;

    // Initialize video system
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\0", SDL_GetError());
        exit(1);
    } else {
        printf("Success init SDL\n");
    }
    
    // Ensure SDL_Quit is called when the program exits
    atexit(SDL_Quit);
    //SDL_Quit();
    
    // Set video mode fo 640 x 480 with 16 - bit pixels
    screen = SDL_SetVideoMode( 640, 480, 16, SDL_SWSURFACE );
    if (screen == NULL) {
        fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
        exit(1);
    }

    wait_for_events();

    return 0;
}

//waitevent.cpp: Waiting for an event to occur.
bool wait_for_events () {
    SDL_Event event;
    int status; char *key;

    bool quit = false;
    printf("waiting for events, press ’q’ or ’ESC’ to quit\n");
    while ( !quit  ) {
        //wait indefinitely for an event to occur
        status = SDL_WaitEvent(&event);

        //event will be removed from event queue
        if ( !status  ) {
            //Error has occurred while waiting
            printf("SDL_WaitEvent error: %s\n", SDL_GetError());
            return false;
        }

        switch (event.type) {//check the event type
        case SDL_KEYDOWN:         //if a key has been pressed
            key = SDL_GetKeyName(event.key.keysym.sym);
            printf("The %s key was pressed!\n", key );
            if (event.key.keysym.sym == SDLK_ESCAPE)//quit if ’ESC’
                quit = true;
            else if ( key[0] == 'q')//quit if ’q’ pressed
                quit = true;
        break;
        case SDL_MOUSEMOTION:   //mouse moved
        printf("Mouse motion x:%d, y:%d\n", event.motion.x, event.motion.y );
        break;
        case SDL_MOUSEBUTTONUP://mouse button pressed
        printf("Mouse pressed x:%d, y:%d\n",
        event.button.x, event.button.y ); 
        break;
        case SDL_QUIT:         //’x’ of Window clicked
                exit ( 1  );
        }
    } //while
    return true;
}
