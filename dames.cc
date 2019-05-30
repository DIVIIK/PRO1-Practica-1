#include "arbreIOcoord.h"

//---- Comprova que la fixa es del teu equip

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      turnActual: turnActual = T. Es el numero asignat a l'equip en el torn actual */
/*      c: coordenada del tauler que indica la fixa en la posicio especifica en el tauler */
/* POST: Retorna cert si la fixa a les coordenades C es de l'equip indicat amb T, d'altra forma retorna fals */
bool comprova_equip(escaquer &e, int &turnActual, coord &c) {
  bool res = true;
  int valorFixa = e(c).valor();

  if (valorFixa == casella::DAMA_BLANCA) valorFixa = casella::BLANCA;
  else if (valorFixa == casella::DAMA_NEGRA) valorFixa = casella::NEGRA;

  if (valorFixa == turnActual) res = true;
  else res = false;
  return res;
}



//---- Inicialitzar l'escaquer de mida N·N i seleccionem el mode de partida (basic o especial)

/* PRE: tamany: tamany = N. Indica cuantes fixes te cada fila/columna del tauler   */
/*      opcio: Pot ser 1 o 2 i indica si es juga en mode jugador contra jugador o contra ordinador */
/* POST: Crea un objecte tipus escaquer inicialitzat amb tamany N */
escaquer començar_partida(int &tamany, int &opcio) {
  //util::neteja();
  cout << endl << "La Dimensió de l'escaquer ha de ser múltiple de 2 i 8 com a minim" << endl;
  cout << "Quina és la Dimensió ? : " ;
  cin >> tamany;
  escaquer e(tamany);

  cout << endl << "Les Opcions disponibles son (1) Bàsic (2) Especial " << endl;
  cout << "Quina opció vols ? : ";
  cin >> opcio;

  //util::neteja();
  return e;
}



//---- Inicialitzar el torn a les peçes indicades i ho indica pel canal de sortida

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      color: color = C. Un nombre que pot ser 1 o -1 indicant quin jugador esta fent el torn */
/*      opcio: Pot ser 1 o 2 i indica si es juga en mode jugador contra jugador o contra ordinador */
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



//---- Mostra pel canal de sortida l'equip que indica amb C

/* PRE: color: color = C. Un nombre que pot ser 1 o -1 indicant quin jugador esta fent el torn */
void mostra(int color) {
  if (color==casella::BLANCA) cout << endl<<"========== Jugador B ==========";
  else if (color==casella::NEGRA) cout << endl<<"========== Jugador N =========="; 
}



//---- L'usuari introdueix les coordenades de fila i columna de la fixa a moure

/* PRE: tamany: Indica cuantes fixes te cada fila/columna del tauler   */
/*      c: coordenada del tauler que introdueix el jugador */
/* POST: Retorna cert si les dades introduidex son valides i volem seguir amb la partida, retorna fals d'altra forma */
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



//---- Evalua i executa els moviments que introdueix el jugador

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      tamany: Indica cuantes fixes te cada fila/columna del tauler   */
/*      color: Un nombre que pot ser 1 o -1 indicant quin jugador esta fent el torn  */
/*      haCapturat: Un boolea referenciat que el fem servir per evaluar si s'ha realitzat una captura */
/* POST: Retorna cert si el moviment es valid i volem seguir amb la partida, retorna fals d'altra forma */
bool introduir_moviment(escaquer &e,int &tamany, int &color, bool &haCapturat) {
  bool seguimJugant = true;
  bool moviment_valid = false;

  while (not moviment_valid and seguimJugant) {

    cout << "Casella Origen" << endl;
    coord cini;
    seguimJugant = demana_coordenades(tamany,cini);

    if (seguimJugant) {
      cout << "Casella Final" << endl;
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

          moviment_valid = e.posa_fitxa(cini,cfin,e(cini).valor());

          //util::neteja();
        } else moviment_valid = false;
      }
      
      if (seguimJugant and not moviment_valid) cout << "Error: Posició ja ocupada o moviment no vàlid."<< endl;

    }
  }
  return seguimJugant;
}


