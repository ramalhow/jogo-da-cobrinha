// constantes
#define WIDTH 40
#define HEIGHT 20
#define W 119
#define A 97
#define S 115
#define D 100
#define SPACE 32

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>

// estruturas do jogo
typedef struct vec2
{
    uint32_t x, y;
} vec2;

typedef struct node
{
    vec2 pos;
    struct node *next;
} node;

// váriaveis globais
char screen[HEIGHT][WIDTH];
char map[HEIGHT][WIDTH];
vec2 food;

// player state
node *head = NULL;
node *end = NULL;
uint8_t snake_size = 1;
uint8_t alive = 1;
uint8_t gotFruit = 0;

// Menus
void StartMenu()
{
    printf("\tBem vindo ao jogo da cobrinha!\n");
    printf("\t  criado por: Arthur Ramalho\n");
    printf("\nPressione qualquer tecla para continuar...");
    getch();
    system("cls");
}

void ShowInstructions()
{
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
        if (getch() == SPACE)
        {
            break;
        }
    }

    system("cls");
}

// OBS: obrigado ferramentas por ia
void ShowEndScreen()
{
    printf("\n    /^\\/^\\ \n");
    printf("    _|__|  O| \n");
    printf("\\/     /~     \\_/ \\ \n");
    printf("\\____|__________/  \\ \n");
    printf("   \\_______      \\ \n");
    printf("           `\\     \\                 \\ \n");
    printf("             |     |                  \\ \n");
    printf("            /      /                    \\ \n");
    printf("           /     /                       \\ \n");
    printf("          /      /                         \\ \\ \n");
    printf("         /     /                            \\  \\ \n");
    printf("       /     /             _----_            \\   \\ \n");
    printf("      /     /           _-~      ~-_         |   |\n");
    printf("     (      (        _-~    _--_    ~-_     _/   |\n");
    printf("      \\      ~-____-~    _-~    ~-_    ~-_-~    /\n");
    printf("        ~-_           _-~          ~-_       _-~\n");
    printf("           ~--______-~                ~-___-~\n");
    printf(" _____                             ______                    _ \n");
    printf("|_   _|                           |  ___|                   | |\n");
    printf("  | | ___  _ __ ___   ___  _   _  | |_ _   _ _ __ ___   ___ | |\n");
    printf("  | |/ _ \\| '_ ` _ \\ / _ \\| | | | |  _| | | | '_ ` _ \\ / _ \\| |\n");
    printf("  | | (_) | | | | | | (_) | |_| | | | | |_| | | | | | | (_) |_|\n");
    printf("  \\_/\\___/|_| |_| |_|\\___/ \\__,_| \\_|  \\__,_|_| |_| |_|\\___/(_)\n");
    printf("                                                               \n");
    printf("Tente Novamente. Pontuacao: %d\n", snake_size - 1);
}

// Map functions
void CreateMap()
{
    memset(map, ' ', sizeof(map));

    for (size_t x = 0; x < WIDTH; x++)
    {
        map[0][x] = '#';
        map[HEIGHT - 1][x] = '#';
    }

    for (size_t y = 1; y < HEIGHT - 1; y++)
    {
        map[y][0] = '#';
        map[y][WIDTH - 1] = '#';
    }
}

uint32_t RandomInMap(uint32_t min, uint32_t max)
{
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

vec2 RandomCoordInMap()
{
    uint32_t x = RandomInMap(1, WIDTH - 1);
    uint32_t y = RandomInMap(1, HEIGHT - 1);

    while (x == y)
    {
        x = RandomInMap(1, WIDTH - 1);
        y = RandomInMap(1, HEIGHT - 1);
    }

    vec2 v = {x, y};
    return v;
}

// Draw functions
void DrawSnake()
{
    // draw head
    screen[head->pos.y][head->pos.x] = 'O';

    node *aux = head->next;
    while (aux)
    {
        screen[aux->pos.y][aux->pos.x] = 'o';
        aux = aux->next;
    }
}

void DrawMap()
{
    memcpy(screen, map, sizeof(map));

    // draw food
    screen[food.y][food.x] = '@';

    DrawSnake();

    // draw screen
    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
        {
            printf("%c", screen[y][x]);
        }
        printf("\n");
    }
}

void DrawInfo()
{
    printf("Pontuacao: %d\n", snake_size - 1);
    printf("Pressione espaco para sair do jogo.\n");
};

// player functions
uint8_t MovePlayer(int keyPressed)
{
    vec2 new_pos = head->pos;
    switch (keyPressed)
    {
    case W:
        new_pos.y -= 1;
        break;
    case A:
        new_pos.x -= 1;
        break;
    case S:
        new_pos.y += 1;
        break;
    case D:
        new_pos.x += 1;
        break;
    default:
        // do nothing
        break;
    }

    // update all snake nodes
    node *aux = head;
    while (aux)
    {
        vec2 curr = aux->pos;
        aux->pos = new_pos;
        new_pos = curr;
        aux = aux->next;
    }

    // self-collision check
    uint8_t hit = 0;
    if (head->next) {
        hit = (head->pos.x == head->next->pos.x) && (head->pos.y == head->next->pos.y);
    }
    return !hit;
}

void ExtendSnake()
{
    // creating a node
    node *new_node = (node *)malloc(sizeof(node));
    new_node->next = NULL;

    // choosing a free position relative to the last snake node
    // the preference is: right, down, up, left
    const vec2 rel = end->pos;
    new_node->pos = rel;

    if (map[rel.y][rel.x + 1] == ' ')
    { // right
        new_node->pos.x += 1;
    }
    else if (map[rel.y + 1][rel.x] == ' ')
    { // down
        new_node->pos.y += 1;
    }
    else if (map[rel.y - 1][rel.x] == ' ')
    { // up
        new_node->pos.y -= 1;
    }
    else if (map[rel.y][rel.x - 1] == ' ')
    { // left
        new_node->pos.x -= 1;
    }

    // adding the new node
    end->next = new_node;
    end = new_node;
};

uint8_t CheckCollision()
{
    uint8_t hitWall = 0;

    // wall check
    hitWall = map[head->pos.y][head->pos.x] == '#';

    // fruit check
    gotFruit = (head->pos.y == food.y) && (head->pos.x == food.x);

    if (gotFruit)
    {
        ExtendSnake();
        for (size_t i = 0; i < 100; i++)
        {
            food = RandomCoordInMap();
        }
        gotFruit = 0;
        snake_size += 1;
    }

    return !hitWall;
}

int main()
{
    StartMenu();
    ShowInstructions();

    // Generating the map
    CreateMap();
    for (size_t i = 0; i < 100; i++)
    {
        food = RandomCoordInMap();
    }

    // creating the player
    head = (node *)malloc(sizeof(node));
    head->pos = RandomCoordInMap();
    head->next = NULL;
    end = head;

    // initial draw
    DrawMap();
    DrawInfo();

    while (1)
    {
        fflush(stdout);
        int command = getch();
        if (command == SPACE)
            break;

        alive = MovePlayer(command) && CheckCollision();
        if (!alive)
        {
            ShowEndScreen();
            break;
        }

        DrawMap();
        DrawInfo();
    }
    return 0;
}
