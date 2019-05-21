#include <iostream>
#include "escaquer.h"

using namespace std;

//---- Inicialitzar l'escaquer de mida n·n

/* PRE:  */
/* POST: */
escaquer començar_partida(int &tamany, int &opcio) {
  util::neteja();
  cout << " d8888b.  .d8b.  .88b  d88. d88888b .d8888." << endl;
  cout << "88  `8D d8' `8b 88'YbdP`88 88'     88'  YP " << endl;
  cout << "88   88 88ooo88 88  88  88 88ooooo `8bo.   " << endl;   
  cout << "88   88 88~~~88 88  88  88 88~~~~~   `Y8b. " << endl;
  cout << "88  .8D 88   88 88  88  88 88.     db   8D " << endl;
  cout << "Y8888D' YP   YP YP  YP  YP Y88888P `8888Y' " << endl;

  cout << endl << "La Dimensió de l'escaquer ha de ser múltiple de 2 i 8 com a minim" << endl;
  cout << "Quina és la Dimensió ? : " ;
  cin >> tamany;
  escaquer e(tamany);

  cout << endl << "Les Opcions disponibles son (1) Bàsic (2) Especial " << endl;
  cout << "Quina opció vols ? : ";
  cin >> opcio;

  util::neteja();
  return e;
}



//---- Inicialitzar el torn a les peçes indicades

/* PRE:  */
/* POST: */
void passa_torn(escaquer &e, int &color) {
  if (color==casella::BLANCA) {
    cout << endl<<"========== Jugador N ==========";
    color = casella::NEGRA;
  } else if (color==casella::NEGRA) {
    cout << endl<<"========== Jugador B =========="; 
    color = casella::BLANCA;
  } else {
    color = casella::BLANCA;
    cout << endl<<"========== Jugador B ==========";
  }
}



//---- 

/* PRE:  */
/* POST: */
void mostra(int &color) {
  if (color==casella::BLANCA) cout << endl<<"========== Jugador B ==========";
  else if (color==casella::NEGRA) cout << endl<<"========== Jugador N =========="; 
}



//---- 

/* PRE:  */
/* POST: */
bool demana_coordenades(int &tamany, coord &c) {
  int fila, columna;
  bool seguimJugant = true;
 
  // Millor que ficar un operator >> a la classe coord ?
  cout << "Fila i columna (1-" << tamany << "): ";
  cin >> fila;

  if (fila < 1 or fila > tamany) seguimJugant = false;
  else {
    cin >> columna;
    if (columna < 1 or columna > tamany) seguimJugant = false;
    else {
      coord aux(fila-1,columna-1);
      c = aux;
    } 
  }

  return seguimJugant;
}



//---- 

/* PRE:  */
/* POST: */
bool introduir_moviment(escaquer &e,int &tamany, int &color, bool &haCapturat) {
  bool seguimJugant = true;

  cout << "---- Casella origen ----" << endl;
  coord cini;
  seguimJugant = demana_coordenades(tamany,cini);

  if (seguimJugant) {
    cout << endl << "---- Casella final ----" << endl;
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
        } else {
          moviment_fet = e.posa_fitxa(cini,cfin,color);
          haCapturat = false;
        }

        util::neteja();
        if(moviment_fet) {
          //cout << endl << "S'ha pogut realitzar el moviment"<< endl;
        } else {
          //cout << "No s'ha pogut realitzar el moviment!"<< endl;
        }
      } else seguimJugant = false; // cout << "No s'ha pogut realitzar el moviment!"<< endl;
    }
  }
  return seguimJugant;
}



void avalua(escaquer &e) {
  int val = e.avalua();
  if (val > 0) cout<<"Guanyen les blanques."<<endl<<endl;
  else if (val < 0) cout<<"Guanyen les negres."<<endl<<endl;
  else cout<<"EMPAT"<<endl<<endl;
}


//---- 

/* PRE:  */
/* POST: */
void terminar(escaquer &e) {
  util::neteja();
  cout << "---- FINAL DE PARTIDA ----" << endl;
  cout << "================================";
  e.mostra();
  cout<<endl;
  avalua(e);
}

 

//---- Descripcio
int main() {
  // 1. Inicialitzar l'escaquer de mida n·n
  int tamany, opcio;
  bool haCapturat;
  coord posicio;

  escaquer e = començar_partida(tamany, opcio);

  // 2. Inicialitzar el torn a les peçes BLANQUES
  int torn_actual;
  passa_torn(e, torn_actual);

  // 3. Comprovar que el jugador que te el torn pugui fer algun moviment. 
  //    En cas que no pugui, haurà de passar el torn al seu contrincant.
  bool seguimJugant = true;
  bool aux = false;
  while (seguimJugant) {
    if (not e.pot_jugar(torn_actual)) {
      cout << "El jugador no pot jugar ninguna peça.";
      passa_torn(e, torn_actual);
    }

    // 4. Mostrar per pantalla l’escaquer indicant els moviments possibles que te la persona amb el torn.
    e.mostra(torn_actual);
    cout << "================================" << endl << endl;

    // Mostrar el resultat provisional de la partida
    if (aux) avalua(e); 
    else aux = true;

    // 5. Demanar a la persona que te el torn un moviment, es a dir, la posicio inicial (fila, columna)
    //    i la posició final (fila, columna). Si alguna fila o alguna columna no estan entre 1 i n voldra
    //    dir que el joc finalitza i s’executara l'ultim pas 11.
    // 6. Cal comprovar que el moviment sigui valid:
    // 7. Un cop validat el moviment, en el cas d'una captura, el mateix jugador torna a tirar.
    // 8. En el cas que la peça moguda es converteixi en Dama ha de quedar reflectit a l'escaquer.
    seguimJugant = introduir_moviment(e,tamany,torn_actual,haCapturat);
    
    // 9. Mostrar el resultat provisional de la partida i canviar el torn si no s'ha produit una captura
    if (seguimJugant) {
      if (not haCapturat) passa_torn(e, torn_actual);
      else mostra(torn_actual);
    }

  }  // 10. Repetir el procediment desde 3 fins acabar la partida o algun dels dos jugadors vulgui aturar

  // 11. Tant si s'acaba la partida com si s'ha aturat sense finalitzar-la, es mostra per pantalla l'escaquer 
  //     i el resultat final de la partida, és a dir qui ha guanyat
  terminar(e);
}