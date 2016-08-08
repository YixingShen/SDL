/*************************************************************************
	> File Name: DrawPixel.cpp
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


void DrawPixel(SDL_Surface *screen, Sint32 x, Sint32 y,  Uint8 R, Uint8 G, Uint8 B);

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

    // Draw Green RGB(0, 255, 0)
    DrawPixel(screen, 200, 200, 0, 255, 0);

    SDL_Delay( 5000 ); // Delay 5 seconds before exit
    printf("Setting video mode successful!\n");

    return 0;
}


//Example: Drawing a pixel on screen
void DrawPixel(SDL_Surface *screen, Sint32 x, Sint32 y,  Uint8 R, Uint8 G, Uint8 B){
    Uint32 color = SDL_MapRGB(screen->format, R, G, B);
    
    if ( SDL_MUSTLOCK(screen) )
        if ( SDL_LockSurface(screen) < 0 )
            return;
        
    
        switch (screen->format->BytesPerPixel) {
        case 1: { /* Assuming 8-bpp */
            Uint8 *bufp;
            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *bufp = color;
        } break;
        case 2: { /* Probably 15-bpp or 16-bpp */
            Uint16 *bufp;
            bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
            *bufp = color;
        } break;
        case 3: { /* Slow 24-bpp mode, usually not used */
            Uint8 *bufp;
            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *(bufp+screen->format->Rshift/8) = R;
            *(bufp+screen->format->Gshift/8) = G;
            *(bufp+screen->format->Bshift/8) = B;
        } break;
        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;
            bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
            *bufp = color;
        } break;
    }
    
    if ( SDL_MUSTLOCK(screen) )
        SDL_UnlockSurface(screen);
    // Draw 10 x 10 rectangular
    SDL_UpdateRect(screen, x, y, 10, 10);
}

