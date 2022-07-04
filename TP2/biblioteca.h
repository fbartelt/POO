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
  vector<Usuario *> usuarios;
  vector<Publicacao *> livros;
  vector<Emprestimo *> emprestimos;

 public:
  Biblioteca(){};
  ~Biblioteca();
  void add_usuario(Usuario *t_usuario);
  void add_publicacao(Publicacao *t_publicacao);
  void add_emprestimo(Emprestimo *t_emprestimo);
  void add_item_emprestimo(Emprestimo *t_emprestimo,
                           ItemEmprestimo const &t_itemEmprestimo);
  void remove_usuario(Usuario const &t_usuario);
  void remove_publicacao(Publicacao &t_publicacao);
  void remove_emprestimo(Emprestimo &t_emprestimo);
  void remove_item_emprestimo(Emprestimo &t_emprestimo,
                              ItemEmprestimo const &t_itemEmprestimo);
  void devolve_livro(Emprestimo &t_emprestimo, Livro &t_livro);
  void devolve_todos_livro(Emprestimo &t_emprestimo);
  bool checa_multa(Usuario *t_usuario);
  vector<Publicacao *> pesquisa_titulo(string &t_titulo);
  vector<Livro> pesquisa_autor(string &t_autor);
  vector<Usuario *> get_usuarios();
  vector<Publicacao *> get_publicacoes();
  vector<Emprestimo *> get_emprestimos();
  // void save();
  // void load();
};

Biblioteca::~Biblioteca() {
  for (auto i : usuarios) {
    delete i;
  }
  for (auto i : emprestimos) {
    delete i;
  }
  for (auto i : livros) {
    delete i;
  }
}

// Adicoes
inline void Biblioteca::add_usuario(Usuario *t_usuario) {
  usuarios.push_back(t_usuario);
}

inline void Biblioteca::add_publicacao(Publicacao *t_publicacao) {
  livros.push_back(t_publicacao);
}

inline void Biblioteca::add_emprestimo(Emprestimo *t_emprestimo) {
  bool multa = false;
  Usuario *tmp_user = t_emprestimo->get_usuario();
  if (tmp_user->get_dataPenalizacao() > Date()) {
    stringstream oss;
    oss << "Usuario ainda nao pode alugar livros. Somente após "
        << tmp_user->get_dataPenalizacao();
    string ss = oss.str();
    throw EmprestimoExcpetion(ss);
  }
  for (auto i : emprestimos) {
    Usuario *tmp = i->get_usuario();
    if (*tmp == *t_emprestimo->get_usuario()) {
      multa = (multa || checa_multa(tmp));
    }
  }
  if (multa)
    throw EmprestimoExcpetion(
        "Usuario deve devolver Livros antes de criar um novo emprestimo.");
  else
    emprestimos.push_back(t_emprestimo);
}

inline void Biblioteca::add_item_emprestimo(
    Emprestimo *t_emprestimo, ItemEmprestimo const &t_itemEmprestimo) {
  bool multa = false;
  if (!t_emprestimo->get_itens().empty()) {
    multa = checa_multa(t_emprestimo->get_usuario());
  }
  if (multa) {
    throw EmprestimoExcpetion(
        "Usuario deve devolver Livros antes de pegar mais emprestados.");
  } else {
    for (auto i : livros) {
      Livro *lv = dynamic_cast<Livro *>(i);
      if (t_itemEmprestimo.livro == *lv) {
        i->emprestimo();
      }
    }
  }
  t_emprestimo->add_item(t_itemEmprestimo);
}

// Remocoes
void Biblioteca::remove_usuario(Usuario const &t_usuario) {
  int counter = 0;
  int position = 0;
  for (auto i : emprestimos) {
    Usuario *temp = i->get_usuario();
    if (*temp == t_usuario)
      throw RemocaoExcpetion(
          "Nao eh possivel remover o usuairo. Usuario ainda tem "
          "emprestimos.");
  }
  for (auto i : usuarios) {
    if (t_usuario == *i) {
      usuarios.erase(usuarios.begin() + counter);
      break;
    }
    counter++;
  }
}

