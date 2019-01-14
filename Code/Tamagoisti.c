#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "definios.h"
#include "funct.h"

#define LARGURA 800
#define ALTURA  600

#define BOTAO_ALIMENTAR 0
#define BOTAO_EXERCITAR 1
#define BOTAO_SAIR 2

/* cria na memória uma nova especie*/
especie * cria_especie(char nome[], int inc, int dec){

    char nome_imagem_magro[30];
    char nome_imagem_normal[30];
    char nome_imagem_gordo[30];

    especie * e = malloc(sizeof(especie));

    if(e == NULL){
        exit(-1);
    }

    strcpy(e->nome_especie, nome);
    e->inc = inc;
    e->dec = dec;

    sprintf(nome_imagem_magro, "%s-magro.bmp", e->nome_especie);
    sprintf(nome_imagem_normal, "%s-normal.bmp", e->nome_especie);
    sprintf(nome_imagem_gordo, "%s-gordo.bmp", e->nome_especie);

    e->imagem_magro = load_image(nome_imagem_magro);
    e->imagem_normal = load_image(nome_imagem_normal);
    e->imagem_gordo = load_image(nome_imagem_gordo);

    return e;
}

/* cria na memoria um novo animal*/
animal * cria_animal(char nome[], especie * nomeEspecie){
    animal * a = malloc(sizeof(animal));

    if(a == NULL){
        exit(-1);
    }

    strcpy(a->nome, nome);
    a->tempo = 0;
    a->peso = 50;
    a->tipo_especie = nomeEspecie;
    a->seguinte = NULL;
    a->anterior = NULL;
	a->texto = write_text(nome, 64);

    return a;
}

/* insere o animal a no fim da lista l*/
void insere_animal(animal * a, lista * l){

    a->anterior = l->ultimo;
    if(l->ultimo == NULL){
        l->primeiro = a;
    }
    else{
        l->ultimo->seguinte = a;
    }
    l->ultimo = a;

    l->num_animais ++;

}

/*verifica se a lista l esta vazia */
int lista_vazia(lista * l){
	return l->ultimo == NULL;
}

/*remove o animal a da lista l*/
void remove_animal(animal * a, lista * l){

    if(lista_vazia(l)) return;

    l->num_animais --;
    if(a->anterior != NULL){
        a->anterior->seguinte = a->seguinte;
    }
    if(a->seguinte != NULL){
        a->seguinte->anterior = a->anterior;
    }
    if(l->primeiro == a){
        l->primeiro = a->seguinte;
    }
    if(l->ultimo == a){
        l->ultimo = a->anterior;
    }
    SDL_FreeSurface(a->texto);
    free (a);

    a->peso = -1;
}

/* cria na memoria uma nova lista*/
lista * cria_lista(){

	lista * l = malloc(sizeof(lista));
	if(l == NULL){
		exit(-1);
	}
	l->num_animais = 0;
	l->primeiro = NULL;
    l->ultimo = NULL;

    return l;
}

/*imprime na consola os dados do animal a*/
void imprime_animal(animal * a){
	printf("%s %d %d %s\n", a->nome, a->peso, a->tempo, a->tipo_especie->nome_especie);
}

/*imprime na consola todos os animais da lista l*/
void imprime_lista(lista * l){
	printf("---Estado dos animais---\n");
	animal * a = l->primeiro;
	while(a != NULL){
		imprime_animal(a);
		a = a->seguinte;
	}
}

/*alimenta todos os animais da lista l */
void alimenta_todos(lista * l){
    animal * a = l->primeiro;

	while(a != NULL){
	    a->peso += a->tipo_especie->inc;
		a = a->seguinte;
	}
	imprime_lista(l);
}

/* exercita todos os animais da lista l*/
void exercita_todos(lista * l){
	animal * a = l->primeiro;

	while(a != NULL){
	    a->peso -= a->tipo_especie->dec;
		a = a->seguinte;
	}
	imprime_lista(l);
}

/* verifica e elimina todos os animais mortos da lista l */
void verifica_animais_mortos(lista * l){

    animal * a = l->primeiro, * aux;

	while(a != NULL){
	    aux = a->seguinte;
	    if(a->peso <=0 || a->peso >=100){
            printf("\nO animal %s morreu!\n", a->nome);
            remove_animal(a, l);
	    }
		a = aux;
	}
}

