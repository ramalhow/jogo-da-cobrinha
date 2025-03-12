#define SCALE 3
#define WIDTH (4 * SCALE)
#define HEIGHT (3 * SCALE)

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

// estruturas do jogo
typedef struct { int x, y; } vec2;


// váriaveis globais
char map[9][12] = {
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

char screen[9][12];
vec2 food;

// funções
void StartMenu() {
    printf("\tBem vindo ao jogo da cobrinha!\n");
    printf("\t  criado por: Arthur Ramalho\n");
    printf("\nPressione qualquer tecla para continuar...");
    getch();
    system("cls");
}

void ShowInstructions() {

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

int main() {

    StartMenu();

    ShowInstructions();

    food = RandomCoordInMap();
    head->pos = RandomCoordInMap();

    SpawnInMap(food);
    SpawnInMap(head->pos);

    int alive = 1;

    DrawMap();

    /*
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
        };

        DrawMap();
        DrawElements();
    }
    */

    return 0;
}
