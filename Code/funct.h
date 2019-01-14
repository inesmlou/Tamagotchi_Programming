#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define LARGURA 800
#define ALTURA  600

#define TECLA_ESPACO 0
#define TECLA_A 1
#define TECLA_E 2
#define TECLA_N 3
#define TECLA_ESQ 4
#define TECLA_DIR 5

/* verifies if the user pressed the space bar */
int space_bar_pressed(SDL_Event e);

int botaoA_pressed(SDL_Event e);

int botaoE_pressed(SDL_Event e);

int botaoN_pressed(SDL_Event e);

int botaoLEFT_pressed(SDL_Event e);

int botaoRIGHT_pressed(SDL_Event e);

int verifica_evento(SDL_Event e);

/* Prints a string into a surface */
SDL_Surface * write_text(char * str, int size);

/* initialize/s SDL and opens a windows */
SDL_Surface * open_window(int width, int height);

SDL_Surface * load_image(char * nome);

/* prints an image into the destination surface */
void print_image(SDL_Surface * dest,
				 SDL_Surface * image,
				int x, int y);

/* function that returns the x, y of a mouse click */
void getMouseClick(SDL_Event evento, int *x, int *y);
