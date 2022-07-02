#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "date.h"
#include "publicacao.h"
#include "usuario.h"

using namespace std;

class ItemEmprestimo {
  Date dataDevolucao;

 public:
  Livro livro;
  ItemEmprestimo(Livro const &t_livro) : livro(t_livro) {
    dataDevolucao = Date(0, 0, 0);
  };
  void set_dataDevolucao(Date const &t_data);
  bool operator==(ItemEmprestimo const &t_item) const;
  bool operator==(Livro const &t_livro) const;
};

class Emprestimo {
  int numero;
  Date dataEmprestimo;
  Date dataPrevDevolucao;
  Usuario usuario;
  vector<ItemEmprestimo> itens;
  static int proximoNumero;

 public:
  Emprestimo(Date const &t_dataPrevDevolucao, Usuario const &t_usuario)
      : dataPrevDevolucao(t_dataPrevDevolucao), usuario(t_usuario) {
    numero = proximoNumero;
    proximoNumero += 1;
    dataEmprestimo = Date();
  };
  void empresta_livro(Livro &t_livro);
  void devolve_livro(Livro &t_livro);
  void exclui_livro(Livro &t_livro);
  void devolve_todos_livro();
  void add_item(ItemEmprestimo const &t_itemEmprestimo);
  void remove_item(ItemEmprestimo const &t_itemEmprestimo);
  Usuario &get_usuario();
  bool operator==(Emprestimo const &t_emprestimo) const;
  Emprestimo &operator=(Emprestimo const &t_emprestimo);
};

int Emprestimo::proximoNumero = 0;

void ItemEmprestimo::set_dataDevolucao(Date const &t_data) {
  this->dataDevolucao = t_data;
}

void Emprestimo::empresta_livro(Livro &t_livro) {
  t_livro.emprestimo();
  itens.push_back(ItemEmprestimo(t_livro));
}

void Emprestimo::devolve_livro(Livro &t_livro) {
  t_livro.devolucao();
  vector<ItemEmprestimo>::iterator position =
      find(itens.begin(), itens.end(), t_livro);
  if (position != itens.end()) {
    position[0].set_dataDevolucao(Date());
    itens.erase(position);
  };
}

void Emprestimo::exclui_livro(Livro &t_livro) {
  t_livro.devolucao();
  vector<ItemEmprestimo>::iterator position =
      find(itens.begin(), itens.end(), t_livro);
  if (position != itens.end()) itens.erase(position);
}

void Emprestimo::devolve_todos_livro() {
  for (auto i : itens) {
    i.livro.devolucao();
  }
  itens.clear();
}

void Emprestimo::add_item(ItemEmprestimo const &t_itemEmprestimo) {
  itens.push_back(t_itemEmprestimo);
}

void Emprestimo::remove_item(ItemEmprestimo const &t_itemEmprestimo) {
  vector<ItemEmprestimo>::iterator position =
      find(itens.begin(), itens.end(), t_itemEmprestimo);
  if (position != itens.end()) itens.erase(position);
}

inline Usuario &Emprestimo::get_usuario() { return usuario; }

bool ItemEmprestimo::operator==(ItemEmprestimo const &t_item) const {
  return ((dataDevolucao == t_item.dataDevolucao) && (livro == t_item.livro));
}
bool ItemEmprestimo::operator==(Livro const &t_livro) const {
  return (livro == t_livro);
}

bool Emprestimo::operator==(Emprestimo const &t_emprestimo) const {
  return ((numero == t_emprestimo.numero) &&
          (dataEmprestimo == t_emprestimo.dataEmprestimo) &&
          (dataPrevDevolucao == t_emprestimo.dataPrevDevolucao) &&
          (usuario == t_emprestimo.usuario) && (itens == t_emprestimo.itens));
}

Emprestimo &Emprestimo::operator=(Emprestimo const &t_emprestimo){
  numero = t_emprestimo.numero;
  dataEmprestimo = t_emprestimo.dataEmprestimo;
  dataPrevDevolucao =t_emprestimo.dataPrevDevolucao;
  usuario = t_emprestimo.usuario;
  itens = t_emprestimo.itens;
  return *this;
}

#endif