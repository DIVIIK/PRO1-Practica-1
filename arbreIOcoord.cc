#include "arbreIOcoord.h"
#include <stack>
#include <string>
#include <fstream>

//Escriptura
string dep="";
ostream& operator<<(ostream &os, const arbre<coord> &x) 
/* Pre: cert */
/* Post: s'han escrit al canal estandard de sortida els elements de x */  
{
  string d1=dep;

  if (x.es_buit()) 
    os<<".";
  else {
    os<< x.arrel().mostra1()<<" h:"<<altura(x)-1<<"\n"<<d1<<" \\__";
    dep = d1+" |  ";
    os<< x.fd();
    os<<"\n"<<d1<<" \\__";
    dep = d1+"    ";
    os<< x.fe();
  }
  dep=d1;
  return os;
}



//---- 

/* PRE: a = A  */
/* POST: El resultat es el nombre de nodes de l'arbre A */
int altura(const arbre<coord> &a) {
  int nnodes;
  if (a.es_buit()) nnodes = 0;
  else {
    arbre<coord> a1 = a.fe();
    arbre<coord> a2 = a.fd();
    int y = altura(a1);
    // HIP: El valor y conte el numero de nodes del fill esquerre de A.
    int z = altura(a2);
    // HIP: El valor z conte el numero de nodes del fill dret de A.
    nnodes = y + z + 1;
  }
  return nnodes;
}

