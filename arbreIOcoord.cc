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
    os<< "["<<x.arrel().mostra1()<<"]\n"<<d1<<" \\__";
    dep = d1+" |  ";
    os<< x.fd();
    os<<"\n"<<d1<<" \\__";
    dep = d1+"    ";
    os<< x.fe();
  }
  dep=d1;
  return os;
}

