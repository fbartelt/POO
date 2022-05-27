#ifndef PONTO3D_H
#define PONTO3D_H
#include <iostream>

#include "ponto2d.h"
using namespace std;

class Ponto3D : public Ponto2D {
 public:
  Ponto3D(double xx = 0.0, double yy = 0.0, double zz = 0.0)
      : Ponto2D(xx, yy), z(zz){};
  friend ostream &operator<<(ostream &op, const Ponto3D &p);
  Ponto3D &operator=(const Ponto2D &p);
  Ponto3D &operator=(const Ponto3D &p);
  void set(double nx = 0.0, double ny = 0.0, double nz = 0.0){
    this->Ponto2D::set(nx, ny);
    z = nz;
  };
  double get_z();

 private:
  double z;
};

ostream &operator<<(ostream &op, const Ponto3D &p) {
  op << endl;
  op << "x = " << p.get_x() << endl;
  op << "y = " << p.get_y() << endl;
  op << "z = " << p.z << endl;
  return op;
}

inline double Ponto3D::get_z(){
  return z;
}

inline Ponto3D &Ponto3D::operator=(const Ponto2D &p) {
  Ponto2D::set(p.get_x(), p.get_y());
  z = 0.0;
  return *this;
}

inline Ponto3D &Ponto3D::operator=(const Ponto3D &p) {
  Ponto2D::set(p.get_x(), p.get_y());
  z = p.z;
  return *this;
}


#endif