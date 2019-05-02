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
  // IMPORTANT!!! coord(x,y) x=files y=columnes

  // inicialitza les caselles del escaquer
  // Primer les blanques
  int j = 0;
  for (int i = n-1; i > n-4; --i) { // Files
    for (;j < n; j+=2) // Columnes
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
  if ( (p.x >= 0 and p.x < taula.size()) and (p.y >= 0 and p.y < taula.size()) )  return true;
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
  for (int x = 0; x < taula.size(); ++x)
    for (int y = 0; y < taula.size(); ++y)
      if (taula[x][y].valor() == color )
        coords.push_back(coord(x,y));
  
  // Copia de la taula original on ficarem els interrogants, per questions 
  // d'eficiencia es una de les millors maneres que hem trobat de fer-ho.
  std::vector<std::vector<casella> > taula_temp = taula;

  // Obtenir les caselles amb possible moviment
  for (int i = 0; i < coords.size(); ++i) {
    list<coord> coords_possible = mov_possibles(coords[i]);
    while (not coords_possible.empty()) {
      coord c = *coords_possible.begin();
      coords_possible.erase(coords_possible.begin());
      taula_temp[c.x][c.y].omple(3); // Asigna l'interrogant
    }
  }

  // Mostrar per pantalla
  cout << endl << " " ;
  for (int i = 1; i <= taula_temp.size(); ++i)
    cout << " " << i ;
  cout << endl;

  for (int i = 0; i < taula_temp.size(); ++i) {
    cout << i+1 ;
    for (int j = 0; j < taula_temp.size(); j++)
      cout << " " << taula_temp[i][j].mostra();
    cout << endl;
  }
}


//---- Avalua les fitxes del escaquer:
//---- num_caselles_blanques - num_caselles_negres 
int escaquer::avalua() const {
  int b = 0;
  int n = 0;

  for (int x = 0; x < taula.size(); ++x)
    for (int y = 0; y < taula.size(); ++y)
      if ( (taula[x][y].valor() == casella::BLANCA) or (taula[x][y].valor() == casella::DAMA_BLANCA)) ++b;
      else if ( (taula[x][y].valor() == casella::NEGRA) or (taula[x][y].valor() == casella::DAMA_NEGRA)) ++n;

  return b-n;
}

//---- Comprova si es pot despl desde la coordenada cini en la direcció d
//---- Retorna: despl (si es pot despl o no), c (coordenada final després del moviment)
void escaquer::es_pot_despl(coord cini, direccio d, bool &despl, coord &c) const {
  despl = true;
  c = (cini + d.despl());
  int valorIni = taula[cini.x][cini.y].valor();

  // Comprovar que no es fora del tauler
  if (not dins_limits(c))
    despl = false;
  else {
    int valorDespl = taula[c.x][c.y].valor();

    // Comprovacions per moviment si es negra
    if ((valorIni == casella::NEGRA or valorIni == casella::DAMA_NEGRA)) {
      
      // Mirar si nomes es negra va cap abaix
      if (valorIni == casella::NEGRA)
        if (d.mostra() == "NORD-EST" or d.mostra() == "NORD-OEST") despl = false; // Amb (direccio::NO | direccio::NE) no funciona be
            
      // Comprovar si hi ha una fixa al desplaçament
      if ((valorDespl == casella::NEGRA) or (valorDespl == casella::DAMA_NEGRA)) despl = false; // Si son del mateix equip
   
      // Mirar si es pot fer captura
      if (despl) es_pot_capturar(cini,d,despl,c);
    }

    // Comprovacions per moviment si es blanca
    if ((valorIni == casella::BLANCA or valorIni == casella::DAMA_BLANCA)) {
      
      // Mirar si nomes es blanca va cap amunt
      if (valorIni == casella::BLANCA)
        if (d.mostra() == "SUD-EST" or d.mostra() == "SUD-OEST") despl = false; // Amb (direccio::SO | direccio::SE) no funciona be
            
      // Comprovar si hi ha una fixa al desplaçament
      if ((valorDespl == casella::BLANCA) or (valorDespl == casella::DAMA_BLANCA)) despl = false; // Si son del mateix equip
   
      // Mirar si es pot fer captura
      if (despl) es_pot_capturar(cini,d,despl,c);
    }
  }
}

//---- Comprova si es pot capturar desde la coordenada cini en la direcció d
//---- Retorna: capturar (si es pot capturar o no), c (coordenada final després de la captura)
void escaquer::es_pot_capturar(coord cini, direccio d, bool &capturar, coord &c) const {
  // valorIni     es la peça a moure
  // valorDespl   es la peça a capturar
  // valorDarrere es la peça darrere de valorDespl
  // cini         es la coord de la peça a moure
  // cDespl       es la coord de la peça a capturar
  // c            es la coord final
  coord cDespl = (cini + d.despl());
  c = (cDespl + d.despl());
  int valorIni = taula[cini.x][cini.y].valor();
  int valorDespl;
  int valorDarrere;
  capturar = true;

  if (not dins_limits(cDespl)) capturar = false;
  else valorDespl = taula[cDespl.x][cDespl.y].valor();

  if (not dins_limits(c)) capturar = false;
  else valorDarrere = taula[c.x][c.y].valor();

  // Si anem amb blanques
  if ((valorIni == casella::BLANCA or valorIni == casella::DAMA_BLANCA))
    if ( (valorDespl == casella::NEGRA) or (valorDespl == casella::DAMA_NEGRA) ) // Tenim una fixa negra (enemiga) a la diagonal
      if (taula[c.x][c.y].valor() != casella::LLIURE) capturar = false; // Si no hi ha ninguna darrere, es pot menjar i aquesta es la ubicacio final

  // Si anem amb negres
  if ((valorIni == casella::NEGRA or valorIni == casella::DAMA_NEGRA))
  if ( (valorDespl == casella::BLANCA) or (valorDespl == casella::DAMA_BLANCA) ) // Tenim una fixa negra (enemiga) a la diagonal
    if (taula[c.x][c.y].valor() != casella::LLIURE) capturar = false; // Si no hi ha ninguna darrere, es pot menjar i aquesta es la ubicacio final

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
  coord coordFin;

  while (not dir.is_stop()) {
    bool valid = true;
    es_pot_despl(c,dir,valid,coordFin);

    if (valid) coords.push_back(coordFin);
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
