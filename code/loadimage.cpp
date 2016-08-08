/*************************************************************************
	> File Name: loadimage.cpp
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
#include<SDL/SDL_image.h>
}

bool load_image(SDL_Surface *screen, char *image_name,int x,int y);

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

    //put image near center of screen
    if ( !load_image ( screen, "../data/test-image.gif", 320, 240  )  )
        exit ( 1  );

    //update the entire screen
    SDL_UpdateRect ( screen, 0, 0, 0, 0  );

    SDL_Delay( 4000 ); // Delay 2 seconds before exit
    printf("Setting video mode successful!\n");

    return 0;
}

//Example: Loading an Image using IMG_Load()
bool load_image(SDL_Surface *screen, char *image_name,int x,int y){
    SDL_Surface *image;
    SDL_Rect source, offset; //Offset is the destination

    image = IMG_Load( image_name );
    if ( image == NULL ) {
        printf ( "Unable to load image\n" );
        return false;
    }

    source.x = 0; source.y = 0;
    source.w = image->w; source.h=image->h;//display the whole image
    offset.x = x; offset.y = y; //position to display the image
    offset.w = image->w;  //width and height here actually NOT used
    offset.h = image->h;

    //Draws image data to the screen:(image,source) is the source,
    // (screen, offset) is the destination
    SDL_BlitSurface ( image, &source, screen, &offset  );
    
    //free the resources allocated to image
    SDL_FreeSurface ( image  );
    
    return true;
}
