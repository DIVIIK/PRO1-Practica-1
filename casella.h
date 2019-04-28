//----  La classe "casella" guarda la informació de les caselles del escaquer
//----  És una classe privada a la que no es pot accedir (ni cal) des del
//----  programa. La informació sobre les caselles d'un escaquer s'obté 
//----  a través de les operacions de la classe "escaquer".

class casella {
  private:
    // Atribut on guardar el contingut de la casella 
    int color;
    // Atribut per saber si la casella esta marcada com a visitada
    bool visitada;

  public:
    // Possibles continguts de les caselles
    static const int BLANCA=1;
    static const int DAMA_BLANCA=2;
    static const int NEGRA=-1;
    static const int DAMA_NEGRA=-2;
    static const int LLIURE=0;

    //---- Crea una casella amb valor inicial LLIURE.
    casella();

    //---- Modifica el color de la casella.
    void omple(int x);
    //---- Marca la casella com a visitada.
    void marca();
    //---- Desmarca la casella (no visitada). 
    void desmarca();
    //---- Obté el contingut (valor) de la casella.
    int valor() const;
    //---- Obté el caràcter de la casella a dibuxar:
    //---- BLANCA -> B, DAMA_BLANCA ->Q, NEGRA -> N, DAMA_NEGRA ->P, LLIURE -> -
    char mostra() const;
    //---- Consulta si la casella esta marcada com visitada.
    bool es_visitada() const;
};

