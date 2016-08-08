/*************************************************************************
	> File Name: waitevent1.cpp
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

//Refresh Event
#define REFRESH_EVENT  (SDL_USEREVENT + 1)

int thread_exit=0;
int thread_pause=0;

int refresh_video(void *opaque){
    while (1) {
        if(thread_pause==0){
            SDL_Event event;
            event.type = REFRESH_EVENT;
            SDL_PushEvent(&event);
        }
        SDL_Delay(1000);
    }
    return 0;
}

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

    SDL_Thread *refresh_thread = SDL_CreateThread(refresh_video, (void *)"Refresh Thread");

    SDL_Event event;
    int status;
    char *key;
    while(1){
        //wait indefinitely for an event to occur
        status = SDL_WaitEvent(&event);
        
        //event will be removed from event queue
        if ( !status   ) {
            //Error mZas occurred while waiting
            printf("SDL_WaitEvent error: %s\n", SDL_GetError());
            return false;
        }

        switch (event.type) {//check the event typedef
        case REFRESH_EVENT:
            printf("Receiveing REFRESH_EVENT\n");
        break;
        case SDL_KEYDOWN:         //if a key has been pressed
            key = SDL_GetKeyName(event.key.keysym.sym);
            printf("The %s key was pressed!\n", key );
            //Pause
            if(event.key.keysym.sym==SDLK_SPACE) {
                thread_pause = !thread_pause;
                //SDLK_SPACE
                printf("Key SPACE has been pressed!!\n");
            } else if(event.key.keysym.sym==SDLK_a)
                printf("Key a has been pressed!!\n");
            else if(event.key.keysym.sym==SDLK_b)
                printf("Key b has been pressed!!\n");
        break;
        }
    } // while

    return 0;
}
