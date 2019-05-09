#include "direccio.h"
using namespace std;

///////////////////////////////////////////
//// Implementació de la classe direcció ///


///--- Crear una direcció nova, amb el primer valor de la llista.

/* PRE: cert */
/* POST: Retorna l'objecte direccio inicialitzat amb la direcció NO */
direccio::direccio() {
	this->d = NO;
}

///--- Obtenir la direcció

/* PRE: cert */
/* POST: Retorna la direcció actual  */
direccio::dirs direccio::getDireccio() const {
	return this->d;
}

///--- Veure si el valor de la direcció és el del final de la llista.

/* PRE: cert */
/* POST: Retorna cert si la direcció es stop, d'altra forma retorna fals*/
bool direccio::is_stop() const {
	if (this->d == STOP) return true;
	else return false;
}

///--- canviar el valor de la direccio, posant-li el primer de la llista

/* PRE: cert */
void direccio::init() {
	this->d = NO;
}

///--- Canviar el valor de la direcció pel següent de la llista.
///--- Permet usar instruccions "++d" (on d és de tipus direcció).

/* PRE: cert */
/* POST: Retorna la següent direcció a la actual */
direccio& direccio::operator++() {
  if (this->d != STOP) d=dirs(d+1);
  return (*this);
}

///--- Obtenir les components x,y que representen un moviment 
///--- en aquesta direcció. P.ex  N -> (-1,0), NE -> (-1,1)

/* PRE: cert */
/* POST: Retorna les coordenades corresponents a la direccio actual */
coord direccio::despl() const {
	switch (this->d) {
		case NO:
			return coord(-1,-1);
			break;
		case NE:
			return coord(-1,1);
			break;
		case SE:
            return coord(1,1);
            break;
		case SO:
			return coord(1,-1);
			break;
		case STOP:
			return coord(0,0);
			break;
	}
}

///--- Obtenir un string amb el nom de la direcció.
///--- Aquest mètode és útil per fer debugging.

/* PRE: cert */
/* POST: Retorna la direcció actual en format string */
string direccio::mostra() const {
	switch(this->d) {
	    case NO: 	return "NORD-OEST";	break;
	    case NE: 	return "NORD-EST";	break;
	    case SE: 	return "SUD-EST";	break;
	    case SO: 	return "SUD-OEST";	break;
	    case STOP:	return "STOP";		break;
	}
}
