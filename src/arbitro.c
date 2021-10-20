#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOG(x, args...) {fprintf(stderr, x, ##args); fflush(stderr);}
#define PRINT(x, args...) {printf(x, ##args); fflush(stdout);}
#ifndef PTS_RANGE
#define PTS_RANGE 100000
#endif
#ifndef DEBUG
#define DEBUG 0
#endif

long int total_pontos = 0;
long int total_colisoes = 0;
long int total_redimensionamentos = 0;

void leia_relatorio_final_jogador(){
    scanf("%ld", &total_colisoes);
    scanf("%ld", &total_redimensionamentos);
}

void print_relatorio_final(){
  leia_relatorio_final_jogador();
  LOG("== Relatorio Final \\ ")
  LOG("pontuação %ld | ", total_pontos);
  LOG("colisoes %ld | ", total_colisoes);
  LOG("resize %ld ", total_redimensionamentos);
  LOG("\\\n");
}

long int gera_pontos(){
    int sinal = (int) pow(-1, rand()%2);
    return sinal * ((16161 * (long int)rand())%PTS_RANGE);
}

void leia_relatorio_turno(int *turno, int *dominou, int *sondagem, int *jogadores, long int *colisao, long int *resize){
	scanf("%d", turno);
  scanf("%d", dominou);
  scanf("%d", sondagem);
  scanf("%d", jogadores);
  scanf("%ld", colisao);
  scanf("%ld", resize);
}

void print_relatorio_turno(){
	int turno, dominou, sondagem, jogadores;
	long int colisao, resize;
	leia_relatorio_turno(&turno, &dominou, &sondagem, &jogadores, &colisao, &resize);

  LOG("-- turno %d\n", turno+1);
  LOG("-- dominou %d\n", dominou);
  LOG("-- qtd sondagem %d\n", sondagem);
  LOG("-- qtd jogadores: %d\n", jogadores);
  LOG("-- pontos até agora: %ld\n", total_pontos);
  LOG("-- Quantidade de colisao: %ld\n", colisao);
  LOG("-- Quantidade de resize: %ld\n", resize);
  LOG("\n");
}
int main(int argc, char **argv)
{
    srand(atoi(argv[1]));

    long int pontos;
    int Li, Ci, Turno;
    Li = atoi(argv[2]);
    Ci = atoi(argv[3]);
    Turno = atoi(argv[4]);

    PRINT("%d %d %d %d\n", Li, Ci, PTS_RANGE, Turno);

    for (int t = 0; t < Turno; t++)
    {
        char buf[100];
        while (scanf(" %s", buf) == 1 && buf[0] != 'f')
        {
            long int l, c;
            scanf("%ld %ld", &l, &c);
            fflush(stderr);
            if (buf[0] == 's'){
                PRINT("sondagem %ld %ld %ld\n", l, c, gera_pontos());
            }   
            else{
                PRINT("dominacao %d\n", 0);
								if(DEBUG){
                	scanf("%ld", &pontos);
                	total_pontos += pontos;
								}
            }
        }
				if(DEBUG)
        print_relatorio_turno();
    }
		if(DEBUG)
    print_relatorio_final();
    return 0;
}