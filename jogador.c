#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "coord.h"
#include "hashtable.h"

#define Item coord_t
#define pq_key(A) (A.pontos)
#define less(A, B) (pq_key(A) < pq_key(B))

#include "pq.h"
#include "dominacao.h"

void print_relatorio_turno(int turno, int qtd_sondagem, int dominou);

int main()
{
  coord_t jogador_inicial = {0, 0, 0, DOMINADO};
  coord_t dominado = NULL_COORD;
  int limite_de_turnos, dominou = 0, qtd_sondagem;

  scanf("%d %d %d %d", &jogador_inicial.x, &jogador_inicial.y,
        &jogador_inicial.pontos, &limite_de_turnos);

  inicializa_jogadores(&jogador_inicial, limite_de_turnos);
  inicializa_sondados(limite_de_turnos);

  for (int turno = 0; turno < limite_de_turnos; turno++)
  {
    qtd_sondagem = sondar();
    dominado = dominar();
    PRINT("fimturno\n");
    ler_resposta_do_juiz(qtd_sondagem, &dominado);
    if (DEBUG)
      print_relatorio_turno(turno + 1, qtd_sondagem, !coord_eh_null(&dominado));
  }

  if (DEBUG)
    print_relatorio_final(calc_total_pontos(), sondados.N, sondados.capacity);

  free(jogadores);
  free(sondados.pq);
  return 0;
}

// Outros
void print_relatorio_turno(int turno, int qtd_sondagem, int dominou)
{
  static int qtd_colisao_passada = 0;
  int total_pontos = calc_total_pontos();
  LOG("-- turno %d\n", turno);
  LOG("-- qtd sondagem %d\n", qtd_sondagem);
  LOG("-- dominou %d\n", dominou);
  LOG("-- qtd jogadores: %d\n", qtd_jogadores);
  LOG("-- pontos até agora: %d\n", total_pontos);
  LOG("-- PQ: ");
  PQprint(&sondados);
  LOG("-- Quantidade de colisao: %d", qtd_colisao - qtd_colisao_passada);
  LOG("\n\n");
  qtd_colisao_passada = qtd_colisao;
}