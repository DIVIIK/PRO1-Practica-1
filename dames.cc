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
int altura(arbre<coord> &a) {
  int nnodes;
  if (a.es_buit()) nnodes = 0;
  else {
    arbre<coord> a1 = a.fe();
    arbre<coord> a2 = a.fd();
    int y = altura(a1);
    int z = altura(a2);
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
        if (dir.mostra() == "SUD-OEST") a = arbre<coord> (cini, arbre<coord>(cfin, empty, empty), a.fd());
        else if (dir.mostra() == "SUD-EST") a = arbre<coord> (cini, a.fe(), arbre<coord>(cfin, empty, empty));

        // Dames
        else if (dir.mostra() == "NORD-OEST" and e(cini).valor() == casella::DAMA_NEGRA) a = arbre<coord> (cini, arbre<coord>(cfin, empty, empty), a.fd());
        else if (dir.mostra() == "NORD-EST"  and e(cini).valor() == casella::DAMA_NEGRA) a = arbre<coord> (cini, a.fe(), arbre<coord>(cfin, empty, empty));
      }
    }
    ++dir;
  }
}



//---- 

/* PRE:  */
void omple_Arbres(escaquer &e, arbre<coord> &a) {
  if (not a.es_buit()) {
    busca_Fills(e,a);
    arbre<coord> fe = a.fe();
    arbre<coord> fd = a.fd();
    
    omple_Arbres(e,fe);
    omple_Arbres(e,fd);

    a = arbre<coord> (a.arrel(), fe, fd);
  }
}



//---- 

/* PRE:  */
void captura(escaquer &e, arbre<coord> &a) {
    if (not a.es_buit()) {
      arbre<coord> fe = a.fe();
      arbre<coord> fd = a.fd();
      if (altura(fe) > altura(fd)) {
        e.posa_fitxa( a.arrel(), fe.arrel(), e(a.arrel()).valor() );
        captura(e,fe);
      } else if (altura(fe) < altura(fd)) {
        e.posa_fitxa( a.arrel(), fd.arrel(), e(a.arrel()).valor() );
        captura(e,fd);
      } else if (altura(fe) == altura(fd) and (altura(fe) + altura(fd)) != 0) {
        int aleatori = rand() % 1;
        if (aleatori == 1) {
          e.posa_fitxa( a.arrel(), fe.arrel(), e(a.arrel()).valor() );
          captura(e,fe);
        }
        else {
          e.posa_fitxa( a.arrel(), fd.arrel(), e(a.arrel()).valor() );
          captura(e,fd);
        }
      } else cout << "Tenemos problemas" << endl;
    }
}



//---- 

/* PRE:  */
void moviment_Ordinador(escaquer &e, list<arbre<coord> > &arbres, vector<coord> &coords, arbre<coord> &a) {


  // No puc capturar, faig moviment aleatori
  if (arbres.empty()) {

    // Buscar una fixa amb moviments per fer la tirada
    vector<coord> cinis;
    vector<list<coord> > v_moviments;
    for (int i = 0; i < coords.size(); ++i) {
      list<coord> temp = e.mov_possibles(coords[i]);
      if (not temp.empty()) {
        v_moviments.push_back(temp);
        cinis.push_back(coords[i]);
      }
    } 

    if (not v_moviments.empty()) {
      // Coordenada inicial aleatoria
      int aleatori = rand() % v_moviments.size()-1;
      list<coord> moviments = v_moviments[aleatori];
      coord cini = cinis[aleatori];

      // Coordenada final aleatoria
      aleatori = rand() % moviments.size();
      list<coord>::iterator it = moviments.begin();
      for (int i = 0; i < aleatori; ++i) ++it;

      coord cfin = *it;
      e.posa_fitxa(cini, cfin, e(cini).valor());
    }    

  // Capturo
  } else if (not a.es_buit()) captura(e,a);
}


//---- 

/* PRE:  */
/* POST:  */
bool cami_amb_Dama(escaquer &e, arbre<coord> &a) {
  bool res = false; 

  if (not a.es_buit()) {
    if (e(a.arrel()).valor() == casella::DAMA_NEGRA) res = true;
    else {
      arbre<coord> a1 = a.fe();
      arbre<coord> a2 = a.fd();
      if (cami_amb_Dama(e,a1)) res = true;
      if (cami_amb_Dama(e,a2)) res = true;
    }
  }
  return res;
}



//---- 

/* PRE:  */
void torn_Ordinador(escaquer &e, int &tamany) {
  avalua(e);
  cout << "Es el torn de l'ordinador" << endl;
  cout << "L'arbre construit es" << endl;

  //// Generar arbre ////
  arbre<coord> empty;
  arbre<coord> arb;
  arbre<coord> arb_Max;
  list<arbre<coord> > arbres;
  list<arbre<coord> >::iterator it = arbres.begin();
  // Obtenir coordenades
  vector<coord> coords;
  for (int x = 0; x < tamany; ++x) {
    for (int y = 0; y < tamany; ++y) {
      if (e(coord(x,y)).valor() == casella::NEGRA or e(coord(x,y)).valor() == casella::DAMA_NEGRA) {
        coords.push_back(coord(x,y));
        arb = arbre<coord>(coord(x,y),empty,empty);
        omple_Arbres(e,arb);
        if (altura(arb) > 1) arbres.insert(it,arb);
        
        // Dames
        if (e(coord(x,y)).valor() == casella::DAMA_NEGRA) {
          arb = arbre<coord>(coord(x,y),empty,empty);
          omple_Arbres(e,arb);
          if (altura(arb) > 1) arbres.insert(it,arb);
        }

        // Seleccionem l'arbre definitiu
        if (altura(arb) > 1 and altura(arb) > altura(arb_Max)) arb_Max = arb;
        else if (altura(arb) == altura(arb)) {
          // Si arb_Max te una dama no es fara res i seguira sent el cami de maxima prioritat,
          // si arb te o no una dama entrará al if.
          if (not cami_amb_Dama(e,arb_Max)) arb_Max = arb;
        }
        //if (altura(arb) > 1) cout << "DEBUG" << endl << arb << endl;
      }
    }
  }

  neteja_visitades(e,tamany);
  util::espera(0.8);
  cout << arb_Max << endl << endl;

  moviment_Ordinador(e,arbres,coords,arb_Max);
  util::espera(1.2);
  util::neteja();
}



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