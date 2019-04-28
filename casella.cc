#include <iostream>
#include "casella.h"

///////////////////////////////////////////
//// Implementació de la classe casella ///

//---- Crea una casella amb valor inicial LLIURE.
casella::casella() {  
  ???
}

//---- Modifica el color de la casella.
void casella::omple(int x) {
  ???
}

//---- Marcar la casella com a visitada.
void casella::marca() {
  ???
}

//---- Desmarca la casella (no visitada). 
void casella::desmarca() {
  ???
}

//---- Obté el contingut de la casella.
int casella::valor() const {
  ???
}

//---- Obté el el caràcter de la casella a dibuxar:
//---- BLANCA -> B, DAMA_BLANCA ->Q, NEGRA -> N, DAMA_NEGRA ->P, LLIURE -> -
char casella::mostra() const {
  ???
}

//---- Consulta si la casella esta marcada com visitada.
bool casella::es_visitada() const {
  ???
}
