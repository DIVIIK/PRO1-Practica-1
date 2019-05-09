#include <sstream>
#include "coord.h"

using namespace std;


///////////////////////////////////////////
//// Implementació de la classe coord ///

//---- Crear un parell de coordenades sense valor inicial

/* PRE: cert */
/* POST: Retorna un tipus coordenada sense inicialitzar */
coord::coord() { }

//---- Crear un nou parell de coordenades, amb valor (a,b)

/* PRE: a i b son numeros enters, a = x, b = y  */
/* POST: Retorna un tipus coordenada inicialitzat en la fila x, columna y */
coord::coord(int a, int b) { 
  this->x = a;
  this->y = b;
}

//---- Suma a la coordenada actual el parell de coordenades donat.
//---- Per exemple:  t=(3,4) i z=(-1,2),  tindrem t+z = (2,6)

/* PRE: c es la coordenada, c = C */
/* POST: retorna la coordenada resultant de fer la suma de C i l'actual coordenada. */
coord coord::operator+(const coord& c) const {
  return coord(this->x + c.x, this->y + c.y);
}

//---- Compara la coordenada actual el parell de coordenades donat.

/* PRE: c es la coordenada a comparar, c = C */
/* POST: Retorna cert si C i l'actual coordenada son iguals, retorna fals en altre cas. */
bool coord::operator==(const coord &c) const {
  if(this->x == c.x and this->y == c.y) return true;
  else return false;
}

//---- Retorna un string amb el contingut de la coordenada entre paréntesis.
//---- Aquest mètode és útil per fer debugging.
//---- Per exemple si x=3 i y=-1, mostra retornaria "(3,-1)"

/* PRE: cert */
/* POST: Mostra pel canal de sortida la coordenada actual formatada */
string coord::mostra() const {
	stringstream ss;
	ss << "(" << this->x << "," << this->y << ")";
	return ss.str();
}

//---- Retorna un string amb el contingut de la coordenada entre paréntesis
//---- sumant 1 a cada component. Aquest mètode és útil per fer debugging.
//---- Per exemple si x=3 i y=-1, mostra1 retornaria "(4,0)"

/* PRE: cert */
/* POST: /* POST: Mostra pel canal de sortida la coordenada actual +1 formatada */
string coord::mostra1() const {
	stringstream ss;
	ss << "(" << this->x+1 << "," << this->y+1 << ")";
	return ss.str();
}