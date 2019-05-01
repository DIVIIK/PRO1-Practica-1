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
  taula = vector<vector<casella> >(n,vector<casella>(n,casella()));

  // inicialitza les caselles del escaquer
  // Primer les blanques
  int j = 0;
  for (int i = n-1; i > n-4; --i) {
    for (; j < n; j+=2)
      taula[i][j].omple(1);

    if (i == n-1) j = 1;
    else j = 0;
  }

  // Ara les negres
  j = 1;
  for (int i = 0; i < 3; ++i) {
    for (;j < n; j+=2)
      taula[i][j].omple(-1);

    if (i == 0) j = 0;
    else j = 1;
  }

}

//---- Diu si les coord p estan dins dels limits del escaquer.
bool escaquer::dins_limits(coord p) const {
  if ((p.x >= 0 and p.x <= taula.size()) )  return true;
  else return false;
}

//---- Accedeix a la casella de la coord p del escaquer.
casella& escaquer::operator()(coord p) {
  return taula[p.x][p.y];
}


//---- Escriu a la pantalla el contingut del escaquer.
void escaquer::mostra() const {
  cout << endl << " " ;
  for (int i = 1; i <= taula.size(); ++i)
    cout << " " << i ;
  cout << endl;

  for (int i = 0; i < taula.size(); ++i) {
    cout << i+1 ;
    for (int j = 0; j < taula.size(); j++)
      cout << " " << taula[i][j].mostra() ;
    cout << endl;
  }
}


//---- Escriu a la pantalla el contingut del escaquer marcant amb '?'
//---- les caselles on es poden posar fitxes del color donat.
void escaquer::mostra(int color) const {
  // Fem una pasada per guardar les coordenades de dames amb el color especificat.
  vector<coord> coords;
  for (int y = 0; y < taula.size(); ++y)
    for (int x = 0; x < taula.size(); ++x)
      if (taula[y][x].valor() == color ) coords.push_back(coord(x,y));
  
  // Obtenir les caselles amb possible moviment
  for (int i = 0; i < coords.size(); ++i)
    list<coord> coords_possible = mov_possibles(coords[i]);

  // Mostrar per pantalla
  cout << endl << " " ;
  for (int i = 1; i <= taula.size(); ++i)
    cout << " " << i ;
  cout << endl;

  for (int i = 0; i < taula.size(); ++i) {
    cout << i+1 ;
    for (int j = 0; j < taula.size(); j++) {
      if (color == taula[i][j].valor()) {
        cout << " ?" ;
      }
      else cout << " " << taula[i][j].mostra() ;
    }
    cout << endl;
  }
}


//---- Avalua les fitxes del escaquer:
//---- num_caselles_blanques - num_caselles_negres 
int escaquer::avalua() const {
  //???
  return 1;
}

//---- Comprova si es pot despl desde la coordenada cini en la direcció d
//---- Retorna: despl (si es pot despl o no), c (coordenada final després del moviment)
void escaquer::es_pot_despl(coord cini, direccio d, bool &despl, coord &c) const {
  //???
}

//---- Comprova si es pot capturar desde la coordenada cini en la direcció d
//---- Retorna: capturar (si es pot capturar o no), c (coordenada final després de la captura)
void escaquer::es_pot_capturar(coord cini, direccio d, bool &capturar, coord &c) const {
  //???
}


//---- Comprova si es pot posar una peça de color de la coordena c:
//---- Cal comprovar si en una de les 4 direccions hi ha una peça dama del color
//---- o bé en los 2 direccions una peça del color
//---- també es poden capturar fitxes de l'adversari (de color diferent al color donat).
list<coord> escaquer::mov_possibles(coord c) const {
  // Tots els moviments possibles
  list<coord> coords;
  direccio dir;
  dir.init();
  int valor = taula[c.y][c.x].valor(); // El valor de la fixa a moure

  while (not dir.is_stop()) {
    coord coordDiag = (c + dir.despl()); // Les coordenades de la casella diagonal
    int valorDiag = taula[coordDiag.y][coordDiag.x].valor(); // El valor de la casella diagonal
    bool valid = true;

    // Comprovar que no es fora del tauler
    if (not dins_limits(coordDiag)) valid = false;

    // Comprovacions per moviment si es negra 
    if (valor == casella::NEGRA)
      if (direccio::NO | direccio::NE) valid = false; // Mirar si vas cap abaix
    
    // Comprovacions per moviment si es blanca
    if (valor == casella::BLANCA)
      if (direccio::SO | direccio::SE) valid = false; // Mirar si vas cap amunt

    // Comprovacions per l'equip de les negres 
    if (valor == casella::NEGRA or valor == casella::DAMA_NEGRA) {
      // Comprovar si es pot fer captura
      if ((valorDiag == casella::NEGRA) or (valorDiag == casella::DAMA_NEGRA)) valid = false; // Si son del mateix equip no
      else if (valorDiag != casella::LLIURE) { // Tenim una fixa blanca (enemiga) a la diagonal
        coord darrere = coordDiag + dir.despl();
        if (taula[darrere.y][darrere.x].valor() == casella::LLIURE) coordDiag = darrere; // Si no hi ha ninguna darrere, es pot menjar i aquesta es la ubicacio final
        else valid = false; // Captura bloquejada per una fixa darrere
      }
    }

    // Comprovacions per l'equip de les blanques 
    if (valor == casella::BLANCA or valor == casella::DAMA_BLANCA) {
      // Comprovar si es pot fer captura
      if ((valorDiag == casella::BLANCA) or (valorDiag == casella::DAMA_BLANCA)) valid = false; // Si son del mateix equip no
      else if (valorDiag != casella::LLIURE) { // Tenim una fixa negra (enemiga) a la diagonal
        coord darrere = coordDiag + dir.despl();
        if (taula[darrere.y][darrere.x].valor() == casella::LLIURE) coordDiag = darrere; // Si no hi ha ninguna darrere, es pot menjar i aquesta es la ubicacio final
        else valid = false; // Captura bloquejada per una fixa darrere
      }
    }

    if (valid) coords.push_back(coordDiag);
    ++dir;
  }

  return coords;
}


//---- Comprova si el color pot jugar (la peça de color es pot col·locar en algun lloc).
bool escaquer::pot_jugar(int color) const {
  //???
  return true;
}


//---- Col·loca la fitxa de color a la coordena c i captura les fitxes (si es poden capturar) segons regles de les dames
//---- S'avalua si realment es pot posar la fitxa o no
bool escaquer::posa_fitxa(coord c, coord cf, int color) {
  //???
  return true;
}
