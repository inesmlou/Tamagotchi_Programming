#include "funct.h"

/* verifies if the user pressed the space bar */
int space_bar_pressed(SDL_Event e){
	if( e.type == SDL_KEYDOWN ) {
		if( e.key.keysym.sym == SDLK_SPACE){
			return 1;
		}
	}
	return 0;
}
int botaoA_pressed(SDL_Event e){
	if( e.type == SDL_KEYDOWN ) {
		if( e.key.keysym.sym == SDLK_a){
			return 1;
		}
	}
	return 0;
}
int botaoE_pressed(SDL_Event e){
	if( e.type == SDL_KEYDOWN ) {
		if( e.key.keysym.sym == SDLK_e){
			return 1;
		}
	}
	return 0;
}
int botaoN_pressed(SDL_Event e){
	if( e.type == SDL_KEYDOWN ) {
		if( e.key.keysym.sym == SDLK_n){
			return 1;
		}
	}
	return 0;
}
int botaoLEFT_pressed(SDL_Event e){
	if( e.type == SDL_KEYDOWN ) {
		if( e.key.keysym.sym == SDLK_LEFT){
			return 1;
		}
	}
	return 0;
}
int botaoRIGHT_pressed(SDL_Event e){
	if( e.type == SDL_KEYDOWN ) {
		if( e.key.keysym.sym == SDLK_RIGHT){
			return 1;
		}
	}
	return 0;
}

/* verifica a tecla pressionada, devolvendo um valor correspondente */
int verifica_evento(SDL_Event e){

    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            case SDLK_SPACE:
                return TECLA_ESPACO;
            case SDLK_A:
                return TECLA_A;
            case SDLK_E:
                return TECLA_E;
            case SDLK_N:
                return TECLA_N;
            case SDLK_LEFT:
                return TECLA_ESQ;
            case SDLK_RIGHT:
                return TECLA_DIR;
        }

    }

    return -1;
}



/* Prints a string into a surface */
SDL_Surface * write_text(char * str, int size){

	TTF_Font *font;
	SDL_Surface * rendered_text;
	SDL_Color textColor = { 225, 175, 35 };

	font = TTF_OpenFont("acmesa.ttf", 64);
	if(font == NULL){
		printf("Font not found!\n%s\n", TTF_GetError());
		exit(-4);
	}
	rendered_text = TTF_RenderText_Solid(font,
								str,
								textColor);
	return rendered_text;
}

/* initialize/s SDL and opens a windows */
SDL_Surface * open_window(int width, int height){
	SDL_Surface * window;

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		printf("SDL not loaded\n");
		exit(-1);
	}
	window = SDL_SetVideoMode(LARGURA, ALTURA, 32,SDL_SWSURFACE);
	if(window == NULL){
		printf("Window not created\n");
		exit(-2);
	}
	SDL_WM_SetCaption("Tamagoisti", NULL);

	if(TTF_Init()==-1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	return window;
}

SDL_Surface * load_image(char * nome){
	SDL_Surface *image;

	image = SDL_LoadBMP(nome);
	if(image == NULL){
		printf("image not found\n");
		exit(-3);
	}
	return image;
}

/* prints an image into the destination surface */
void print_image(SDL_Surface * dest,
				 SDL_Surface * image,
				int x, int y){

	SDL_Rect position;
	position.x = x;
	position.y = y;

	SDL_BlitSurface(image,  NULL,
       dest, &position);
	/* SDL_Flip(dest); */
}

/* function that returns the x, y of a mouse click */
void getMouseClick(SDL_Event evento, int *x, int *y){
	*x = evento.button.x;
	*y = evento.button.y;
}

