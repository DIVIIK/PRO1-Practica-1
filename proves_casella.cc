#include <iostream>
#include "casella.h"

using namespace std;

/// funció que ensenya el que té la casella per dins, usant 
/// els mètodes de la classe.
void mostra_casella(casella c) {
  cout<<"["<<c.mostra()<<"]";
  cout<<boolalpha;
  cout<< "  contingut="<< c.valor();
  cout<< "  visitada="<< c.es_visitada();
  cout<<endl;
}

int main() {
  
  // Proves amb les operacions de 'casella':
  // Omplir-la de diferents maneres, i cridar les operacions
  // de marcar, desmarcar, etc, per comprovar si funcionen.
  casella c;  // una casella lliure
  mostra_casella(c);

  c.omple(casella::BLANCA);  // una casella blanca
  mostra_casella(c);

  c.omple(casella::NEGRA);  // una casella negra
  mostra_casella(c);

  c.omple(casella::DAMA_BLANCA);  // una casella blanca
  mostra_casella(c);

  c.omple(casella::DAMA_NEGRA);  // una casella negra
  mostra_casella(c);

  c.marca();     // una casella marcada com a visitada
  mostra_casella(c);

  c.desmarca();  // la mateixa, desmarcada
  mostra_casella(c);
}