//---- Indica quin equip va guanyant

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
void avalua(escaquer &e) {
  int val = e.avalua();
  if (val > 0) cout<<"Guanyen les blanques."<<endl;
  else if (val < 0) cout<<"Guanyen les negres."<<endl;
  else cout<<"EMPAT"<<endl;
}



//---- Mira si queden fixes de un dels dos equips per saber si ha acabat la partida

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      tamany: Indica cuantes fixes te cada fila/columna del tauler   */
/* POST: El resultat de la funció sera cert si no queden mes fixes de un dels dos equips, d'altra forma sera fals  */
bool hem_acabat(escaquer &e, int &tamany) {
  bool res = false;
  int b = 0;
  int n = 0;
  for (int x = 0; x < tamany; ++x)
    for (int y = 0; y < tamany; ++y)
      if (e(coord(x,y)).valor() == casella::NEGRA or e(coord(x,y)).valor() == casella::DAMA_NEGRA) ++n;
      else if (e(coord(x,y)).valor() == casella::BLANCA or e(coord(x,y)).valor() == casella::DAMA_BLANCA) ++b;
  if (n == 0 or b == 0 ) res = true;
  return res;
}



//---- Donat un arbre amb unes coordenades inicials, omple els seus dos fills, que son les captures possibles

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      a: a = A. Serà buit si no pot capturar ninguna fixa, sino serà l'arbre amb la millor captura possible */
/*      dama: cert si l'arrel de A son les coordenades que indican la posicio d'una dama al tauler, fals d'altra forma */
void busca_Fills(escaquer &e, arbre<coord> &a, bool &dama) {
  vector<coord> cfins;
  arbre<coord> empty;
  coord cfin;
  coord cini = a.arrel();
  direccio dir;
  dir.init();

  // Busquem la direccio
  while (not dir.is_stop()) {
    cfin = cini + dir.despl() + dir.despl();
    cfins.push_back(cfin);
    if (e.dins_limits(cfin)) {
      
      bool esPot = false;
      e.es_pot_capturar(cini, dir, esPot, cfin);

      if (esPot) {
        // 5 - Si es pot capturar direccio OEST es creara un node fill esquerre amb les coordenades finals despres de la captura
        if (dir.mostra() == "SUD-OEST" and not dama) a = arbre<coord> (cini, arbre<coord>(cfin, empty, empty), a.fd());
        // 5 - Si es pot capturar direccio EST es creara un node fill esquerre amb les coordenades finals despres de la captura
        else if (dir.mostra() == "SUD-EST" and not dama) a = arbre<coord> (cini, a.fe(), arbre<coord>(cfin, empty, empty));
        
        // Si es Dama
        else if (dir.mostra() == "NORD-OEST" and dama) a = arbre<coord> (cini, a.fe(), arbre<coord>(cfin, empty, empty));
        else if (dir.mostra() == "NORD-EST"  and dama) a = arbre<coord> (cini, arbre<coord>(cfin, empty, empty), a.fd());
      }
    }
    ++dir;
  }
}



//---- Donat un arbre amb unes coordenades inicials, l'omple fins al final amb les possibles captures

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      a: a = A. Arbre binari del cual es buscaran els seus fills esquerre i dret */
/*      dama: cert si l'arrel de A son les coordenades que indican la posicio d'una dama al tauler, fals d'altra forma */
void omple_Arbres(escaquer &e, arbre<coord> &a, bool dama) {
  // 5 - El proces es repeteix amb el fill esquerre i fill dret fins que no es piguin capturar mes peces
  if (not a.es_buit()) {
    busca_Fills(e,a,dama);
    arbre<coord> fe = a.fe();
    arbre<coord> fd = a.fd();

    escaquer temp(0);
    temp = e;

    if (not fe.es_buit()) {
      temp.posa_fitxa(a.arrel(), fe.arrel(), e(a.arrel()).valor());
      omple_Arbres(temp,fe,dama);
      // HIP: fe es un arbre amb fills esquerre i drets, aquestos poden estar buits o no
    }
    
    temp = e;
    if (not fd.es_buit()) {
      temp.posa_fitxa(a.arrel(), fd.arrel(), e(a.arrel()).valor());
      omple_Arbres(temp,fd,dama);
      // HIP: fd es un arbre amb fills esquerre i drets, aquestos poden estar buits o no
    }

    // Creem l'arbre definitiu amb els fills dels arbres esquerre i dret
    a = arbre<coord> (a.arrel(), fe, fd);
  }
}



