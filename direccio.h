#include <string>

#include "coord.h"

//---- Definició del tipus "direccio", que enumera els valors
//---- possibles de la direcció que podem mirar des d'una
//---- casella qualsevol. Aquest tipus té l'operador d'autoincrement,
//---- que permet modificar una variable de tipus "direccio" amb el valor
//---- de la direcció següent en el sentit de les agulles del rellotge.

class direccio {
   public:
     ///--- Llista de direccions possibles, més STOP per marcar 
     ///--- que no n'hi ha més. 
     enum dirs {NO,NE,SE,SO,STOP};
     ///--- Crear una direcció nova, amb el primer valor de la llista.
     direccio();

     ///--- Obtenir la direcció
     ??? getDireccio() const;

     ///--- Veure si el valor de la direcció és el del final de la llista.
     ??? is_stop() const;

     ///--- Canviar el valor de la direcció, posant-li el primer de la llista.
     void init();

     ///--- Canviar el valor de la direcció pel següent de la llista.
     ///--- Permet usar instruccions "++d" (on d és de tipus direcció).
     ///--- No es pot avançar més enllà de la posició STOP
     direccio& operator++(); 
  
     ///--- Obtenir les components x,y que significa un moviment en 
     ///--- en aquesta direcció. P.ex NE -> (-1,1)
     ??? despl() const;

     ///--- Obtenir un string amb el nom de la direcció.
     ///--- Aquest mètode és útil per fer debugging.
     ??? mostra() const;

   private:
     dirs d;


};
