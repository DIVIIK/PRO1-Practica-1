#include <string>

//---- La classe "coord" guarda una parella de coordenades


class coord {
  public:
    //---- Una posició esta formada per dues coordenades. 
    //---- Com que x i y són atributs públics, són accessibles
    //---- des del programa. Per exemple:  coord p;  p.x=3;
    //---- Recordeu que x són files i y columnes (no com a les matemàtiques convencionals)
    int x, y;

    //---- La constructora "coord" permet declarar
    //---- variables del tipus, per exemple: coord p;
    coord();

    //---- La constructora "coord(int,int)" permet declarar i
    //---- incialitzar variables del tipus, per exemple: coord p(3,5);
    //---- i també permet construir objectes del tipus "coord" sense 
    //---- declarar cap variable, per exemple: if (taulell(coord(4,5))==...)
    coord(int, int); 

    //---- Suma a la coordenada actual el parell de coordenades donat.
    //---- Per exemple:  t=(3,4) i z=(-1,2),  tindrem t+z = (2,6)
    coord operator+(const coord &) const;

    //---- Compara la coordenada actual el parell de coordenades donat.
    bool operator==(const coord &) const;

    //---- Retorna un string amb el contingut de la coordenada entre paréntesis.
    //---- Aquest mètode és útil per fer debugging.
    //---- Per exemple si x=3 i y=-1, mostra retornaria "(3,-1)"
    std::string mostra() const;

    //---- Retorna un string amb el contingut de la coordenada entre paréntesis
    //---- sumant 1 a cada component. Aquest mètode és útil per fer debugging.
    //---- Per exemple si x=3 i y=-1, mostra1 retornaria "(4,0)"
    std::string mostra1() const;
};
