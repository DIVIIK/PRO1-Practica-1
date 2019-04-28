#include <string>
#include <vector>
#include <queue>
#include <list>

#include "direccio.h"
#include "casella.h"
#include "util.h"

using namespace std;

//----  La classe "escaquer" és l'estructura de dades principal de la
//----  pràctica. Guarda la taula n x n amb la informació de les caselles.

class escaquer {
 private:
   //---- Taula per guardar les caselles del escaquer.
   std::vector<std::vector<casella> > taula;

   /// casella lliure extra, per si estem fora dels límits.
   casella lliure;

 public: 
   //---- Constructora. Serveix per declarar una variable
   //---- de tipus "escaquer" de mida n x n inicialitzada
   //---- amb les fitxes inicials d'una partida de Dames.
   //---- Pre: n >=8
   escaquer(nat n);

   //---- Diu si les coord p estan dins dels limits del escaquer.
   bool dins_limits(coord p) const;

   //---- Accedeix a la casella de la coord p del escaquer.
   casella& operator()(coord);

   //---- Escriu a la pantalla el contingut del escaquer.
   void mostra() const;

   //---- Escriu a la pantalla el contingut del escaquer marcant amb 'x' o '?'
   //---- les caselles on es poden posar fitxes del color donat.
   void mostra(int color) const; 

   //---- Avalua les fitxes del escaquer:
   //---- num_caselles_blanques - num_caselles_negres.
   int avalua() const;

   //---- Comprova si es pot despl desde la coordenada cini en la direcció d
   //---- Retorna: despl (si es pot despl o no), c (coordenada final després del moviment)
   void es_pot_despl(coord cini, direccio d, bool &despl, coord &c) const;

   //---- Comprova si es pot capturar desde la coordenada cini en la direcció d
   //---- varies fitxes de l'adversari (al final hem de trobar un color 'nostre').
   //---- Retorna: capturar (si es pot capturar o no), c (coordenada final on s'ha trobat el color donat)
   void es_pot_capturar(coord cini, direccio d, bool &capturar, coord &c) const;

   //---- Comprova si es pot posar una peça de color de la coordena c:
   //---- Cal comprovar si en una de les 4 direccions hi ha una peça dama del color
   //---- o bé en los 2 direccions una peça del color
   //---- també es poden capturar fitxes de l'adversari (de color diferent al color donat).
   list<coord> mov_possibles(coord c) const;

   //---- Comprova si el color pot jugar (la fitxa de color es pot col·locar en algun lloc).
   bool pot_jugar(int color) const;

   //---- Col·loca la fitxa de color a la coordena c i captura les fitxes (si es poden capturar) segons regles de les dames
   //---- S'avalua si realment es pot posar la fitxa o no
   bool posa_fitxa(coord c, coord cf, int color);
};
