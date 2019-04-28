#include <iostream>
#include <algorithm>
#include <math.h>
#include "escaquer.h"

///////////////////////////////////////////
//// Implementació de la classe escaquer ///

//---- Constructora. Serveix per declarar una variable
//---- de tipus "escaquer" de mida n x n inicialitzada
//---- amb les peces inicials d'una partida de Dames.
//---- Pre: n és parell i n>=8
escaquer::escaquer(nat n) {
  // crea taula de mida n x n
  taula = vector<vector<casella> >(???,vector<casella>(???,casella()));

  // inicialitza les caselles del escaquer
  ???
  
}

//---- Diu si les coord p estan dins dels limits del escaquer.
bool escaquer::dins_limits(coord p) const {
  ???
}

//---- Accedeix a la casella de la coord p del escaquer.
casella& escaquer::operator()(coord p) {
 ???
}


//---- Escriu a la pantalla el contingut del escaquer.
void escaquer::mostra() const {
  ???
}


//---- Escriu a la pantalla el contingut del escaquer marcant amb '?'
//---- les caselles on es poden posar fitxes del color donat.
void escaquer::mostra(int color) const {
  ???
}


//---- Avalua les fitxes del escaquer:
//---- num_caselles_blanques - num_caselles_negres 
int escaquer::avalua() const {
  ???
}

//---- Comprova si es pot despl desde la coordenada cini en la direcció d
//---- Retorna: despl (si es pot despl o no), c (coordenada final després del moviment)
void escaquer::es_pot_despl(coord cini, direccio d, bool &despl, coord &c) const {
  ???
}

//---- Comprova si es pot capturar desde la coordenada cini en la direcció d
//---- Retorna: capturar (si es pot capturar o no), c (coordenada final després de la captura)
void escaquer::es_pot_capturar(coord cini, direccio d, bool &capturar, coord &c) const {
  ???
}


//---- Comprova si es pot posar una peça de color de la coordena c:
//---- Cal comprovar si en una de les 4 direccions hi ha una peça dama del color
//---- o bé en los 2 direccions una peça del color
//---- també es poden capturar fitxes de l'adversari (de color diferent al color donat).
list<coord> escaquer::mov_possibles(coord c) const {
  ???
}


//---- Comprova si el color pot jugar (la peça de color es pot col·locar en algun lloc).
bool escaquer::pot_jugar(int color) const {
  ???
}


//---- Col·loca la fitxa de color a la coordena c i captura les fitxes (si es poden capturar) segons regles de les dames
//---- S'avalua si realment es pot posar la fitxa o no
bool escaquer::posa_fitxa(coord c, coord cf, int color) {
  ???
}
