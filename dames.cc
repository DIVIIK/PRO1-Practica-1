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
escaquer començar_partida(int &tamany) {
  cout << endl << endl;
  cout << " d8888b.  .d8b.  .88b  d88. d88888b .d8888." << endl;
  cout << "88  `8D d8' `8b 88'YbdP`88 88'     88'  YP " << endl;
  cout << "88   88 88ooo88 88  88  88 88ooooo `8bo.   " << endl;   
  cout << "88   88 88~~~88 88  88  88 88~~~~~   `Y8b. " << endl;
  cout << "88  .8D 88   88 88  88  88 88.     db   8D " << endl;
  cout << "Y8888D' YP   YP YP  YP  YP Y88888P `8888Y' " << endl;

  cout << endl << "Introdueix el tamany de l'escaquer: " ;
  cin >> tamany;
  escaquer e(tamany);
  return e;
}



//---- Inicialitzar el torn a les peçes indicades

/* PRE:  */
/* POST: */
void passa_torn(escaquer &e, int &color) {
  if (color==casella::BLANCA) {
    cout << endl<<"============== EQUIP NEGRE =============="<<endl;
    color = casella::NEGRA;
  } else if (color==casella::NEGRA) {
    cout << endl<<"============== EQUIP BLANC ==============="<<endl; 
    color = casella::BLANCA;
  } else {
    color = casella::BLANCA;
    cout << endl<<"============== EQUIP BLANC =============="<<endl;
  }
}



//---- 

/* PRE:  */
/* POST: */
bool demana_coordenades(int &tamany, coord &c) {
  int fila, columna;
  bool seguimJugant = true;
 
  // Millor que ficar un operator >> a la classe coord ?
  cout << "Fila: ";
  cin >> fila;
  if (fila < 1 or fila >= tamany) seguimJugant = false;
  
  if (seguimJugant) {
    cout << "Columna: ";
    cin >> columna;
    if (columna < 1 or columna >= tamany) seguimJugant = false;
      coord c(fila-1,columna-1); // Funciona?
  }

  return seguimJugant;
}



//---- 

/* PRE:  */
/* POST: */
bool introduir_moviment(escaquer &e,int &tamany, int &color) {
  bool haCapturat = true;
  bool seguimJugant = true;

  while (haCapturat) {
    haCapturat = false;

    cout << "---- Peça a moure ----" << endl;
    coord cini;
    seguimJugant = demana_coordenades(tamany,cini);

    if (seguimJugant) {
      cout << endl << "---- Destí ----" << endl;
      coord cfin;
      seguimJugant = demana_coordenades(tamany,cfin);
      
      if (seguimJugant) {
        // Descobrir la direccio
        bool trobat = false;
        direccio dir;
        dir.init();
        while (not dir.is_stop() and not trobat)
          if (cini + dir.despl() == cfin or cini + dir.despl() + dir.despl() == cfin)  trobat = true; else ++dir;

        bool moviment_fet;

        if (trobat) {
          bool espot;
          e.es_pot_capturar(cini,dir,espot,cfin);
          if (espot) {
            moviment_fet = e.posa_fitxa(cini,cfin,color);
            haCapturat = true;
          } else 
            moviment_fet = e.posa_fitxa(cini,cfin,color);

          util::neteja();
          if(moviment_fet) {
            cout << endl << "S'ha pogut realitzar el moviment"<< endl;
            if (haCapturat) cout<<"Torna a tirar"<< endl;
          } else {
            haCapturat = false; // Per asegurarnos que no repeteixi
            cout << "No s'ha pogut realitzar el moviment!"<< endl;
          }
        } else cout << "No s'ha pogut realitzar el moviment!"<< endl;
      }
    }
  }
  return seguimJugant;
}



//---- 

/* PRE:  */
/* POST: */
void terminar(escaquer &e) {
  util::neteja();
  cout << "---- Ha terminat la partida ----" << endl;
  e.mostra(); 

  int val = e.avalua();
  cout<< endl << "El valor del escaquer és: "<<val<<endl;
  if (val > 0)
    cout<<"Guanyen les blanques."<<endl;
  else if (val < 0)
    cout<<"Guanyen les negres."<<endl;
  else
    cout<<"Blanques i negres empaten."<<endl;
}



//---- Descripcio
int main() {
  // 1. Inicialitzar l'escaquer de mida n·n
  int tamany;
  escaquer e = començar_partida(tamany);

  // 2. Inicialitzar el torn a les peçes BLANQUES
  int torn_actual;
  passa_torn(e, torn_actual);

  // 3. Comprovar que el jugador que te el torn pugui fer algun moviment. 
  //    En cas que no pugui, haurà de passar el torn al seu contrincant.
  bool seguimJugant = true;
  while (seguimJugant) {
    if (not e.pot_jugar(torn_actual)) {
      cout << "El jugador no pot jugar ninguna peça.";
      passa_torn(e, torn_actual);
    }

    // 4. Mostrar per pantalla l’escaquer indicant els moviments possibles que te la persona amb el torn.
    e.mostra(torn_actual);
    cout<<endl;

    // 5. Demanar a la persona que te el torn un moviment, es a dir, la posicio inicial (fila, columna)
    //    i la posició final (fila, columna). Si alguna fila o alguna columna no estan entre 1 i n voldra
    //    dir que el joc finalitza i s’executara l'ultim pas 11.
    // 6. Cal comprovar que el moviment sigui valid:
    // 7. Un cop validat el moviment, en el cas d'una captura, el mateix jugador torna a tirar.
    // 8. En el cas que la peça moguda es converteixi en Dama ha de quedar reflectit a l'escaquer.
    seguimJugant = introduir_moviment(e,tamany,torn_actual);

    // 9. Mostrar el resultat provisional de la partida i canviar el torn si no s'ha produit una captura
    if (seguimJugant) {
      e.mostra();
      passa_torn(e, torn_actual);
    }
  }
  // 10. Repetir el procediment desde 3 fins acabar la partida o algun dels dos jugadors vulgui aturar

  // 11. Tant si s'acaba la partida com si s'ha aturat sense finalitzar-la, es mostra per pantalla l'escaquer 
  //     i el resultat final de la partida, és a dir qui ha guanyat
  terminar(e);
}