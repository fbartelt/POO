#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "date.h"
#include "emprestimo.h"
#include "publicacao.h"
#include "usuario.h"

using namespace std;

class Biblioteca {
  vector<Usuario> usuarios;
  vector<Publicacao> livros;
  vector<Emprestimo> emprestimos;

 public:
  Biblioteca(){};
  void add_usuario(Usuario const &t_usuario);
  void add_publicacao(Publicacao const &t_publicacao);
  void add_emprestimo(Emprestimo const &t_emprestimo);
  void add_item_emprestimo(Emprestimo &t_emprestimo,
                           ItemEmprestimo const &t_itemEmprestimo);
  void remove_usuario(Usuario const &t_usuario);
  // void remove_publicacao(Publicacao const &t_publicacao);
  void remove_emprestimo(Emprestimo const &t_emprestimo);
  void remove_item_emprestimo(Emprestimo &t_emprestimo,
                              ItemEmprestimo const &t_itemEmprestimo);
  void devolve_livro(Emprestimo &t_emprestimo, Livro &t_livro);
  void devolve_todos_livro(Emprestimo &t_emprestimo);
  vector<Publicacao> pesquisa_titulo(string &t_titulo);
  // vector<Livro> pesquisa_autor(string &t_autor);
  vector<Usuario> &get_usuarios();
  vector<Publicacao> &get_publicacoes();
  vector<Emprestimo> &get_emprestimos();
  // void save();
  // void load();
};

// Adicoes
inline void Biblioteca::add_usuario(Usuario const &t_usuario) {
  usuarios.push_back(t_usuario);
}

inline void Biblioteca::add_publicacao(Publicacao const &t_publicacao) {
  livros.push_back(t_publicacao);
}

inline void Biblioteca::add_emprestimo(Emprestimo const &t_emprestimo) {
  emprestimos.push_back(t_emprestimo);
}

inline void Biblioteca::add_item_emprestimo(
    Emprestimo &t_emprestimo, ItemEmprestimo const &t_itemEmprestimo) {
  t_emprestimo.add_item(t_itemEmprestimo);
}

// Remocoes
void Biblioteca::remove_usuario(Usuario const &t_usuario) {
  int counter = 0;
  for (auto i : emprestimos) {
    Usuario temp = i.get_usuario();
    if (temp == t_usuario)
      throw invalid_argument(
          "Nao eh possivel remover o usuairo. Usuario ainda tem emprestimos.");
    else {
      vector<Usuario>::iterator position =
          find(usuarios.begin(), usuarios.end(), t_usuario);
      usuarios.erase(position);
    }
    counter++;
  }
}

void Biblioteca::remove_emprestimo(Emprestimo const &t_emprestimo) {
  vector<Emprestimo>::iterator position =
      find(emprestimos.begin(), emprestimos.end(), t_emprestimo);
  if (position != emprestimos.end()) {
    emprestimos.erase(position);
  };
}

void remove_item_emprestimo(Emprestimo &t_emprestimo,
                            ItemEmprestimo const &t_itemEmprestimo) {
  t_emprestimo.remove_item(t_itemEmprestimo);
}

// Devolucoes
inline void Biblioteca::devolve_livro(Emprestimo &t_emprestimo,
                                      Livro &t_livro) {
  t_emprestimo.devolve_livro(t_livro);
}

inline void Biblioteca::devolve_todos_livro(Emprestimo &t_emprestimo) {
  t_emprestimo.devolve_todos_livro();
}

// Pesquisas
vector<Publicacao> Biblioteca::pesquisa_titulo(string &t_titulo) {
  cout << "chamou";
  vector<Publicacao> matches;
  smatch titulo_match;
  regex titulo_regex(t_titulo);
  for (auto i : livros) {
    cout << " dentro for ";
    string titulo = i.get_titulo();
    if (regex_search(titulo, titulo_match, titulo_regex)) {
      cout << " match";
      matches.push_back(i);
    }
  }
  return matches;
}

// vector<Livro> Biblioteca::pesquisa_autor(string &t_autor) {
//   vector<Livro> matches;
//   smatch autor_match;
//   regex autor_regex(t_autor);
//   for (auto i : livros) {
//     Livro *lv = dynamic_cast<Livro *>(&i);
//     if (lv != nullptr) {
//       string titulo = lv->get_autores();
//       if (regex_search(titulo, autor_match, autor_regex)) {
//         matches.push_back(*lv);
//       }
//     }
//   }
//   return matches;
// }

// Getters
vector<Usuario> &Biblioteca::get_usuarios() { return usuarios; }
vector<Publicacao> &Biblioteca::get_publicacoes() { return livros; }
vector<Emprestimo> &Biblioteca::get_emprestimos() { return emprestimos; }

#endif