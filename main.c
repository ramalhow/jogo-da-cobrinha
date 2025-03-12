// constantes
#define SCALE 3
#define WIDTH (4 * SCALE)
#define HEIGHT (3 * SCALE)
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

// estruturas do jogo
typedef struct vec2 { 
    int x, y; 
} vec2;

typedef struct node {
    vec2 pos;
    struct node* next;
} node;

// váriaveis globais
char screen[HEIGHT][WIDTH];

char map[HEIGHT][WIDTH] = {
    "############",
    "#          #",
    "#          #",
    "#          #",
    "#          #",
    "#          #",
    "#          #",
    "#          #",
    "############"
};

vec2 food;
node* head = NULL;

// funções
void StartMenu() {
    printf("\tBem vindo ao jogo da cobrinha!\n");
    printf("\t  criado por: Arthur Ramalho\n");
    printf("\nPressione qualquer tecla para continuar...");
    getch();
    system("cls");
}

void ShowInstructions() {
    while (1)
    {
        system("cls");
        printf("Instrucoes: \n");
        printf("\tW - pra cima\n");
        printf("\tA - pra esquerda\n");
        printf("\tS - pra baixo\n");
        printf("\tD - pra direita\n");
        printf("Objetivo: Comer o maior numero de frutinhas (@) sem bater nas paredes (e em si mesmo!)\n");
        printf("\nPressione espaco para comecar o jogo...");
        if (getch() == SPACE) {
            break;
        }
    }
    
    system("cls");
}

int RandomInMap(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

vec2 RandomCoordInMap() {
    int x = RandomInMap(1, WIDTH-1);
    int y = RandomInMap(1, HEIGHT-1);

    while(x == y){
        x = RandomInMap(1, WIDTH-1);
        y = RandomInMap(1, HEIGHT-1);
    }

    vec2 v = {x,y};
    return v;
}

void DrawMap() {
    memcpy(screen, map, sizeof(HEIGHT * WIDTH));

    strcpy(&screen[food.x][food.y],"@");

    DrawSnake();

    // TODO: printar
    for (size_t i = 0; i < ; i++)
    {
        printf("%s", );
    }
    
}

void DrawSnake() {

    // draw head
    strcpy(&screen[head->pos.x][head->pos.y],"O");

    node* aux = head->next;
    while (aux)
    {
        strcpy(&screen[aux->pos.x][aux->pos.y], "o");
        aux = aux->next;
    } 
}

int main() {

    StartMenu();

    ShowInstructions();
    
    head = (node*)malloc(sizeof(node));
    head->next = NULL;

    food = RandomCoordInMap();
    head->pos = RandomCoordInMap();

    DrawMap();

    /*
    int alive = 1;
    
    while(1) {
        ClearScreen();

        int command = WaitInput();
        MovePlayer(command);
        
        alive = CheckCollision();

        if( !alive ) {
            ShowEndScreen();
            Finish();
            break;
        }

        if ( CheckApple() ) {
            ExtendSnake();
            food = RandomCoordInMap();
            SpawnFood();
        };

        DrawMap();
        DrawElements();
    }
    */

    return 0;
}
