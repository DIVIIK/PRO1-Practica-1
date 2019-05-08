#include <iostream>
#include <algorithm>
#include <math.h>
#include "escaquer.h"

//________________________________________//
//////////// Metodes privats //////////////

/* PRE: p son les coordenades on actualment es la fixa, color es el tipus de fixa */
void convertir_dama(std::vector<std::vector<casella> > t, coord &p, int &color) {
  // Comproba si encara no es dama i segons l'equip la fila apropiada
  if(color == casella::BLANCA and p.x == 0)
    t[p.x][p.y].omple(color++); // Converteix a dama
  else if (color == casella::NEGRA and p.x == t.size()-1)
    t[p.x][p.y].omple(color--); // Converteix a dama
}

/* PRE: */
/* POST: */
direccio obtenir_direccio(coord &cini, coord &cfin, bool &trobat) {
  trobat = false;
  direccio dir;
  dir.init();

  while (not dir.is_stop() and not trobat) {
    if (cini + dir.despl() == cfin)  trobat = true;

    // Normalitzar coordenades si fa falta
    else if (cini + dir.despl() + dir.despl() == cfin) {
      cfin = cini + dir.despl();
      trobat = true;
    }
    
    else ++dir;
  }

  return dir;
}


/* PRE: */
/* POST: */
void mostra_taula(std::vector<std::vector<casella> > tau) {
  cout << endl << " " ;
  for (int i = 1; i <= tau.size(); ++i)
    cout << " " << i ;
  cout << endl;

  for (int i = 0; i < tau.size(); ++i) {
    cout << i+1 ;
    for (int j = 0; j < tau.size(); j++)
      cout << " " << tau[i][j].mostra();
    cout << endl;
  }
}


///////////////////////////////////////////
//// Implementació de la classe escaquer ///

//---- Constructora. Serveix per declarar una variable
//---- de tipus "escaquer" de mida n x n inicialitzada
//---- amb les peces inicials d'una partida de Dames.

/* PRE: n és parell i n>=8 */
/* POST: crea un vector de vectors de caselles (Una taula de caselles) de n files i n columnes */
escaquer::escaquer(nat n) {
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

/* PRE: p es una coordenada (x,y), p = P */
/* POST: Retorna cert si P <= taula.size(), es a dir que P es troba dintre del escaquer, d'altre forma retorna fals */
bool escaquer::dins_limits(coord p) const {
  if ( (p.x >= 0 and p.x < taula.size()) and (p.y >= 0 and p.y < taula.size()) )  return true;
  else return false;
}

//---- Accedeix a la casella de la coord p del escaquer.

  /* PRE: p es una coordenada (x,y), p = P */
  /* POST: Retorna la casella de l'escaquer corresponent a la coordenada P */
casella& escaquer::operator()(coord p) {
  // Us exemple: 
  // escaquer e(8);
  // e(p).mostra();
  return taula[p.x][p.y];
}


//---- Escriu a la pantalla el contingut del escaquer.
void escaquer::mostra() const {
  mostra_taula(taula);
}


//---- Escriu a la pantalla el contingut del escaquer marcant amb '?'
//---- les caselles on es poden posar fitxes del color donat.

/* PRE: color indica l'equip del cual mostrem els possibles moviments, -3 < color < 4 */
// Fem una pasada per guardar les coordenades de dames amb el color especificat.
void escaquer::mostra(int color) const {
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
  cout << "MOSTRA PER PANTALLA" << endl;
  }

  // Mostrar per pantalla
  mostra_taula(taula_temp);
}


//---- Avalua les fitxes del escaquer:
//---- num_caselles_blanques - num_caselles_negres 

/* POST: Retorna el resultat de restar la cuantitat de peçes blanques i negres que queden al escaquer */
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

/* PRE: cini son les coordenades inicials, d es la direccio on es mou la peça, */
/*      despl indica si pot fer el moviment o no, c son les coordenades finals resultants */ 
void escaquer::es_pot_despl(coord cini, direccio d, bool &despl, coord &c) const {
  despl = true;
  c = (cini + d.despl());
  int valorIni = taula[cini.x][cini.y].valor();

  // Comprovar que no es fora del tauler
  if (not dins_limits(c)) {
    despl = false;
  } else {
    int valorDespl = taula[c.x][c.y].valor();

    // Comprovar si hi ha una fixa al desplaçament
    if (valorDespl != casella::LLIURE) {
      despl = false;
    
    // Comprovacions negra
    } else if ( (valorIni == casella::NEGRA) and (d.mostra() == "NORD-EST" or d.mostra() == "NORD-OEST") ) {
      despl = false;
    
    // Comprovacions blanca            
    } else if ( (valorIni == casella::BLANCA) and (d.mostra() == "SUD-EST" or d.mostra() == "SUD-OEST") )
      despl = false;

    // La coordenada final es la inicial si no es pot realitzar el moviment
    if (not despl) c = cini;

  }
}

