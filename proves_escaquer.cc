#include <iostream>
#include "escaquer.h"

using namespace std;

void jugades_possibles(escaquer &e, coord ci, direccio d, int color) {
  if (color==casella::BLANCA)
    cout << endl<<"============== BLANCA =============="<<endl;
  else if (color==casella::NEGRA)
    cout << endl<<"============== NEGRA ==============="<<endl;
  else
    cout << endl<<"============== LLIURE ==============="<<endl;

  /// Comprovem si es pot posar una fitxa de color a la coordena c

  list<coord> moviments_possibles = e.mov_possibles(ci);
  cout<<"Es pot moure la fitxa de "<<ci.mostra1()<<": "<<endl;
  list<coord>::iterator it;
  for (it=moviments_possibles.begin(); it!=moviments_possibles.end(); ++it)
    std::cout << ' ' << (*it).mostra1();
  cout<<endl;

}


void prova_moviments(escaquer &e, coord ci, coord cf, int color) {

  if (color==casella::BLANCA)
    cout << endl<<"============== BLANCA =============="<<endl;
  else if (color==casella::NEGRA)
    cout << endl<<"============== NEGRA ==============="<<endl;

  /// Dibuixem l'escaquer amb les caselles on podem tirar 
  e.mostra(color);
  cout<<endl;

  //fem n moviments per fer una captura
  bool moviment_fet = e.posa_fitxa(ci,cf,color);
  
  if(moviment_fet) cout<<"S'ha pogut realitzar el moviment"<<endl;
  else cout<<"No s'ha pogut realitzar el moviment!"<<endl;

  /// Dibuixem l'escaquer després de tirar
  cout << endl<<"============== LLIURE =============="<<endl;
  e.mostra();
  cout<<endl;


  /// Avaluem l'escaquer
  int val = e.avalua();
  cout<<"El valor del escaquer és: "<<val<<endl;
  if (val > 0)
    cout<<"Guanyen les blanques."<<endl;
  else if (val < 0)
    cout<<"Guanyen les negres."<<endl;
  else
    cout<<"Blanques i negres empaten."<<endl;

}


int main() {
  /// Creem un escaquer 8x8
  escaquer e(8);

  /// Dibuixem el escaquer
  e.mostra();

  /// Inicialitzem 10 valors per fer proves
  coord vc[10] = {coord(5,0), coord(5,2), coord(5,4), coord(5,6),
                 coord(2,1), coord(2,3), coord(2,5), coord(2,7),
                 coord(3,3), coord(3,5)
               };
  direccio vd[10];      // Totes inicialitzades amb la direcció NORD-OEST
  int color[10] = {casella::BLANCA, casella::BLANCA, casella::BLANCA, casella::BLANCA, 
                  casella::NEGRA, casella::NEGRA, casella::NEGRA, casella::NEGRA,
                  casella::LLIURE, casella::LLIURE
                };

  for (nat i=0; i<10; i++) {
    jugades_possibles(e, vc[i], vd[i], color[i]);
  }

  /// Inicialitzem valors per fer proves
  coord vc_mov[6] = {coord(5,0), coord(4,1), coord(2,3), coord(3,2),
                    coord(4,1), coord(2,3)
                  };
  int color_mov[3] = {casella::BLANCA, casella::NEGRA, casella::BLANCA};

  cout << endl<<"============== SEQÜÈNCIA MOVIMENTS =============="<<endl;

  prova_moviments(e,vc_mov[0],vc_mov[1],color_mov[0]);
  prova_moviments(e,vc_mov[2],vc_mov[3],color_mov[1]);
  prova_moviments(e,vc_mov[4],vc_mov[5],color_mov[2]);
}
