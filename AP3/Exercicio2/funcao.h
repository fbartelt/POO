#ifndef FUNCAO_H
#define FUNCAO_H
#include <cmath>
#include <iostream>
using namespace std;
class Funcao {
 public:
  // funcao que obtem a integral da funcao pela regra do trapezio
  double getIntegral(double limiteInferior, double limiteSuperior,
                     double intervalos);
  // funcao virtual representando a funcao cuja integral deve ser calculada
  virtual double func(double input) = 0;
  // destrutor
  virtual ~Funcao() {}
};

double Funcao::getIntegral(double limiteInferior, double limiteSuperior,
                           double intervalos) {
  double delta = (limiteSuperior - limiteInferior) / intervalos;
  double sum_fxk = 0;
  for (int i = 1; i < intervalos; i++) {
    sum_fxk += func(limiteInferior + (i * delta));
  }
  double res =
      delta * (sum_fxk + (func(limiteInferior) + func(limiteSuperior)) / 2);
  return res;
}

class Quadratica : public Funcao {
 private:
  double a;
  double b;
  double c;

 public:
  Quadratica(double aa, double bb, double cc) : a(aa), b(bb), c(cc){};
  double func(double input) { return a * pow(input, 2) + b * input + c; };
};

class Senoide : public Funcao {
 public:
  Senoide(){};
  double func(double input) { return sin(input) / input; };
};

class Linear : public Funcao {
 private:
  double a;
  double b;

 public:
  Linear(double aa, double bb) : a(aa), b(bb){};
  double func(double input) { return a * input + b; };
};

#endif