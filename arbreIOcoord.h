#ifndef ARBREIOINT_H 
#define ARBREIOINT_H
#include "arbre.h"
#include "coord.h"
#include <iostream>
using namespace std;

arbre<int> construeix_arbre_int (char* nomf);
/* Pre: nomf conte el nom d'un fitxer amb els nodes d'un arbre en
   postordre; per cada node s'indica el seu valor i el nombre de fills */
/* Post: el resultat es un arbre binari creat a partir del nodes que es
   troben al fitxer nomf */  
   
ostream& operator<<(ostream &os, const arbre<coord> &x);
/* Pre: cert */
/* Post: s'han escrit al canal estandard de sortida els elements de x */  

#endif