//---- Ens indica si l'arbre referenciat conté alguna dama a un dels seus nodes

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      a: a = A  */
/* POST: cert si hi ha una dama a A, fals d'altra forma */
bool cami_amb_Dama(escaquer &e, arbre<coord> &a) {
  bool res = false; 
  if (not a.es_buit()) {
    arbre<coord> a1 = a.fe();
    arbre<coord> a2 = a.fd();

    // Mirar valor fixa a capturar
    direccio dir;
    dir.init();
    coord cini = a.arrel();
    coord cfin;
    int valorFixa;
    bool trobat = false;

    while (not dir.is_stop() and not trobat) {
      cfin = cini + dir.despl() + dir.despl();  

      if (not a1.es_buit()) if (cfin == a1.arrel()) trobat = true;
      if (not trobat and not a2.es_buit()) if (cfin == a2.arrel()) trobat = true;

      if (trobat) valorFixa = e(cini + dir.despl()).valor();
      ++dir;
    }
  
    if (valorFixa == casella::DAMA_BLANCA) res = true;
    else {
      if (cami_amb_Dama(e,a1)) res = true;
      if (cami_amb_Dama(e,a2)) res = true;
    }
  }
  return res;
}



//---- Executa l'operació de captura durant el turn de l'ordinador

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      a: a = A. Serà buit si no pot capturar ninguna fixa, sino serà l'arbre amb la millor captura possible */
void captura(escaquer &e, arbre<coord> &a) {
  // 7.(especial) De la llista d'arbres resultant del pas anterior, el programa ha d'escollir moure
  // la peça corresponent a l'arbre amb l'alçada maxima. En cas d'empat s'escollira el cami 
  // que capturi alguna Dama. Si hi ha mes d'un cami amb aquesta situacio el programa escullira
  // un cami a l'atzar.

  if (not a.es_buit()) {
    arbre<coord> fe = a.fe();
    arbre<coord> fd = a.fd();

    // L'arbre esquerre té mes captures
    if (altura(fe) > altura(fd)) {
      e.posa_fitxa( a.arrel(), fe.arrel(), e(a.arrel()).valor() );
      captura(e,fe);

    // L'arbre dret té mes captures
    } else if (altura(fe) < altura(fd)) {
      e.posa_fitxa( a.arrel(), fd.arrel(), e(a.arrel()).valor() );
      captura(e,fd);

    // Els dos arbres tenen la mateixa altura
    } else if (altura(fe) == altura(fd) and (altura(fe) + altura(fd)) != 0) {

      // Mirem si algu captura una DAMA i sino agafem un dels dos de forma aleatoria
      if (cami_amb_Dama(e,fe)) {
        e.posa_fitxa( a.arrel(), fe.arrel(), e(a.arrel()).valor() );
        captura(e,fe);

      } else if (cami_amb_Dama(e,fd)) {
        e.posa_fitxa( a.arrel(), fd.arrel(), e(a.arrel()).valor() );
        captura(e,fd);

      } else {
        int aleatori = rand() % 1;

        if (aleatori == 1) {
          e.posa_fitxa( a.arrel(), fe.arrel(), e(a.arrel()).valor() );
          captura(e,fe);
          // HIP: fe es l'arbre fill de l'arbre inicial
        } else {
          e.posa_fitxa( a.arrel(), fd.arrel(), e(a.arrel()).valor() );
          captura(e,fd);
          // HIP: fd es l'arbre fill de l'arbre inicial
        }
      }
    }
  }
}



