#include "direccio.h"
using namespace std;

///////////////////////////////////////////
//// Implementació de la classe direcció ///


///--- Crear una direcció nova, amb el primer valor de la llista.
direccio::direccio() {
  ???;
}

///--- Obtenir la direcció
??? direccio::getDireccio() const {
  ???
}


///--- Veure si el valor de la direcció és el del final de la llista.
??? direccio::is_stop() const {
  ???
}

///--- canviar el valor de la direccio, posant-li el primer de la llista
void direccio::init() {
  ???
}

///--- Canviar el valor de la direcció pel següent de la llista.
///--- Permet usar instruccions "++d" (on d és de tipus direcció).
direccio& direccio::operator++() {
  if (not ???) d=dirs(d+1);
  return (*this);
}  

///--- Obtenir les components x,y que representen un moviment 
///--- en aquesta direcció. P.ex  N -> (-1,0), NE -> (-1,1)
??? direccio::despl() const {
  ???
}


///--- Obtenir un string amb el nom de la direcció.
///--- Aquest mètode és útil per fer debugging.
??? direccio::mostra() const {
  ???
}