void Biblioteca::remove_publicacao(Publicacao &t_publicacao) {
  int counter = 0;
  int rem = 0;
  Livro *lv = dynamic_cast<Livro *>(&t_publicacao);
  if (lv != nullptr) {  // Livro
    for (auto i : emprestimos) {
      for (auto j : i->get_itens()) {
        if (j.livro == *lv) {
          rem += 1;
          throw RemocaoExcpetion(
              "Nao eh possivel remover o Livro, pois ha um esprestimo do "
              "mesmo.");
        }
      }
    }
  } else {  // Periodico
    for (auto i : livros) {
      if (t_publicacao == *i) {
        livros.erase(livros.begin() + counter);
        break;
      }
      counter++;
    }
  }
  if (!rem) {  // Periodico
    for (auto i : livros) {
      if (t_publicacao == *i) {
        livros.erase(livros.begin() + counter);
        break;
      }
      counter++;
    }
  }
}

void Biblioteca::remove_emprestimo(Emprestimo &t_emprestimo) {
  int counter = 0;
  bool multa = checa_multa(t_emprestimo.get_usuario());
  if (multa) {
    t_emprestimo.get_usuario()->set_dataPenalizacao(Date() + 3);
  }
  if (t_emprestimo.get_itens().empty()) {
    for (auto i : emprestimos) {
      if (t_emprestimo == *i) {
        // position = counter;
        emprestimos.erase(emprestimos.begin() + counter);
        break;
      }
      counter++;
    }
  } else
    throw RemocaoExcpetion(
        "Nao eh possivel remover o Emprestimo. Ainda ha itens a serem "
        "devolvidos.");
}

void Biblioteca::remove_item_emprestimo(
    Emprestimo &t_emprestimo, ItemEmprestimo const &t_itemEmprestimo) {
  int counter = 0;
  bool multa = checa_multa(t_emprestimo.get_usuario());
  if (multa) {
    t_emprestimo.get_usuario()->set_dataPenalizacao(Date() + 3);
  }
  for (auto i : emprestimos) {
    if (*i == t_emprestimo) {
      emprestimos.at(counter)->remove_item(t_itemEmprestimo);
      if (emprestimos.at(counter)->get_itens().empty()) {
        remove_emprestimo(t_emprestimo);
      }
      break;
    }
    counter++;
  }
  for (auto i : livros) {
    Livro *lv = dynamic_cast<Livro *>(i);
    if (t_itemEmprestimo.livro == *lv) {
      i->devolucao();
    }
  }
}

// Devolucoes
inline void Biblioteca::devolve_livro(Emprestimo &t_emprestimo,
                                      Livro &t_livro) {
  for (auto i : emprestimos) {
    if (*i == t_emprestimo) {
      for (auto j : i->get_itens()) {
        if (j.livro == t_livro) {
          remove_item_emprestimo(*i, j.livro);
        }
      }
    }
  }
  t_emprestimo.devolve_livro(t_livro);
}

inline void Biblioteca::devolve_todos_livro(Emprestimo &t_emprestimo) {
  for (auto i : emprestimos) {
    if (*i == t_emprestimo) {
      for (auto j : i->get_itens()) {
        remove_item_emprestimo(*i, j.livro);
      }
      remove_emprestimo(*i);
    }
  }
  t_emprestimo.devolve_todos_livro();
}

bool Biblioteca::checa_multa(Usuario *t_usuario) {
  bool multa = false;
  for (auto i : emprestimos) {
    if (*i->get_usuario() == *t_usuario) {
      multa = multa || (Date() > i->get_dataPrevDevolucao());
    }
  }
  return multa;
}
// Pesquisas
vector<Publicacao *> Biblioteca::pesquisa_titulo(string &t_titulo) {
  vector<Publicacao *> matches;
  smatch titulo_match;
  regex titulo_regex(t_titulo);
  for (auto i : livros) {
    string titulo = i->get_titulo();
    if (regex_search(titulo, titulo_match, titulo_regex)) {
      matches.push_back(i);
    }
  }
  return matches;
}

vector<Livro> Biblioteca::pesquisa_autor(string &t_autor) {
  vector<Livro> matches;
  smatch autor_match;
  regex autor_regex(t_autor);
  for (auto i : livros) {
    Livro *lv = dynamic_cast<Livro *>(i);
    if (lv != nullptr) {
      string titulo = lv->get_autores();
      if (regex_search(titulo, autor_match, autor_regex)) {
        matches.push_back(*lv);
      }
    }
  }
  return matches;
}

// Getters
vector<Usuario *> Biblioteca::get_usuarios() { return usuarios; }
vector<Publicacao *> Biblioteca::get_publicacoes() { return livros; }
vector<Emprestimo *> Biblioteca::get_emprestimos() { return emprestimos; }

#endif