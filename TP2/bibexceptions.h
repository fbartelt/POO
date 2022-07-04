#ifndef BIBEXCEPTIONS_H
#define BIBEXCEPTIONS_H

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class BibliotecaException : public exception {
  string message;

 public:
  BibliotecaException(string const &msg) : message(msg){};
  string get_msg() { return message; };
  virtual string what() = 0;
};

class EmprestimoExcpetion : public BibliotecaException {
  string detailed_msg;

 public:
  EmprestimoExcpetion(string const &msg)
      : BibliotecaException("ERRO de Emprestimo: ") {
    detailed_msg = get_msg() + msg;
  }
  string what() { return detailed_msg; };
};

class DevolucaoExcpetion : public BibliotecaException {
  string detailed_msg;

 public:
  DevolucaoExcpetion(string const &msg)
      : BibliotecaException("ERRO de Devolucao: ") {
    detailed_msg = get_msg() + msg;
  }
  string what() { return detailed_msg; };
};

class RemocaoExcpetion : public BibliotecaException {
  string detailed_msg;

 public:
  RemocaoExcpetion(string const &msg)
      : BibliotecaException("ERRO de Remocao: ") {
    detailed_msg = get_msg() + msg;
  }
  string what() { return detailed_msg; };
};

#endif