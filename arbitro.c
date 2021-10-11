#include <stdio.h>
#include <stdlib.h>

#define LOG(x, args...) {fprintf(stderr, x, ##args); fflush(stderr);}
#define PRINT(x, args...) {printf(x, ##args); fflush(stdout);}
static int mapa[1000][1000];

void imprime_entorno(int L, int C)
{
    for (int i = L - 1; i <= L + 1; i++)
    {   

        LOG("<< ");
        for (int j = C - 1; j <= C + 1; j++)
        {
            LOG(" %3d ", mapa[i][j]);
        }
        LOG("\n");
    }
}

int main(int argc, char **argv)
{
    srand(atoi(argv[1]));

    int Li, Ci, Turno;
    Li = atoi(argv[2]);
    Ci = atoi(argv[3]);
    Turno = atoi(argv[4]);

    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            mapa[i][j] = rand() % 300;

    LOG("==Entorno inicial\n");
    imprime_entorno(Li, Ci);
    LOG("\n");

    // Informacoes para o jogador vao na saida padrao
    // Informacoes recebidas pela entrada padrao
    // Informacoes de debug e acompanhamento via stderr
    PRINT("%d %d %d %d\n", Li, Ci, mapa[Li][Ci], Turno);

    for (int t = 0; t < Turno; t++)
    {
        // jogador pode executar as seguintes operações:
        // sondar L C
        // dominar L C
        // fimturno
        char buf[100];
        while (scanf(" %s", buf) == 1 && buf[0] != 'f')
        {
            int l, c;
            scanf("%d %d", &l, &c);
            //LOG("=== %s %d %d %d\n", buf, l, c, mapa[l][c]);
            fflush(stderr);
            if (buf[0] == 's'){
                PRINT("sondagem %d %d %d\n", l, c, mapa[l][c]);
            }   
            else
                PRINT("dominacao %d\n", mapa[l][c]);
        }
    }
    return 0;
}