/* cria um novo animal a partir de dados recebidos da consola */
void introduzir_animal(lista * l, especie * e[]){

    char s[20];
    int k;
    int i;
    printf("Qual o nome do animal que deseja criar?\n");
    scanf("%s", s);
    printf("\nEscolha a espécie do animal %s\n", s);
    for(i=0; i<10; i++){

       printf("%d - %s\n", i, e[i]->nome_especie);
    }
    scanf("%d", &k);
    if(k>= 0 && k<= 9){

        insere_animal(cria_animal(s, e[k]), l);

    }
}

/* aumenta uma unidade de tempo ao estado de todos os animais */
void passa_tempo(lista * l){

    animal * a = l->primeiro;

	while(a != NULL){
        a->tempo++;
        if(a->tempo % 2 == 0)
        {
            if(a->peso > 75)
            {
                a->peso += a->tipo_especie->inc;
            }
            else if(a->peso < 25)
            {
                a->peso -= a->tipo_especie->dec;
            }
        }
		a = a->seguinte;
	}
}

/* muda o animal atual para o seguinte da lista l */
animal * muda_animal_seguinte(animal * atual){

    if(atual->seguinte != NULL){
        return atual->seguinte;
    }
    return atual;
}

/* muda o animal atual para o anterior da lista l */
animal * muda_animal_anterior(animal * atual){

    if(atual->anterior != NULL){
        return atual->anterior;
    }
    return atual;
}

/* desenha a interface (botoes e barra) e devolve um valor caso algum tenha sido premido */
int desenha_interface(SDL_Event * evento, SDL_Surface * window, SDL_Surface * alimentar,
                      SDL_Surface * exercitar, SDL_Surface * sair, SDL_Surface * barra){
	int x, y;

    print_image(window, alimentar, 20, 430);
    print_image(window, exercitar, 220, 430);
    print_image(window, sair, 420, 430);
    print_image(window, barra, 700, 203);


    if(evento->type == SDL_MOUSEBUTTONDOWN){
        getMouseClick(*evento, &x, &y);
    /* cadeia de if para definir os diferentes butoes*/
        if(x > 20 && x < 200 && y > 430 && y < 560){
            return BOTAO_ALIMENTAR;
        }
        else if(x > 220 && x < 400 && y > 430 && y < 560){
            return BOTAO_EXERCITAR;
        }
        else if(x > 420 && x < 600 && y > 430 && y < 560){
            return BOTAO_SAIR;
        }
    }
    return -1;

}

/* desenha o animal a no ecra */
void desenha_animal(animal * a, SDL_Surface * window){

    if(a->peso >= 25 && a->peso <= 75){
        print_image(window, a->tipo_especie->imagem_normal, 0, 0);
    }
    else if(a->peso < 25)
    {
        print_image(window, a->tipo_especie->imagem_magro, 0, 0);
    }
    else
    {
        print_image(window, a->tipo_especie->imagem_gordo, 0, 0);
    }
}

/* desenha o valor do peso do animal a no ecra */
void desenha_peso(animal * a, SDL_Surface * window, SDL_Surface * barraVerde, SDL_Surface * barraVermelha){

    print_image(window, a->texto, 170, 50);

    if(a->peso >= 25 && a->peso <= 75){
        print_image(window, barraVerde, 706, 405 - a->peso * 2);
    }
    else if(a->peso < 25)
    {
        print_image(window, barraVermelha, 706, 405 - a->peso * 2);
    }
    else
    {
        print_image(window, barraVermelha, 706, 405 - a->peso * 2);
    }
}

/* funçao que termina o programa, libertando a memoria alocada */
void termina_programa(especie * e[], lista * l,
                      SDL_Surface * alimentar,
                      SDL_Surface * exercitar,
                      SDL_Surface * sair,
                      SDL_Surface * barra){

    int i;
    animal * a, * aux;

    a = l->primeiro;

	while(a != NULL){
	    aux = a->seguinte;
        remove_animal(a, l);
		a = aux;
	}

	free(l);

    for(i = 0; i<10; i++){
        SDL_FreeSurface(e[i]->imagem_magro);
        SDL_FreeSurface(e[i]->imagem_normal);
        SDL_FreeSurface(e[i]->imagem_gordo);
        free(e[i]);
    }

    SDL_FreeSurface(alimentar);
    SDL_FreeSurface(exercitar);
    SDL_FreeSurface(sair);
    SDL_FreeSurface(barra);

    SDL_Quit();
}

