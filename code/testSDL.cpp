/*************************************************************************
	> File Name: testSDL.cpp
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
    if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    } else {
        printf("Success init SDL\n");
    }
    // atexit(SDL_Quit);
    SDL_Quit();

    return 0;
}
