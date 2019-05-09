#include <iostream>
#include "casella.h"

///////////////////////////////////////////
//// Implementació de la classe casella ///

//---- Crea una casella amb valor inicial LLIURE.

/* PRE: cert */
/* POST: Retorna un tipus casella inicialitzat com a lliure i no visitada */
casella::casella() {  
  this->color = 0;
  this->visitada = false;
}

//---- Modifica el color de la casella.

/* PRE: -2 <= x <= 2 */
void casella::omple(int x) {
  this->color = x;
}

//---- Marcar la casella com a visitada.

/* PRE: cert */
void casella::marca() {
  this->visitada = true;
}

//---- Desmarca la casella (no visitada). 

/* PRE: cert */
void casella::desmarca() {
  this->visitada = false;
}

//---- Obté el contingut de la casella.

/* PRE: cert */
/* POST: Retorna un valor del -2 al 2 indicant el contingut de la casella */
int casella::valor() const {
	return this->color;
}

//---- Obté el el caràcter de la casella a dibuxar:
//---- BLANCA -> B, DAMA_BLANCA ->Q, NEGRA -> N, DAMA_NEGRA ->P, LLIURE -> -

/* PRE: cert */
/* POST: Retorna, segons el contingut de la casella, la seva representació en carácters */
char casella::mostra() const {
	switch (this->color) {
		case 0:
			return '-';
			break;
		case 1:
			return 'B';
			break;
		case -1:
            return 'N';
            break;
		case 2:
			return 'Q';
			break;
		case -2:
			return 'P';
			break;
		case 3:
			return '?';
			break;
		default:
			return '-';
			break;
	}
}

//---- Consulta si la casella esta marcada com visitada.

/* PRE: cert */
/* POST: Retorna cert si la casella ha sigut marcada com a visitada, d'altra forma retorna fals */
bool casella::es_visitada() const {
  return this->visitada;
}