/* guarda num ficheiro "animais.txt" o estado dos animais da lista l */
void guardar_backup(lista * l){

    animal * a;

    FILE * fp = fopen("animais.txt", "w+");

    a = l->primeiro;

	while(a != NULL){
	    fprintf(fp, "%s %d %d %s\n", a->nome, a->peso, a->tempo, a->tipo_especie->nome_especie);
		a = a->seguinte;
	}
	fclose(fp);

}

/* carrega do ficheiro "animais.txt" o estado dos animais e guarda na lista l */
void carregar_backup(lista * l, especie * e[]){

    FILE * fp;
    char s[20], esp[20];
    int peso, tempo;
    int i;
    fp = fopen("animais.txt", "r");
    if(fp == NULL)
	{
		introduzir_animal(l, e);
	}
	else
	{
        while(fscanf(fp, "%s %d %d %s", s, &peso, &tempo, esp) != EOF){

            especie * tipo_esp;
            animal * a;

            for(i=0; i<10; i++){
                if(strcmp(e[i]->nome_especie, esp) == 0){
                    tipo_esp = e[i];
                    break;
                }
            }
            a = cria_animal(s, tipo_esp);
            a->peso = peso;
            a->tempo = tempo;

            insere_animal(a, l);


        }
		fclose(fp);
	}

}

int main()
{
	SDL_Surface * window;
	SDL_Surface * barraVerde;
	SDL_Surface * barraVermelha;
	SDL_Surface * barraPeso;
	SDL_Surface * alimentar;
	SDL_Surface * sair;
	SDL_Surface * exercitar;

	SDL_Event evento;

	int end = 0;
	FILE * fp;

	animal * atual = NULL;
	especie * especies[10];
	lista * l = cria_lista();

	fp = fopen("especies.txt", "r");
	if(fp == NULL)
	{
	    printf("Nao encontra o ficheiro especies.txt");
		exit(-1);
	}
	else
	{
	    char nome_esp[20];
	    int inc, dec, i;

        for(i=0; i<10; i++){

            fscanf(fp, "%s %d %d", nome_esp, &inc, &dec);
            especies[i] = cria_especie(nome_esp, inc, dec);
        }
	}
	fclose(fp);

	window = open_window(LARGURA, ALTURA);

    carregar_backup(l, especies);
    atual = l->primeiro;

	barraVerde = SDL_LoadBMP("barraVerde.bmp");
	barraVermelha = SDL_LoadBMP("barraVermelha.bmp");
	barraPeso = SDL_LoadBMP("barraPeso.bmp");
	alimentar = SDL_LoadBMP("alimentar.bmp");
	exercitar = SDL_LoadBMP("exercitar.bmp");
	sair = SDL_LoadBMP("sair.bmp");

/* ciclo principal */
	while(!end)
	{
		if(SDL_WaitEvent( &evento))
		{
            desenha_animal(atual, window);
            int interface = desenha_interface(&evento, window, alimentar, exercitar, sair, barraPeso);
            desenha_peso(atual, window, barraVerde, barraVermelha);

            if(interface == -1);
            else if(interface == BOTAO_ALIMENTAR)
            {
                atual->peso += atual->tipo_especie->inc;
            }
            else if(interface == BOTAO_EXERCITAR)
            {
                atual->peso -= atual->tipo_especie->dec;
            }
            else if(interface == BOTAO_SAIR)
            {
                end = 1;
            }

            int valor_evento = verifica_evento(evento);

            switch(valor_evento){

                case -1:
                    break;
                case TECLA_ESPACO:
                    passa_tempo(l);
                    break;
                case TECLA_A:
                    alimenta_todos(l);
                    break;
                case TECLA_E:
                    exercita_todos(l);
                    break;
                case TECLA_N:
                    introduzir_animal(l, especies);
                    break;
                case TECLA_ESQ:
                    atual = muda_animal_anterior(atual);
                    break;
                case TECLA_DIR:
                    atual = muda_animal_seguinte(atual);
                    break;
            }

            verifica_animais_mortos(l);

            if(atual->peso < 0){
                if(lista_vazia(l))
                {
                    end = 1;
                    printf("Já não tens mais animais!\n");
                }
                else{
                    atual = l->primeiro;
                }
            }


            SDL_Flip(window);
		}
	}
	if(lista_vazia(l)){

        remove("animais.txt");

	}
	else{
        guardar_backup(l);
	}
	termina_programa(especies, l, alimentar, exercitar, sair, barraPeso);
	exit (0);
}
