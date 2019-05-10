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



//---- Inicialitzar l'escaquer de mida n·n

/* PRE:  */
/* POST: */
escaquer començar_partida() {
  cout << endl << endl;
  cout << " d8888b.  .d8b.  .88b  d88. d88888b .d8888." << endl;
  cout << "88  `8D d8' `8b 88'YbdP`88 88'     88'  YP " << endl;
  cout << "88   88 88ooo88 88  88  88 88ooooo `8bo.   " << endl;   
  cout << "88   88 88~~~88 88  88  88 88~~~~~   `Y8b. " << endl;
  cout << "88  .8D 88   88 88  88  88 88.     db   8D " << endl;
  cout << "Y8888D' YP   YP YP  YP  YP Y88888P `8888Y' " << endl;

  cout << endl << "Introdueix el tamany de l'escaquer: " ;
  int n;
  cin >> n;
  escaquer e(n);
  return e;
}



//---- Inicialitzar el torn a les peçes indicades

/* PRE:  */
/* POST: */
void jugar_torn(escaquer &e, int color) {
  if (color==casella::BLANCA) cout << endl<<"============== EQUIP BLANC =============="<<endl;
  else if (color==casella::NEGRA) cout << endl<<"============== EQUIP NEGRE ==============="<<endl; 
}



//---- Descripcio
int main() {
  int torn_actual;

  // 1. Inicialitzar l'escaquer de mida n·n
  escaquer e = començar_partida();

  // 2. Inicialitzar el torn a les peçes BLANQUES
  torn_actual = casella::BLANCA;
  jugar_torn(e, torn_actual);

  // 3. Comprovar que el jugador que te el torn pugui fer algun moviment. 
  //    En cas que no pugui, haurà de passar el torn al seu contrincant.
  if (not e.pot_jugar(torn_actual)) {
    if (torn_actual == casella::BLANCA) jugar_torn(e, casella::NEGRA);
    else jugar_torn(e, casella::BLANCA);
  }

  // 4. Mostrar per pantalla l’escaquer indicant els moviments possibles que te la persona amb el torn.
  e.mostra(torn_actual);
  cout<<endl;

  // 5. Demanar a la persona que te el torn un moviment, es a dir, la posicio inicial (fila, columna)
  //    i la posició final (fila, columna). Si alguna fila o alguna columna no estan entre 1 i n voldra
  //    dir que el joc finalitza i s’executar`a l’u ́ltim pas 11.

  // 6. Cal comprovar que el moviment sigui v`alid:


}
