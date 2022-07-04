#ifndef PUBLICACAO_H
#define PUBLICACAO_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "bibexceptions.h"

using namespace std;

class Publicacao {
  int codPublicacao;
  string titulo;
  string editora;
  int ano;
  // date dataPenalizacao;
 public:
  Publicacao(int t_codPublicacao, string t_titulo, string t_editora, int t_ano)
      : codPublicacao(t_codPublicacao),
        titulo(t_titulo),
        editora(t_editora),
        ano(t_ano){};
  virtual ~Publicacao(){};
  virtual void emprestimo() = 0;
  virtual void devolucao() = 0;
  virtual ostream &print(ostream &op) const { return op; };
  ostream &print_(ostream &op) const;
  friend ostream &operator<<(ostream &op, Publicacao const &t_publicacao);
  int get_codigo() const { return codPublicacao; };
  string get_titulo() const { return titulo; };
  string get_editora() const { return editora; };
  int get_ano() const { return ano; };
  bool compare(Publicacao const &t_publicacao) const;
  virtual bool operator==(Publicacao const &t_publicacao) const = 0;
};

class Livro : public Publicacao {
  string autores;
  int qtdeExemplares;

 public:
  Livro(int t_codPublicacao, string t_titulo, string t_editora, int t_ano,
        string t_autores, int t_qtdExemplares)
      : Publicacao(t_codPublicacao, t_titulo, t_editora, t_ano),
        autores(t_autores),
        qtdeExemplares(t_qtdExemplares){};
  Livro(int t_codPublicacao, string t_titulo, string t_editora, int t_ano,
        string t_autores)
      : Publicacao(t_codPublicacao, t_titulo, t_editora, t_ano),
        autores(t_autores),
        qtdeExemplares(0){};
  ~Livro(){};
  void emprestimo();
  void devolucao();
  string get_autores() const { return autores; };
  int get_qtdExemplares() const { return qtdeExemplares; };
  ostream &print(ostream &op) const override;
  bool operator==(Publicacao const &t_publicacao) const;
};

class Periodico : public Publicacao {
  string mes;
  int numEdicao;

 public:
  Periodico(int t_codPublicacao, string t_titulo, string t_editora, int t_ano,
            string t_mes, int t_numEdicao)
      : Publicacao(t_codPublicacao, t_titulo, t_editora, t_ano),
        mes(t_mes),
        numEdicao(t_numEdicao){};
  ~Periodico(){};
  void emprestimo();
  void devolucao();
  string get_mes() const { return mes; };
  int get_numEdicao() const { return numEdicao; };
  ostream &print(ostream &op) const override;
  bool operator==(Publicacao const &t_publicacao) const;
};

inline void Livro::emprestimo() {
  if (qtdeExemplares > 0) {
    qtdeExemplares -= 1;
  } else
    throw EmprestimoExcpetion("Nao há mais livros para empréstimo.");
}

inline void Periodico::emprestimo() {
  throw EmprestimoExcpetion("Periodicos nao poder ser emprestados.");
}

inline void Livro::devolucao() { qtdeExemplares += 1; }

inline void Periodico::devolucao() {
  throw DevolucaoExcpetion("Periodicos nao poderiam ter sido emprestados.");
}

bool Publicacao::compare(Publicacao const &t_publicacao) const {
  return ((titulo == t_publicacao.titulo) && (ano == t_publicacao.ano) &&
          (codPublicacao == t_publicacao.codPublicacao) &&
          (editora == t_publicacao.editora));
}

bool Periodico::operator==(Publicacao const &t_publicacao) const {
  bool ret = true;
  const Periodico *pd = dynamic_cast<const Periodico *>(&t_publicacao);
  if (pd != nullptr)
    ret = ((mes == pd->mes) && (numEdicao == pd->numEdicao) &&
           (this->compare(t_publicacao)));
  else
    ret = false;
  return ret;
}

bool Livro::operator==(Publicacao const &t_publicacao) const {
  bool ret = true;
  const Livro *lv = dynamic_cast<const Livro *>(&t_publicacao);
  if (lv != nullptr)
    ret = ((autores == lv->autores) && (this->compare(t_publicacao)));
  else
    ret = false;
  return ret;
}

ostream &Publicacao::print_(ostream &op) const {
  op << endl;
  op << "Codigo : " << get_codigo() << endl;
  op << "Titulo : " << get_titulo() << endl;
  op << "Editora : " << get_editora() << endl;
  op << "Ano : " << get_ano() << endl;
  return op;
}

ostream &operator<<(ostream &op, Publicacao const &t_publicacao) {
  ostream &op2 = t_publicacao.print_(op);
  return t_publicacao.print(op2);
}

ostream &Livro::print(ostream &op) const {
  op << "Autores : " << get_autores() << endl;
  op << "Quantidade de Exemplares : " << get_qtdExemplares() << endl;
  return op;
}

ostream &Periodico::print(ostream &op) const {
  op << "Mes : " << get_mes() << endl;
  op << "Numero de edicao : " << get_numEdicao() << endl;
  return op;
}

#endif