//---- Mira si l'ordinador pot fer captura o ha de fer un moviment de fixa estandard i ho executa

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      arbres: Llista d'arbres amb les possibles captures de cada fixa de l'equip de l'ordinador que té al tauler */
/*      coords: vector de coordenades de les fixes del torn de l'ordinador */
/*      a: a = A. Serà buit si no pot capturar ninguna fixa, sino serà l'arbre amb la millor captura possible */
void moviment_Ordinador(escaquer &e, list<arbre<coord> > &arbres, vector<coord> &coords, arbre<coord> &a) {
  // 8. (especial) En cas que la llista d'arbres sigui buida (Vol dir que cap de les peces pot capturar) el programa escollira
  // aleatoriament un desplaçament de peça si es possible.
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
      int aleatori;
      if (v_moviments.size() == 1) aleatori = 0; 
      else aleatori = rand() % (v_moviments.size());

      list<coord> moviments = v_moviments[aleatori];
      coord cini = cinis[aleatori];

      // Coordenada final aleatoria
      aleatori = rand() % moviments.size();
      list<coord>::iterator it = moviments.begin();
      for (int i = 0; i < aleatori; ++i) ++it;

      coord cfin = *it;
      e.posa_fitxa(cini, cfin, e(cini).valor());
      cout << "Movimiento de " << cini.mostra1() << " a " << cfin.mostra1() << endl;
    }    

  // Capturo
  } else if (not a.es_buit()) {
    cout << "L'arbre construit es" << endl << a << endl  << " i té alçada " << altura(a)-1 << endl;
    captura(e,a);
  } else cout << "Ni capturo ni muevo" << endl;
}



//---- Gestiona el torn de l'ordinador cuan juguem en mode especial.

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      tamany: Indica cuantes fixes te cada fila/columna del tauler   */
/*      haCapturat: cert. Un boolea referenciat que el fem servir per evaluar si s'ha realitzat una captura */
void torn_Ordinador(escaquer &e, int &tamany, bool &haCapturat) {
  mostra(-1);
  e.mostra(-1);
  cout << "================================" << endl << endl;

  avalua(e);
  cout << "Es el torn de l'ordinador" << endl;

  //// Generar arbre ////
  arbre<coord> empty;
  arbre<coord> arb;
  arbre<coord> arb2;
  arbre<coord> arb_Max;
  list<arbre<coord> > arbres;
  list<arbre<coord> >::iterator it = arbres.begin();
  // Obtenir coordenades
  vector<coord> coords;
  for (int x = 0; x < tamany; ++x) {
    for (int y = 0; y < tamany; ++y) {
      if (e(coord(x,y)).valor() == casella::NEGRA or e(coord(x,y)).valor() == casella::DAMA_NEGRA) {
        coords.push_back(coord(x,y));
        
        // 5.(especial) Els passos a seguir en la construccio de l'arbre donada una peça normal que pot capturar
        // son els seguents

        // - L'arrel de l'arbre contindra les coordenades de la peça que es pot moure
        arb = arbre<coord>(coord(x,y),empty,empty);

        // Obtenim els moviments de la fixa
        omple_Arbres(e,arb,false);
        
        // Analitzem els moviments que pot fer la fixa, nomes guardem les captures!
        if (altura(arb) > 1) {
          arbres.insert(it,arb);
          haCapturat = true;
        }

        // 6.(especial) Si la peça es una Dama i pot capturar donat que es pot moure en les 4 direccions
        // es crearan dos arbres
        if (e(coord(x,y)).valor() == casella::DAMA_NEGRA) {
          arb2 = arbre<coord>(coord(x,y),empty,empty);
            omple_Arbres(e,arb2,true);
          if (altura(arb2) > 1) {
            arbres.insert(it,arb2);
            haCapturat = true;
          }
          // cout << "DEBUG:" << arb2 << endl;
        }

        //cout << "DEBUG: Tots els arbres" << endl << arb << endl;

        // Escollim l'arbre amb mes altura, despres escollirem el millor cami de l'arbre
        if (altura(arb) > 1 and altura(arb) > altura(arb_Max)) arb_Max = arb;
        else if (altura(arb) == altura(arb_Max)) {
          // Si tenim dos camins iguals, tindra prioritat aquell que capturi una dama
          if (cami_amb_Dama(e,arb)) arb_Max = arb;
        }

        // Si tenim una dama hem de jugar amb els dos arbres per trobar el millor cami
        if (e(coord(x,y)).valor() == casella::DAMA_NEGRA) {
          if (altura(arb2) > 1 and altura(arb2) > altura(arb_Max)) {
            arb_Max = arb2;
          } else if (altura(arb2) == altura(arb_Max)) {
            // Si tenim dos camins iguals, tindra prioritat aquell que capturi una dama
            if (cami_amb_Dama(e,arb2)) arb_Max = arb2;
          }
          
        }
        //if (altura(arb) > 1) cout << "DEBUG: Tots els arbres amb captura" << endl << arb << endl;
      }
    }
  }

  //util::espera(0.6);
  moviment_Ordinador(e,arbres,coords,arb_Max);
  //util::espera(1.7);
  //util::neteja();
}



