#ifndef PONTO2D_H
#define PONTO2D_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
using namespace std;

// Constantes para os limites dos IDs [0, 1000).
const int MIN_ID = 0;
const int MAX_ID = 999;

class Ponto2D{
  private:
    // Pontos cartesianos x, y. 
    double x, y;
    // Identificador unico para cada objeto.
    int id;
    // Vetor estatico que contém todos os IDs utilizados.
    static vector<int> id_list;
    // Função que retorna um ID único aleatório para o objeto, com
    // valores pertencentes ao intervalo [MIN_ID, MAX_ID].
    int getNextId();

  public:
    // Construtor do objeto, com valores default x=0.0, y=0.0. Gera
    // ID automaticamente.
    Ponto2D(double xx=0, double yy=0): x(xx), y(yy), id(getNextId()) {cout << "Created Ponto2D with ID: " << id << " at:" << endl; print();};
    // Construtor por copia. O novo objeto tem as mesmas coordenadas que o
    // objeto P a ser copiado, obtendo um ID unico para si.
    Ponto2D(const Ponto2D &P): x(P.x), y(P.y), id(getNextId()) {cout << "Created Ponto2D with ID: " << id << " at:" << endl; print();};
    // Destrutor do objeto. Tambem remove o ID utilizado de <id_list>.
    ~Ponto2D();
    // Imprime as coordenadas do objeto.
    void print() const;
    // Imprime a distancia euclidiana do objeto ate a origem.
    double distToOrig() const;
    // Imprime a distancia euclidiana do objeto ate o ponto P.
    double distTo(const Ponto2D &P) const;
    // Altera as coordenadas do objeto para a resultante da soma de suas
    // coordenadas com as coordenadas de P.
    void sumOf(const Ponto2D &P);
    // Retorna um novo ponto cujas coordenadas sao as resultantes da soma das
    // coordenadas do objeto atual com as coordenadas de P.
    Ponto2D sumOfWithReturn(const Ponto2D &P) const;
    // Permite a soma de dois objetos Ponto2D, retornando um novo ponto cujas 
    // coordenadas sao as resultantes da soma das coordenadas do objeto atual 
    // com as coordenadas de P.
    Ponto2D operator+(const Ponto2D &P) const;
    // Permite a operacao prefixada -- que reduz em uma unidade ambas as
    // coordenadas do objeto atual.
    Ponto2D &operator--();
};

inline void Ponto2D::print() const {
  cout << "\tx: " << x << " y: " << y << endl;
}

inline double Ponto2D::distToOrig() const {
  return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

inline double Ponto2D::distTo(const Ponto2D &P) const {
  return sqrt(pow(x - P.x, 2.0) + pow(y - P.y, 2.0));
}

inline void Ponto2D::sumOf(const Ponto2D &P){
  x += P.x;
  y += P.y;
}

inline Ponto2D Ponto2D::sumOfWithReturn(const Ponto2D &P) const {
  Ponto2D Pnew(*this);
  Pnew.sumOf(P);
  return Pnew;
}

inline Ponto2D Ponto2D::operator+(const Ponto2D &P) const {
  Ponto2D Pnew = this->sumOfWithReturn(P);
  return Pnew;
}

inline Ponto2D &Ponto2D::operator--(){
  x--;
  y--;
  return *this;
}

#endif