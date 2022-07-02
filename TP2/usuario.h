#ifndef USUARIO_H
#define USUARIO_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "date.h"

using namespace std;

class Usuario {
  string nome;
  string cpf;
  string endereco;
  string fone;
  Date dataPenalizacao;

 public:
  Usuario(string const t_nome, string const t_cpf, string const t_endereco,
          string const t_fone)
      : nome(t_nome), cpf(t_cpf), endereco(t_endereco), fone(t_fone) {
    dataPenalizacao = Date();
  };
  Usuario(Usuario const &t_usuario)
      : nome(t_usuario.nome),
        cpf(t_usuario.cpf),
        endereco(t_usuario.endereco),
        fone(t_usuario.fone),
        dataPenalizacao(t_usuario.dataPenalizacao){};

  // Getters
  string get_nome() const { return nome; };
  string get_cpf() const { return cpf; };
  string get_endereco() const { return endereco; };
  string get_fone() const { return fone; };
  Date get_dataPenalizacao() const { return dataPenalizacao; };
  // Setters
  void set_dataPenalizacao(Date const &t_data);
  // Operators
  bool operator==(Usuario const &t_usuario) const;
  Usuario &operator=(Usuario const &t_usuario);
  friend ostream &operator<<(ostream &op, Usuario const &t_usuario);
};

inline void Usuario::set_dataPenalizacao(Date const &t_data){
 dataPenalizacao = t_data; 
}

bool Usuario::operator==(Usuario const &t_usuario) const {
  bool r = (nome == t_usuario.nome) && (cpf == t_usuario.cpf) &&
           (endereco == t_usuario.endereco) && (fone == t_usuario.fone) &&
           (dataPenalizacao == t_usuario.dataPenalizacao);
  return r;
}

Usuario &Usuario::operator=(Usuario const &t_usuario){
  nome = t_usuario.nome;
  cpf = t_usuario.cpf;
  endereco = t_usuario.endereco;
  fone = t_usuario.fone;
  dataPenalizacao = t_usuario.dataPenalizacao;
  return *this;
}

ostream &operator<<(ostream &op, Usuario const &t_usuario) {
  op << "Nome : " << t_usuario.get_nome() << endl;
  op << "  Cpf : " << t_usuario.get_cpf() << endl;
  op << "  Endereco : " << t_usuario.get_endereco() << endl;
  op << "  Telefone : " << t_usuario.get_fone() << endl;
  return op;
}

#endif