//---- Gestiona el torn dels jugadors de forma que puguin introduir moviments

/* PRE: e: Ojecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
/*      torn actual: Un nombre que pot ser 1 o -1 indicant quin jugador esta fent el torn  */
/*      aux: Serà cert si no es el primer torn d'altra forma sera fals   */
/*      tamany: Indica cuantes fixes te cada fila/columna del tauler   */
/*      haCapturat: cert. Un boolea referenciat que el fem servir per evaluar si s'ha realitzat una captura */
/* POST: cert si s'ha pogut realitzat el moviment, fals d'altra forma */
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



//---- Un cop acaba la partida, mostrar per pantalla el resultat

/* PRE: e es l'objecte instanciat de la classe escaquer que conté el tauler i les operacions necessaries per jugar una partida */
void terminar(escaquer &e) {
  //util::neteja();
  cout << "---- FINAL DE PARTIDA ----" << endl;
  cout << "================================";
  e.mostra();
  cout<<endl;
  avalua(e);
}

//---- Programa principal

int main() {
  int tamany, opcio;
  coord posicio;

  // 1. Inicialitzar l'escaquer de mida n·n
  escaquer e = començar_partida(tamany, opcio);

  // 2. Inicialitzar el torn a les peçes BLANQUES
  int torn_actual;
  passa_torn(e, torn_actual, opcio);

  bool seguimJugant = true; // Si ha ficat coordenades fora del tauler indica que acaba la partida
  bool aux = false; // Per no mostrar avalua el primer torn
  bool haCapturat;
  while (seguimJugant) {
    haCapturat = false;

    // 3. Comprovar que el jugador que te el torn pugui fer algun moviment. 
    //    En cas que no pugui, haurà de passar el torn al seu contrincant.
    int temp;
    if (torn_actual == casella::NEGRA) temp = casella::DAMA_NEGRA;
    else if (torn_actual == casella::BLANCA) temp = casella::DAMA_BLANCA;

    if (not e.pot_jugar(torn_actual) and not e.pot_jugar(temp)) {
      cout << "El jugador no pot jugar ninguna peça.";
      passa_torn(e, torn_actual, opcio);
    }

    // 4.(especial) Quan és el torn de l'ordinador el programa generarà una llista d'arbres corresponents a les diferents peces que es poden moure.
    if (opcio == 2 and torn_actual == casella::NEGRA) torn_Ordinador(e,tamany,haCapturat);
    // 4. Mostrar per pantalla l’escaquer indicant els moviments possibles que te la persona amb el torn.
    else seguimJugant = torn_Jugador(e,torn_actual,aux,tamany,haCapturat);

    // 9. Mostrar el resultat provisional de la partida i canviar el torn si no s'ha produit una captura
    if (seguimJugant) {
      if (not haCapturat) passa_torn(e, torn_actual, opcio);
      else if (opcio == 1 ) mostra(torn_actual);
    }

    if (hem_acabat(e,tamany)) seguimJugant = false;
  }  // 10. Repetir el procediment desde 3 fins acabar la partida o algun dels dos jugadors vulgui aturar

  // 11. Tant si s'acaba la partida com si s'ha aturat sense finalitzar-la, es mostra per pantalla l'escaquer 
  //     i el resultat final de la partida, és a dir qui ha guanyat
  terminar(e);
}