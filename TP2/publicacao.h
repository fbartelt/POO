#ifndef PUBLICACAO_H
#define PUBLICACAO_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
  virtual void emprestimo() {
    cout << "Metodo ainda nao implementado para essa classe" << endl;
  };
  virtual void devolucao() {
    cout << "Metodo ainda nao implementado para essa classe" << endl;
  };
  virtual ostream &print(ostream &op) const{return op;};
  ostream &print_(ostream &op) const;
  friend ostream &operator<<(ostream &op, Publicacao const &t_publicacao);
  string get_titulo() const { return titulo; };
  int get_codigo() const { return codPublicacao; };
  string get_editora() const { return editora; };
  int get_ano() const { return ano; };
  // bool operator==(Publicacao const &t_publicacao);
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
  // friend ostream &operator<<(ostream &op, Livro const &t_livro);
  ostream &print(ostream &op) const override;
  bool operator==(Livro const &t_livro) const;
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
  // friend ostream &operator<<(ostream &op, Periodico const &t_periodico);
  ostream &print(ostream &op) const override;
  bool operator==(Periodico const &t_periodico) const;
};

inline void Livro::emprestimo() {
  if (qtdeExemplares > 0) {
    qtdeExemplares -= 1;
  } else
    throw out_of_range("Nao há mais livros para empréstimo.");
}

inline void Periodico::emprestimo() {
  throw domain_error("Periodicos nao poder ser emprestados.");
}

inline void Livro::devolucao() { qtdeExemplares += 1; }

inline void Periodico::devolucao() {
  throw domain_error("Periodicos nao poderiam ter sido emprestados.");
}

// bool Publicacao::operator==(Publicacao const &t_publicacao) {
//   return ((codPublicacao == t_publicacao.codPublicacao) &&
//           (titulo == t_publicacao.titulo) && (ano == t_publicacao.ano) &&
//           (editora == t_publicacao.editora));
// }

bool Periodico::operator==(Periodico const &t_periodico) const {
  return ((mes == t_periodico.mes) && (numEdicao && t_periodico.numEdicao));
}

bool Livro::operator==(Livro const &t_livro) const{
  return ((autores == t_livro.autores) &&
          (qtdeExemplares && t_livro.qtdeExemplares));
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
// ostream &operator<<(ostream &op, Livro const &t_livro) {
//   ostream &op2 = t_livro.print_(op);
//   op2 << "Autores : " << t_livro.get_autores() << endl;
//   op2 << "Quantidade de Exemplares : " << t_livro.get_qtdExemplares() <<
//   endl; return op2;
// }

// ostream &operator<<(ostream &op, Periodico const &t_periodico) {
//   ostream &op2 = t_periodico.print_(op);
//   op2 << "Mes : " << t_periodico.get_mes() << endl;
//   op2 << "Numero de edicao : " << t_periodico.get_numEdicao() << endl;
//   return op2;
// }
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

// ostream &operator<<(ostream &op, Publicacao const &t_publicacao) {
//   return t_publicacao.print_(op);
// }
#endif