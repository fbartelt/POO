#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "bibexceptions.h"
#include "biblioteca.h"
#include "date.h"
#include "emprestimo.h"
#include "interface.h"
#include "publicacao.h"
#include "usuario.h"
using namespace std;

const int TEST_WITH = 1;  // Se 0 - Testa a Interface, Se 1 - Roda um teste
                          // padrao para testar cada funcao das classes.

void print_lista_usuarios(Biblioteca &b1) {
  cout << "Lista de Usuários" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  vector<Usuario *> users = b1.get_usuarios();
  for (auto i : users) {
    cout << *i << endl;
  }
}

void print_lista_emprestimos(Biblioteca &b1) {
  cout << "Lista de Emprestimos" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  vector<Emprestimo *> emps = b1.get_emprestimos();
  for (auto i : emps) {
    cout << *i << endl;
  }
}

void print_lista_publicacoes(Biblioteca &b1) {
  cout << "Lista de Publicacoes" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  vector<Publicacao *> publis = b1.get_publicacoes();
  for (auto i : publis) {
    cout << *i << endl;
  }
}

void search_titulo(Biblioteca &biblioteca, string &ss) {
  vector<Publicacao *> titles = biblioteca.pesquisa_titulo(ss);
  cout << "Resultados da Pesquisa" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  for (auto i : titles) {
    cout << i->get_codigo() << " - " << i->get_titulo() << ". "
         << i->get_editora() << ". " << i->get_ano() << endl;
  }
}

void search_autor(Biblioteca &biblioteca, string &ss) {
  vector<Livro> titles = biblioteca.pesquisa_autor(ss);
  cout << "Resultados da Pesquisa" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  for (auto i : titles) {
    cout << i.get_codigo() << " - " << i.get_titulo() << ". " << i.get_autores()
         << ". " << i.get_editora() << ". " << i.get_ano() << endl
         << "Quantidade de exemplares:" << i.get_qtdExemplares() << endl;
  }
}

void tester() {
  Usuario *u1 = new Usuario("Carlos Carlos", "96889480040",
                            "Rua A, Belo Horizonte - MG", "(79) 99256-1654");
  Usuario *u2 = new Usuario("Luiz Silva", "89205101052",
                            "R. B, C, Contagem - MG", "(32) 979465505");
  Usuario *u3 = new Usuario("Joao Carlos", "17962734060",
                            "Rua C, Bairro, BH - MG", "31992928117");

  Livro *l1 = new Livro(1, "Calculo", "Cengage", 2013, "Stewart, James", 88);
  Livro *l2 = new Livro(2, "Calculus", "Thomson Brooks/Cole", 2012,
                        "Stewart, James", 2);
  Livro *l3 =
      new Livro(12, "Calculo Numerico: Aspectos Teoricos e Computacionais",
                "Pearson Universidades", 2000,
                "Marcia A. Gomes Ruggiero, Vera Lucia Da Rocha Lopes", 1);
  Livro *l4 = new Livro(22, "Fundamentos de Programacao", "Editora 2", 2001,
                        "Stewart, John", 5);
  Periodico *p1 = new Periodico(3, "Calculos", "Editora", 2021, "Junho", 1);
  Periodico *p2 = new Periodico(30, "Programacao Orientada a Objetos", "UFMG",
                                2022, "Julho", 15);

  Biblioteca(b1);
  b1.add_usuario(u1);
  b1.add_usuario(u2);
  b1.add_usuario(u3);
  b1.add_publicacao(l1);
  b1.add_publicacao(l2);
  b1.add_publicacao(l3);
  b1.add_publicacao(l4);
  b1.add_publicacao(p1);
  b1.add_publicacao(p2);
  Date d1 = Date(2021, 5, 27);
  Date d2 = Date(2022, 9, 30);
  Emprestimo *e1 = new Emprestimo(d1, u1);
  Emprestimo *e2 = new Emprestimo(d2, u2);
  ItemEmprestimo ie1 = ItemEmprestimo(*l3);
  ItemEmprestimo ie2 = ItemEmprestimo(*l1);
  ItemEmprestimo ie3 = ItemEmprestimo(*l2);
  b1.add_emprestimo(e1);
  b1.add_emprestimo(e2);
  b1.add_item_emprestimo(e1, ie1);
  b1.add_item_emprestimo(e2, ie2);
  b1.add_item_emprestimo(e2, ie3);

  cout << "#1 TESTE - Lista de Usuarios, Publicacoes e Emprestimos:" << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  print_lista_usuarios(b1);
  print_lista_emprestimos(b1);
  print_lista_publicacoes(b1);

  cout << "#2 TESTE - Deleta Usuario 3 - Joao Carlos" << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  b1.remove_usuario(*u3);
  print_lista_usuarios(b1);

  cout << "#3 TESTE - Tentativa de emprestimo para livro sem exemplares" << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;

  try {
    ItemEmprestimo ie2_ = ItemEmprestimo(*l3);
    b1.add_item_emprestimo(e2, ie2_);
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#4 TESTE - Pesquisa por titulo de Publicacoes : 'Calculo' " << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  string search = "Calculo";
  search_titulo(b1, search);

  cout << "\n#5 TESTE - Pesquisa por autor de Livros : 'Stewart' " << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  string search2 = "Stewart";
  search_autor(b1, search2);

  cout << "\n#6 TESTE - Remocao de um Periodico : '3 - Calculos'" << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  b1.remove_publicacao(*p1);
  print_lista_publicacoes(b1);

  cout << "\n#7 TESTE - Tentativa de Excluir um livro com emprestimos " << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  try {
    b1.remove_publicacao(*l3);
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#8 TESTE - Usuario tem devolucoes atrasadas e tenta alugar um "
          "Livro. "
       << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  try {
    ItemEmprestimo ie1_ = ItemEmprestimo(*l1);
    b1.add_item_emprestimo(e1, ie1_);
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#8 TESTE - Usuario tem devolucoes atrasadas e tenta criar um novo "
          "Emprestimo. "
       << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  try {
    Emprestimo *e2_ = new Emprestimo(d2, u1);
    b1.add_emprestimo(e2_);
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#9 TESTE - Usuario devolve o Livro atrasado.: '12 - Calculo "
          "Numerico' "
       << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  b1.devolve_livro(*e1, *l3);
  print_lista_emprestimos(b1);

  cout << "\n#10 TESTE - Usuario penalizado tenta alugar um novo Livro." << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  try {
    Emprestimo *e3_ = new Emprestimo(d2, u1);
    b1.add_emprestimo(e3_);
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#11 TESTE - Tentativa de exlcuir um Emprestimo, cujos itens ainda "
          "nao foram devolvidos."
       << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  try {
    b1.remove_emprestimo(*e2);
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#12 TESTE - Usuario devolve todos os livros." << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  b1.devolve_todos_livro(*e2);
  print_lista_emprestimos(b1);

  cout << "\n#13 TESTE - Tentando emprestar um Periodico." << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  try {
    p1->emprestimo();
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#14 TESTE - Tentando devolver um Periodico." << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;
  try {
    p1->devolucao();
  } catch (BibliotecaException &e) {
    cout << e.what() << endl;
  }

  cout << "\n#15 TESTE - Excluir Livro." << endl
       << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
       << endl;

  b1.remove_publicacao(*l3);
  print_lista_publicacoes(b1);
}

int main() {
  if (!TEST_WITH) {
    Biblioteca(b1);
    Interface i3 = Interface(b1);
    i3.main();
  } else {
    tester();
  }
  return 0;
}