//---- Comprova si es pot capturar desde la coordenada cini en la direcció d
//---- Retorna: capturar (si es pot capturar o no), c (coordenada final després de la captura)

/* PRE: cini son les coordenades inicials de la peça a moure, d es la direccio on es mou la peça, */
/*      capturar indica si pot fer la captura o no, c son les coordenades finals resultants */ 
void escaquer::es_pot_capturar(coord cini, direccio d, bool &capturar, coord &c) const {
  coord cDespl = (cini + d.despl());                    // coord de la peça a capturar
  c = (cDespl + d.despl());                             // coord final teorica
  int valorIni = taula[cini.x][cini.y].valor();         // peça a moure
  int valorDespl = taula[cDespl.x][cDespl.y].valor();   // peça a capturar
  int valorDarrere;                                     // peça darrere de valorDespl
  capturar = true;

  if (not dins_limits(c)) {
    capturar = false;
  } else {
    valorDarrere = taula[c.x][c.y].valor();

    // Comprovacions fuego amigo            
    if ( (valorIni == casella::BLANCA or valorIni == casella::DAMA_BLANCA) and (valorDespl == casella::BLANCA or valorDespl == casella::DAMA_BLANCA) ) capturar = false;
    else if ( (valorIni == casella::NEGRA or valorIni == casella::DAMA_NEGRA) and (valorDespl == casella::NEGRA or valorDespl == casella::DAMA_NEGRA) ) capturar = false;

    // Si darrere no esta lliure no es pot capturar
    if (taula[c.x][c.y].valor() != casella::LLIURE) capturar = false;

    // La coordenada final es la inicial si no es pot realitzar la captura
    if (not capturar) c = cini;
  }
}



//---- Comprova si es pot posar una peça de color de la coordena c:
//---- Cal comprovar si en una de les 4 direccions hi ha una peça dama del color
//---- o bé en los 2 direccions una peça del color
//---- també es poden capturar fitxes de l'adversari (de color diferent al color donat).

/* PRE: c son les coordenades de la peça a evaluar, c = C */
/* POST: Retorna una llista amb totes les coordenades posibles on es pot moure C */
list<coord> escaquer::mov_possibles(coord c) const {
  list<coord> coords;
  direccio dir;
  dir.init();
  coord coordFin;
  bool valid;

  while (not dir.is_stop()) {
    es_pot_despl(c,dir,valid,coordFin);
    if (not valid)
      es_pot_capturar(c,dir,valid,coordFin);

    if (valid) coords.push_back(coordFin);
    ++dir;
  }

  return coords;
}


//---- Comprova si el color pot jugar (la peça de color es pot col·locar en algun lloc).
  
/* PRE: color indica l'equip que estem mirant si pot jugar, -3 < color < 4 */
/* POST: Retorna cert si el color pot fer algun moviment amb les fixes del escaquer, si hi han. D'altre forma retorna fals */
bool escaquer::pot_jugar(int color) const {
  bool potJugar = false;
  int x = 0;
  int y = 0;

  while (not potJugar and x < taula.size()) {
    while (not potJugar and y < taula.size()) {
      if (taula[x][y].valor() == color) potJugar = true;
      ++y;
    }
    ++x;
  }

  return potJugar;
}


//---- Col·loca la fitxa de color a la coordena c i captura les fitxes (si es poden capturar) segons regles de les dames
//---- S'avalua si realment es pot posar la fitxa o no

/* PRE: c son les coordenades inicials, cf son les coordenades despres de posar la fixa, si ha sigut possible, */
/*      color indica quin tipus de fixa farà el moviment, -3 < color < 4 */
/* POST: Retorna cert si es possible realitzar el moviment, indicant que s'ha mogut la fixa de c a cf, d'altra forma retorna fals */
bool escaquer::posa_fitxa(coord c, coord cf, int color) {
  bool trobat;
  bool esPot = false;
  
  direccio dir = obtenir_direccio(c,cf,trobat);
  
  // Nomès operacions valides
  if (trobat) {
    es_pot_despl(c,dir,esPot,cf);
    if (not esPot) {
      es_pot_capturar(c,dir,esPot,cf);

      // Fem totes les captures possibles
      if (esPot) {

        // Fa el moviment si es posible
        taula[c.x][c.y].omple(casella::LLIURE);
        taula[(c+dir.despl()).x][(c+dir.despl()).y].omple(casella::LLIURE);
        taula[cf.x][cf.y].omple(color);

        // Marca la casella com a visitada
        taula[cf.x][cf.y].marca();

        // Mira si es pot convertir a dama
        convertir_dama(taula, cf,color);
        
        // Mirem si podem fer mes captures
        esPot = false;
        list<coord> coords = mov_possibles(cf);
        while (not coords.empty() and not esPot) {
          coord co = *coords.begin();
          coords.erase(coords.begin());

          direccio dir = obtenir_direccio(cf,co,trobat);
          if (trobat) es_pot_capturar(cf,dir,esPot,co);
          if (esPot) posa_fitxa(cf,co,color);
        }
      }
    }
  }
  return esPot;
}