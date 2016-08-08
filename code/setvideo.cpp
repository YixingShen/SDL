/*************************************************************************
	> File Name: setvideo.cpp
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

    SDL_Delay( 2000 ); // Delay 2 seconds before exit
    printf("Setting video mode successful!\n");

    return 0;
}
