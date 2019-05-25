#include "arbreIOcoord.h"

//---- Comprova que la fixa es del teu equip

/* PRE: color es l'equip en el torn actual */
/* POST: Retorna cert si es pot realitzar el moviment, d'altra forma retorna fals */
bool comprova_equip(escaquer &e, int &color, coord &c) {
  bool res = true;
  int turnActual = color;
  int valorFixa = e(c).valor();

  if (valorFixa == casella::DAMA_BLANCA) turnActual = casella::BLANCA;
  else if (valorFixa == casella::DAMA_NEGRA) turnActual = casella::NEGRA;

  if (valorFixa == turnActual) res = true;
  else res = false;
  return res;
}



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
void passa_torn(escaquer &e, int &color, int &opcio) {
  if (color==casella::BLANCA) {
    if (opcio != 2) cout << endl<<"========== Jugador N ==========";
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
  bool moviment_valid = false;

  while (not moviment_valid and seguimJugant) {

    cout << "---- Casella origen ----" << endl;
    coord cini;
    seguimJugant = demana_coordenades(tamany,cini);

    if (seguimJugant) {
      cout << endl << "---- Casella final ----" << endl;
      coord cfin;
      seguimJugant = demana_coordenades(tamany,cfin);

      // Comprobar si esta movent una fixa del seu equip
      if (seguimJugant) moviment_valid = comprova_equip(e, color, cini);

      if (seguimJugant and moviment_valid) {
        // Descobrir la direccio
        bool trobat = false;
        direccio dir;
        dir.init();
        while (not dir.is_stop() and not trobat)
          if (cini + dir.despl() == cfin or cini + dir.despl() + dir.despl() == cfin)  trobat = true; else ++dir;

        if (trobat) {
          bool espot;
          e.es_pot_capturar(cini,dir,espot,cfin);
          if (espot) haCapturat = true;
          else haCapturat = false;

          moviment_valid = e.posa_fitxa(cini,cfin,color);

          util::neteja();
        } else moviment_valid = false;
      }
      
      if (seguimJugant and not moviment_valid) cout << "Error: Posició ja ocupada o moviment no vàlid."<< endl;

    }
  }
  return seguimJugant;
}


//---- 

/* PRE:  */
/* POST: */
void avalua(escaquer &e) {
  int val = e.avalua();
  if (val > 0) cout<<"Guanyen les blanques."<<endl;
  else if (val < 0) cout<<"Guanyen les negres."<<endl;
  else cout<<"EMPAT"<<endl;
}



//---- 

/* PRE: a = A  */
/* POST: El resultat es el nombre de nodes de l'arbre A */
int mida(arbre<coord> &a) {
  int nnodes;
  if (a.es_buit()) nnodes = 0;
  else {
    arbre<coord> a1 = a.fe();
    arbre<coord> a2 = a.fd();
    int y = mida(a1);
    int z = mida(a2);
    nnodes = y + z + 1;
  }
  return nnodes;
}



//---- 

/* PRE:  */
/* POST: */
void neteja_visitades(escaquer &e, int &tamany) {
  for (int x = 0; x < tamany; ++x)
    for (int y = 0; y < tamany; ++y)
      e(coord(x,y)).desmarca();
}



//---- 

/* PRE:  */
/* POST: */
void busca_Fills(escaquer &e, arbre<coord> &a) {
  arbre<coord> empty;
  direccio dir;
  dir.init();
  coord cini = a.arrel();
  e(cini).marca();
  while (not dir.is_stop()) {
    coord cfin = cini + dir.despl() + dir.despl();
    if (e.dins_limits(cfin)) {
      bool esPot = false;
      if (not e(cfin).es_visitada()) e.es_pot_capturar(cini, dir, esPot, cfin);
      if (esPot) {
        e(cfin).marca();
        if (dir.mostra() == "NORD-OEST" or dir.mostra() == "SUD-OEST") {
          arbre<coord> temp(cini, arbre<coord>(cfin, empty, empty), a.fd());
          a = temp;
        } else if (dir.mostra() == "NORD-EST" or dir.mostra() == "SUD-EST") {
          arbre<coord> temp(cini, a.fe(), arbre<coord>(cfin, empty, empty));
          a = temp;
        }
      }
    }
    ++dir;
  }
}



void omple_Arbres(escaquer &e, arbre<coord> &a) {
  if (not a.es_buit()) {
    busca_Fills(e,a);
    arbre<coord> fe = a.fe();
    arbre<coord> fd = a.fd();
    
    omple_Arbres(e,fe);
    omple_Arbres(e,fd);

    arbre<coord> temp(a.arrel(), fe, fd);
    a = temp;
  }
}



//---- 

/* PRE:  */
/* POST: */
void torn_Ordinador(escaquer &e, int &tamany) {
  avalua(e);
  cout << "Es el torn de l'ordinador" << endl;
  cout << "L'arbre construit es" << endl;

  //// Generar arbre ////
  arbre<coord> empty;
  list<arbre<coord> > arbres;
  list<arbre<coord> >::iterator it = arbres.begin();
  // Obtenir coordenades
  for (int x = 0; x < tamany; ++x)
    for (int y = 0; y < tamany; ++y)
      if (e(coord(x,y)).valor() == casella::NEGRA) {
        arbre<coord> arb(coord(x,y),empty,empty);
        arbres.insert(it,arb);
        
        omple_Arbres(e, arb);
        //util::espera(0.05);
        cout << arb << endl << endl;
        ++it;
      }

  //list<arbre<coord> >::iterator it_max = it;
      neteja_visitades(e,tamany);
}
  // if (mida(*it) > mida(*it_max)) it_max = it;



//---- 

/* PRE:  */
/* POST: */
bool torn_Jugador(escaquer &e, int &torn_actual, bool &aux, int &tamany, bool &haCapturat) {
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
  return introduir_moviment(e,tamany,torn_actual,haCapturat);
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
  passa_torn(e, torn_actual, opcio);

  // 3. Comprovar que el jugador que te el torn pugui fer algun moviment. 
  //    En cas que no pugui, haurà de passar el torn al seu contrincant.
  bool seguimJugant = true;
  bool aux = false;
  while (seguimJugant) {
    if (not e.pot_jugar(torn_actual)) {
      cout << "El jugador no pot jugar ninguna peça.";
      passa_torn(e, torn_actual, opcio);
    }

    // 4.1 Quan és el torn de l'ordinador el programa generarà una llista d'arbres corresponents a les diferents peces que es poden moure.
    if (opcio == 2 and torn_actual == casella::NEGRA) torn_Ordinador(e,tamany);
    // 4.2 Mostrar per pantalla l’escaquer indicant els moviments possibles que te la persona amb el torn.
    else seguimJugant = torn_Jugador(e, torn_actual, aux, tamany, haCapturat);

    // 9. Mostrar el resultat provisional de la partida i canviar el torn si no s'ha produit una captura
    if (seguimJugant) {
      if (not haCapturat) passa_torn(e, torn_actual, opcio);
      else mostra(torn_actual);
    }

  }  // 10. Repetir el procediment desde 3 fins acabar la partida o algun dels dos jugadors vulgui aturar

  // 11. Tant si s'acaba la partida com si s'ha aturat sense finalitzar-la, es mostra per pantalla l'escaquer 
  //     i el resultat final de la partida, és a dir qui ha guanyat
  terminar(e);
}