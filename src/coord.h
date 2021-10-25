#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

// Coordenadas
typedef struct Coord
{
  long int x;
  long int y;
} Coord;

#define coord_eh_igual(A, B) ((A).x == (B).x && (A).y == (B).y)
#endif // COORD_H_INCLUDED