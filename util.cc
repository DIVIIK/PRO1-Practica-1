#include "util.h"

// netejar pantalla
void util::neteja() {
  char esc=27;
  std::cout<<esc<<"[2J"<<esc<<"[1;1H";
}

// esperar t segons
void util::espera(float t) { 
  useconds_t s=t*1000000;
  usleep(s);
}

