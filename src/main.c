#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#include "coord.h"
#include "map.h"
#include "sondcoord.h"
#include "pq.h"
#include "sondados.h"
#include "jogador.h"
#include "dominacao.h"

int main()
{
  Map map;
  Sondados sondados;
  Jogadores jogadores;
  Direcao direcoes[DIRECAO_TAM] = {LU, UR, UL, RU, UM, MR, ML, MU};

  Jogador jogador_inicial = {0, 0, 0};
  Jogador *dominado = JOGADOR_NULL;

  int limite_turnos, qtd_sondagem;

  scanf("%ld %ld %*d %d", &jogador_inicial.coord.x, &jogador_inicial.coord.y, &limite_turnos);

  map_inicializa(&map);
  sondados_inicializa(&sondados, 2*limite_turnos);
  jogadores_inicializa(&map, &jogadores, jogador_inicial, limite_turnos);

  for (int turno = 0; turno < limite_turnos; turno++)
  {
    qtd_sondagem = sondar(&map, &jogadores, direcoes);
    if(eh_inicio_jogo(turno, limite_turnos)){
      dominado = dominar_inicial(&map, &jogadores, direcoes, turno);
    }else{
      dominado = dominar(&map, &jogadores, &sondados);
    }
    printf("fimturno\n");
    fflush(stdout);
    ler_resposta_do_juiz(&map, &jogadores, &sondados, qtd_sondagem, dominado, direcoes, eh_inicio_jogo(turno, limite_turnos));
    if(DEBUG)
      print_relatorio_turno(turno, qtd_sondagem, jogadores.tamanho, !jogador_eh_null(dominado));
  }

  if(DEBUG)
    print_relatorio_final();

  //map_destruir(&map);
  return 0;
}