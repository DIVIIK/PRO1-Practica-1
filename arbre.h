#ifndef ARBRE_H
#define ARBRE_H

#include <string>
#include <cstdlib>
#include <iostream>

/// -----------------------------------------
///
///  Declaració operacions tipus ARBRE BINARI
///
/// -----------------------------------------

template <typename T>
class arbre {

  private:
    struct node {
      node* f_esq;
      node* f_dret;
      T info;
    };
    node* _arrel;

    static node* copia_nodes(node* m);
    /* Pre: cert */
    /* Post: si m és NULL, el resultat és NULL; sinó,
       el resultat apunta al primer node d'un arbre binari
       de nodes que són còpia de l'arbre apuntat per m */
    static void esborra_nodes(node* m);
    /* Pre: cert */
    /* Post: no fa res si m és NULL, sinó allibera
       espai dels nodes de l'arbre binari apuntat per m */

  public:
    //constructors
    arbre();
    /* Pre: cert */
    /* Post: el resultat és un arbre sense cap element */
    arbre(const arbre<T> &a);
    /* Pre: cert */
    /* Post: el resultat és una còpia de l'arbre rebut */
    arbre(const T &x,const arbre<T> &ae,const arbre<T> &ad);
    /* Pre: cert */
    /* Post: el resultat és un arbre amb un element i dos
       subarbres */

   //destructor: esborra automàticament els objectes locals
   //en sortir d'un àmbit de visibilitat
   ~arbre();

    //modificadors
    void a_buit();
    /* Pre: cert */
    /* Post: el paràmetre implícit no té cap element */
    arbre<T>& operator=(const arbre<T> &a);
    /* Pre: cert */
    /* Post: operació d'assignació d'arbres  */

   //consultors
   const T& arrel() const;
   /* Pre: el paràmetre implícit no és buit */
   /* Post: el resultat és l'arrel del paràmetre implícit */
   arbre<T> fe() const;
   /* Pre: el paràmetre implícit no és buit */
   /* Post: el resultat és el fill esquerre del p.i. original */
   arbre<T> fd() const;
   /* Pre: el paràmetre implícit no és buit */
   /* Post: el resultat és el fill dret del p.i. original */
   bool es_buit() const;
   /* Pre: cert */
   /* Post: el resultat indica si el p.i. és buit o no */
};


/// ------------------------------------------
///
///  Codificació operacions tipus ARBRE BINARI
///
/// ------------------------------------------

//privades ----------------------
template <typename T>
typename arbre<T>::node* arbre<T>::copia_nodes(node* m) {
  node* n;
  if (m == NULL) n = NULL;
  else {
    n = new node;
    try {
      n->info = m->info;
      n->f_esq = copia_nodes(m->f_esq);
      n->f_dret = copia_nodes(m->f_dret);
    } catch(...) {
      delete n;
      throw;
    }
  }
  return n;
};

template <typename T>
void arbre<T>::esborra_nodes(node* m) {
  if (m != NULL) {
    esborra_nodes(m->f_esq);
    esborra_nodes(m->f_dret);
    delete m;
  }
};

//constructors ----------------------
template <typename T>
arbre<T>::arbre()
/* Pre: cert */
/* Post: el resultat és un arbre sense cap element */
{
  _arrel = NULL;
}

template <typename T>
arbre<T>::arbre(const arbre<T>& a)
/* Pre: cert */
/* Post: el resultat és una còpia de a */
{
  _arrel = copia_nodes(a._arrel);
}

template <typename T>
arbre<T>::arbre(const T& x, const arbre<T>& ae, const arbre<T>& ad)
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret */
{
  _arrel = new node;
  try {
    _arrel->info = x;
    _arrel->f_esq = copia_nodes(ae._arrel);
    _arrel->f_dret = copia_nodes(ad._arrel);
  }
  catch (...) {
    delete _arrel;
    throw;
  }
}

//destructor ----------------------
template <typename T>
arbre<T>::~arbre() {
  esborra_nodes(_arrel);
}

//modificadors ----------------------
template <typename T>
void arbre<T>::a_buit()
/* Pre: cert */
/* Post: el paràmetre implícit no té cap element */
{
  esborra_nodes(_arrel);
  _arrel = NULL;
}

template <typename T>
arbre<T>& arbre<T>::operator=(const arbre<T>& a) {
  if (this != &a) {
    node* aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
}

//consultors ----------------------
template <typename T>
const T& arbre<T>::arrel() const {
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és l'arrel del paràmetre implícit */
  if (this->es_buit()) {
    std::cout<<"ERROR - Operacio 'arrel' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  return _arrel->info;
}

template <typename T>
arbre<T> arbre<T>::fe() const
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és el fill esquerre del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operacio 'fe' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  arbre<T> a;
  a._arrel = copia_nodes(_arrel->f_esq);
  return a;
}

template <typename T>
arbre<T> arbre<T>::fd() const
/* Pre: el paràmetre implícit no és buit */
/* Post: el resultat és el fill dret del p.i. original */
{
  if (this->es_buit()) {
    std::cout<<"ERROR - Operacio 'fd' sobre un arbre buit."<<std::endl;
    exit(1);
  }
  arbre<T> a;
  a._arrel = copia_nodes(_arrel->f_dret);
  return a;
}

template <typename T>
bool arbre<T>::es_buit() const
/* Pre: cert */
/* Post: el resultat indica si el p.i. és buit o no */
{
  return (_arrel == NULL);
}

#endif
