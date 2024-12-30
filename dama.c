#include <stdio.h>
#include <stdbool.h>

void show (char *game, int sizex, int sizey){

    printf("\n  ");
    for (size_t j = 1; j < sizey+1; j++) // coluna
    {
        printf("  %d ", j);
    }

    printf("< y (columns)\n  ");
    for (size_t j = 0; j < sizey; j++) // coluna
    {
        printf("----");
    }
    printf("\n");

    for (size_t i = 0; i < sizex; i++) // linha
    {
        printf("%d |", i+1);

        for (size_t j = 0; j < sizey; j++) // coluna
        {
            printf(" %c |", *(game + i*sizex + j));
        }

        printf("\n  ");

        for (size_t j = 0; j < sizey; j++) // coluna
        {
            printf("----");
        }

        printf("-\n");
    }

    printf("^\nx (lines)\n");
}

void clear (char *game, int sizex, int sizey){
    for (size_t i = 0; i < sizex; i++) // linha
    {
        for (size_t j = 0; j < sizey; j++) // coluna
        {
            *(game + i*sizex + j) = ' ';
        }
    }
}

bool velha (char *game, int sizex, int sizey){

    for (size_t i = 0; i < sizex; i++) // linha
    {
        for (size_t j = 0; j < sizey; j++) // coluna
        {
            if (*(game + i*sizex + j) == ' ') return false;
        }
    }
    return true;
}

bool valid (char *game, int sizex, int sizey, int x, int y, char player){
    /*
    -1,-1 -1,0 -1,1
     0,-1  0,0  0,1
     1,-1  1,0  1,1
    */

   int newx;
   int newy;

   // Lê envolta da marcação feita
   for (int i = -1; i <= 1; i++)
   {
        for (int j = -1; j <= 1; j++)
        {
            newx = x + i;
            newy = y + j;

            // Vê se não esta fora do escopo da matriz e se não é ele mesmo
            if (!(i == 0 && j == 0) && (newx <= 3 && newx > 0) && (newy <= 3 && newy > 0))
            {
                // Verifica se é dele para vencer
                if (*(game + (newx-1)*sizex + newy-1) == player)
                {
                    newx = newx + i;
                    newy = newy + j;

                    // Atualiza valores para dar a volta no tabuleiro e verificar a peça
                    if (!(newx <= 3 && newx > 0 && newy <= 3 && newy > 0))
                    {
                        newx = x - i;
                        newy = y - j;
                    }

                    // Verifica se o próximo quadrado da mesma direção é dele, caso sim vitória
                    if (*(game + (newx-1)*sizex + newy-1) == player && (newx <= 3 && newx > 0 && newy <= 3 && newy > 0)){
                        return true;
                    }
                }
            }
        }
   }

   return false;
}

int main () {
    char game[3][3] = {};
    bool running = true;
    char overagain = 'Y';
    int x, y;
    char player = 'X';
    

    while (overagain == 'y' || overagain == 'Y')
    {
        clear((char *)game, 3, 3);

        while (running)
        {
            show((char *)game, 3, 3);

            printf("Vez do jogador %c...\nFaca sua jogada:\n\n", player);

            while (true)
            {
                printf("x: ");
                scanf("%d", &x);
                getchar();
                printf("y: ");
                scanf("%d", &y);
                getchar();
                if ((x <= 3 && x > 0) && (y <= 3 && y > 0))
                {
                    if (game[x-1][y-1] == ' ') 
                    {
                        game[x-1][y-1] = player;
                        break;
                    }
                    else printf("Essa casa ja esta ocupada!\nTente novamente...\n");
                }
                else printf("Posicao invalida!\nTente novamente...\n\n");
                
            }

            if (valid((char *)game, 3, 3, x, y, player)){
                printf("Parabens!, o jogador %c venceu o jogo!\n", player);
                break;
            } else if (velha((char *)game, 3, 3))
            {
                printf("Jogo deu velha!\n");
                break;
            }
            

            player = (player == 'X') ? 'O' : 'X';
        }

        printf("Deseja jogar novamente(y, n): ");
        scanf("%c", &overagain);
    }
    

    
    return 0;
}