#include <stdio.h>
#include <stdlib.h>

#define LOG(x, args...) (fprintf(stderr, x, ##args))
static int mapa[1000][1000];

void imprime_entorno(int L, int C)
{
    for (int i = L - 1; i <= L + 1; i++)
    {
        for (int j = C - 1; j <= C + 1; j++)
        {
            LOG(" %d ", mapa[i][j]);
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
    printf("%d %d %d %d\n", Li, Ci, mapa[Li][Ci], Turno);
    fflush(stdout);

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
            if (buf[0] == 's')
                printf("sondagem %d %d %d\n", l, c, mapa[l][c]);
            else
                printf("dominacao %d\n", mapa[l][c]);
        }
    }
    fflush(stdout);
    return 0;
}