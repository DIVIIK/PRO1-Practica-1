#include <iostream>
#include "coord.h"

using namespace std;

int main() {

  int x,y;

  // preguntar components 
  cout << " Entreu coordenades: ";
  cin >> x >> y;
  // crear variable coord amb aquestes coordenades
  coord p(x,y);

  cout << " Entreu desplacament: ";
  cin >> x >> y;
  // crear variable coord amb aquestes coordenades
  coord d(x,y);

  // comparar les dues coordenades p i d
  bool iguals = p==d;
  cout<<"Coordenades i desplaçament són iguals: "<<boolalpha<<iguals<<endl;

  // sumar els dos parells de coordenades p + d 
  coord z = p+d;
  cout<<p.mostra()<<" + "<<d.mostra()<<" = "<<z.mostra()<<endl;
}
