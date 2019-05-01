#include <iostream>
#include "casella.h"

///////////////////////////////////////////
//// Implementació de la classe casella ///

//---- Crea una casella amb valor inicial LLIURE.
casella::casella() {  
  this->color = 0;
  this->visitada = false;
}

//---- Modifica el color de la casella.
void casella::omple(int x) {
  this->color = x;
}

//---- Marcar la casella com a visitada.
void casella::marca() {
  this->visitada = true;
}

//---- Desmarca la casella (no visitada). 
void casella::desmarca() {
  this->visitada = false;
}

//---- Obté el contingut de la casella.
int casella::valor() const {
	return this->color;
}

//---- Obté el el caràcter de la casella a dibuxar:
//---- BLANCA -> B, DAMA_BLANCA ->Q, NEGRA -> N, DAMA_NEGRA ->P, LLIURE -> -
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
		default:
			return '-';
			break;
	}
}

//---- Consulta si la casella esta marcada com visitada.
bool casella::es_visitada() const {
  return this->visitada;
}
