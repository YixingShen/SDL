/* ppmviewer.cpp
 * Demostrate rendering a PPM file.
 * It is a slight modification of ppmdemo.cpp; SDL is used to display image.
 *
 * Compile: g++ -o ppmviewer ppmviewer.cpp -I/usr/include -L/usr/local/lib -lSDL 
 * Execute: ./ppmviewer
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

//A public class is the same as a 'struct'
class CImage {
public:
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};


void ppm_read_comments ( FILE *fp )
{
  int c;
  while ( (c = getc ( fp ) )  == '#' ) {
    while (  getc( fp )  != '\n' )
	;
  }
  ungetc ( c, fp );
}  

class ppm_error
{
  public:
    ppm_error() {
      printf("\nIncorrect PPM format!\n");
      exit ( 1 );
    }
};


//change from (R, G, B) to (B, G, R) 
void  ppm2sdl ( CImage *ibuf, int width, int height )
{
  unsigned char temp;

  for ( int i = 0; i < height; ++i ) {
    int row_offset = i * width;
    for ( int j = 0; j < width; ++j ){
      int offset =  row_offset + j;
      temp = ibuf[offset].red;
      ibuf[offset].red = ibuf[offset].blue;
      ibuf[offset].blue = temp;
    }
  }
}

int main()
{
  int ppmh[20], c;			//PPM header
  int width, height;			//image width and height  
  SDL_Surface *screen;
  char filename[] = "../data/beach.ppm";

  FILE *input = fopen (filename, "rb"); //PPM file for testing read
  if ( !input ) {
    printf("\nError opening input file %s!\n", filename);
    return 1;
  }

  //read PPM input file
  ppm_read_comments ( input );		//read comments
  char temp[100];
  fscanf ( input, "%2s", temp );
  temp[3] = 0;
  if ( strncmp ( temp, "P6", 2 ) ) 
    throw ppm_error();
  ppm_read_comments ( input );
  fscanf ( input, "%d", &width );
  ppm_read_comments ( input );
  fscanf ( input, "%d", &height );
  ppm_read_comments ( input );
  int colorlevels;
  fscanf ( input, "%d", &colorlevels );
  printf("\n%s PPM file: ", temp );
  printf(" \n\twidth=%d\theight=%d\tcolorlevles=%d\n", width,height,colorlevels+1 ); 
  ppm_read_comments ( input );
  while ( ( c = getc ( input )) == '\n' );     //get rid of extra line returns
  ungetc ( c ,input ); 

  // May use CImage ibuf[width][height] if we do not use SDL_QUIT;
  CImage *ibuf = (CImage *) malloc ( width * height * 3 );
  fread ( ibuf,  3, width * height, input );   //read image data from file
  fclose ( input );

  //initialize video system
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }
  //ensure SDL_Quit is called when the program exits
  atexit(SDL_Quit);	//if not use this, we need to 
                        //  do house cleaning manually when program ends
 
  //set video mode of width x height with 24-bit pixels
  screen = SDL_SetVideoMode( width, height, 24, SDL_SWSURFACE);
  if ( screen == NULL ) {
        fprintf(stderr, "Unable to set %dx%d video: %s\n", width, height, SDL_GetError());
        exit(1);
  } 

  //convert PPM format (R, G, B)  to SDL format (B, G, R)
  ppm2sdl ( ibuf,  width, height );

  screen->pixels = ibuf;  //point framebuffer to data buffer
			  //  ibuf needs to be dynamically allocated if SDL_QUIT is used
  SDL_UpdateRect ( screen, 0, 0, 0, 0 );	//blit data to screen  

  SDL_Delay ( 4000 );	  //delay 4 seconds before exit
  printf("Displaying PPM image %s successful!\n", filename );
  
  //do NOT free( ibuf ) if use SDL_QUIT which does the house cleaning
  return 0;
}
