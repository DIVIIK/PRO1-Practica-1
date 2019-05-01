#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>
#include <iostream>

/// ============================================== ///
///             Definició de tipus                 ///

#define nat unsigned int


/// ============================================== ///
///             Definició operacions               ///

namespace util {

  // netejar pantalla
  void neteja();
  
  // esperar t segons
  void espera(float t);
}

#endif

