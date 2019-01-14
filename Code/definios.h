/*
        Definição de estruturas
*/

/* Estrutura especie
contem:
    o nome da especie
    os valores de incremento(inc) e decremento(dec) que alteram o peso
    as imagens correspondentes aos diferentes estados do animal

*/

typedef struct _especie{
	char nome_especie[15];
	int inc;
	int dec;
	SDL_Surface * imagem_magro;
	SDL_Surface * imagem_normal;
	SDL_Surface * imagem_gordo;
}especie;

/* Estrutura animal
contem:
    o nome do animal
    o seu peso
    uma referencia para a especie do animal
    o tempo que passou desde a sua criação
    a imagem com o nome do animal (texto)
    um ponteiro para o animal seguinte e para o anterior

*/
typedef struct _animal{
    char nome[20];
    int peso;
    especie * tipo_especie;
    int tempo;
    SDL_Surface * texto;

    struct _animal * seguinte;
    struct _animal * anterior;

} animal;

/* Lista
    e a estrutura base para a lista dos animais
    tem o numero de elementos da lista
    um ponteiro para o primeiro animal da lista
    um ponteiro para o ultimo animal da lista

*/

typedef struct _lista{
    int num_animais;
    animal * primeiro;
    animal * ultimo;


} lista;
