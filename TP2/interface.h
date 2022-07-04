#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "biblioteca.h"
#include "date.h"
#include "publicacao.h"
#include "usuario.h"

using namespace std;

class Interface {
  Biblioteca biblioteca;
  static const string TEXTO_MENU;

 public:
  Interface(Biblioteca &t_biblioteca) : biblioteca(t_biblioteca){};
  ~Interface(){};
  void main();
  int menu();
  void add_usuario();
  void add_livro();
  void add_periodico();
  void add_emprestimo();
  void add_item_emprestimo();
  void exclui_usuario();
  void exclui_livro();
  void exclui_periodico();
  void exclui_emprestimo();
  void exclui_item_emprestimo();
  void devolve_livro();
  void devolve_todos_livro();
  void search_titulo();
  void search_autor();
  void print_usuarios();
  void print_publicacoes();
  void print_emprestimos();
  Usuario *find_usuario();
  Emprestimo *find_emprestimo();
  Publicacao *find_livro();
  Publicacao *find_periodico();
};

void Interface::main() {
  string in;

  int quit = 1;

  while (quit) {
    quit = menu();
  }
}

void Interface::add_usuario() {
  cout << "Insira o nome do usuario: ";
  string t_nome;
  getline(cin >> ws, t_nome);
  cout << "Insira o cpf de " << t_nome << ": ";
  string t_cpf;
  getline(cin >> ws, t_cpf);
  cout << "Insira o endereco de " << t_nome << ": ";
  string t_endereco;
  getline(cin >> ws, t_endereco);
  // cin >> t_endereco;
  cout << "Insira o telefone de " << t_nome << ": ";
  string t_fone;
  getline(cin >> ws, t_fone);
  Usuario *user = new Usuario(t_nome, t_cpf, t_endereco, t_fone);
  biblioteca.add_usuario(user);
}

void Interface::add_livro() {
  cout << "Insira o codigo de publicacao: ";
  string scod;
  getline(cin >> ws, scod);
  int t_cod = stoi(scod);
  cout << "Insira o titulo do livro: ";
  string t_titulo;
  getline(cin >> ws, t_titulo);
  cout << "Insira a editora de " << t_titulo << ": ";
  string t_editora;
  getline(cin >> ws, t_editora);
  cout << "Insira o ano de publicacao de " << t_titulo << ": ";
  string sano;
  getline(cin >> ws, sano);
  int t_ano = stoi(sano);
  cout << "Insira os autores de " << t_titulo << ": ";
  string t_autores;
  getline(cin >> ws, t_autores);
  cout << "Deseja inserir a quantidade de exemplares? [S]im/[N]ao: ";
  char confirma;
  cin >> confirma;

  if (char(tolower(confirma)) == 'n') {
    Livro *livro = new Livro(t_cod, t_titulo, t_editora, t_ano, t_autores);
    biblioteca.add_publicacao(livro);
  } else {
    cout << "Insira a quantidade de exemplares de " << t_titulo << ": ";
    string sqty;
    cin >> sqty;
    int qty = stoi(sqty);
    Livro *livro = new Livro(t_cod, t_titulo, t_editora, t_ano, t_autores, qty);
    biblioteca.add_publicacao(livro);
  }
}

void Interface::add_periodico() {
  cout << "Insira o codigo de publicacao: ";
  string scod;
  getline(cin >> ws, scod);
  int t_cod = stoi(scod);
  cout << "Insira o titulo do periodico: ";
  string t_titulo;
  getline(cin >> ws, t_titulo);
  cout << "Insira a editora de " << t_titulo << ": ";
  string t_editora;
  getline(cin >> ws, t_editora);
  cout << "Insira o ano de publicacao de " << t_titulo << ": ";
  string sano;
  getline(cin >> ws, sano);
  int t_ano = stoi(sano);
  cout << "Insira o mes de " << t_titulo << ": ";
  string t_mes;
  getline(cin >> ws, t_mes);
  cout << "Insira o numero de edicao de " << t_titulo << ": ";
  string sed;
  getline(cin >> ws, sed);
  int t_numEdicao = stoi(sed);
  Periodico *t_periodico =
      new Periodico(t_cod, t_titulo, t_editora, t_ano, t_mes, t_numEdicao);
  biblioteca.add_publicacao(t_periodico);
}

void Interface::add_emprestimo() {
  cout << "Adicionar um emprestimo a qual dos seguintes usuarios?" << endl;
  Usuario *tmp = find_usuario();
  cout << "Insira o ano da Data de Devolucao: ";
  string sano;
  getline(cin >> ws, sano);
  int t_ano = stoi(sano);
  cout << "Insira o mes da Data de Devolucao: ";
  string smes;
  getline(cin >> ws, smes);
  int t_mes = stoi(smes);
  cout << "Insira o dia da Data de Devolucao: ";
  string sdia;
  getline(cin >> ws, sdia);
  int t_dia = stoi(sdia);
  Emprestimo *emp = new Emprestimo(Date(t_ano, t_mes, t_dia), tmp);
  biblioteca.add_emprestimo(emp);
}

void Interface::add_item_emprestimo() {
  cout << "Escolha o Emprestimo de referencia:" << endl;
  Emprestimo *tmp = find_emprestimo();
  cout << endl << "Escolha a Publicacao a ser emprestada" << endl;
  Publicacao *pub = find_livro();
  Livro *lv = dynamic_cast<Livro *>(pub);
  if (lv != nullptr) {
    ItemEmprestimo item = ItemEmprestimo(*lv);
    biblioteca.add_item_emprestimo(tmp, item);
  } else
    throw invalid_argument("Livro nao encontrado");
}

void Interface::exclui_usuario() {
  cout << "Qual usuario deve ser excluido?" << endl;
  Usuario *tmp = find_usuario();
  biblioteca.remove_usuario(*tmp);
}

void Interface::exclui_livro() {
  cout << "Qual livro deve ser excluido?" << endl;
  Publicacao *tmp = find_livro();
  biblioteca.remove_publicacao(*tmp);
}

void Interface::exclui_periodico() {
  cout << "Qual periodico deve ser excluido?" << endl;
  Publicacao *tmp = find_periodico();
  biblioteca.remove_publicacao(*tmp);
}

void Interface::exclui_emprestimo() {
  cout << "Qual Emprestimo deve ser excluido?" << endl;
  Emprestimo *tmp = find_emprestimo();
  biblioteca.remove_emprestimo(*tmp);
}

void Interface::exclui_item_emprestimo() {
  cout << "Qual Emprestimo deve ser excluido?" << endl;
  Emprestimo *tmp = find_emprestimo();
  cout << endl << "Qual item deve ser excluido?" << endl;
  vector<ItemEmprestimo> it = tmp->get_itens();
  int counter = 0;
  for (auto i : it) {
    cout << "[" << counter << "]"
         << " " << i.livro.get_codigo() << " - " << i.livro.get_titulo() << ". "
         << i.livro.get_autores() << ". " << i.livro.get_editora() << ". "
         << i.livro.get_ano() << endl;
  }
  cout << "Insira o indice do item de referencia: ";
  string us;
  getline(cin >> ws, us);
  int idx = stoi(us);
  biblioteca.remove_item_emprestimo(*tmp, it.at(idx));
}

void Interface::devolve_livro() {
  cout << "Qual Emprestimo referente a devolucao?" << endl;
  Emprestimo *tmp = find_emprestimo();
  cout << endl << "Qual livro deve ser devolvido?" << endl;
  vector<ItemEmprestimo> it = tmp->get_itens();
  int counter = 0;
  for (auto i : it) {
    cout << "[" << counter << "]"
         << " " << i.livro.get_codigo() << " - " << i.livro.get_titulo() << ". "
         << i.livro.get_autores() << ". " << i.livro.get_editora() << ". "
         << i.livro.get_ano() << endl;
  }
  cout << "Insira o indice do item de referencia: ";
  string us;
  getline(cin >> ws, us);
  int idx = stoi(us);
  biblioteca.devolve_livro(*tmp, it.at(idx).livro);
}

void Interface::devolve_todos_livro() {
  cout << "Qual Emprestimo referente a devolucao?" << endl;
  Emprestimo *tmp = find_emprestimo();
  biblioteca.devolve_todos_livro(*tmp);
}

void Interface::search_titulo() {
  cout << "Insira o titulo a ser pesquisado:";
  string ss;
  getline(cin >> ws, ss);
  vector<Publicacao *> titles = biblioteca.pesquisa_titulo(ss);
  cout << "Resultados da Pesquisa" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  for (auto i : titles) {
    cout << i->get_codigo() << " - " << i->get_titulo() << ". "
         << i->get_editora() << ". " << i->get_ano();
  }
}

void Interface::search_autor() {
  cout << "Insira o autor a ser pesquisado:";
  string ss;
  getline(cin >> ws, ss);
  vector<Livro> titles = biblioteca.pesquisa_autor(ss);
  cout << "Resultados da Pesquisa" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  for (auto i : titles) {
    cout << i.get_codigo() << " - " << i.get_titulo() << ". " << i.get_autores()
         << ". " << i.get_editora() << ". " << i.get_ano() << endl
         << ". Quantidade de exemplares:" << i.get_qtdExemplares() << endl;
  }
}

void Interface::print_usuarios() {
  cout << "Lista de Usuários" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  vector<Usuario *> users = biblioteca.get_usuarios();
  for (auto i : users) {
    cout << *i << endl;
  }
}

void Interface::print_publicacoes() {
  cout << "Lista de Publicacoes" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  vector<Publicacao *> publis = biblioteca.get_publicacoes();
  for (auto i : publis) {
    cout << *i << endl;
  }
}

void Interface::print_emprestimos() {
  cout << "Lista de Emprestimos" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  vector<Emprestimo *> emps = biblioteca.get_emprestimos();
  for (auto i : emps) {
    cout << *i << endl;
  }
}

Usuario *Interface::find_usuario() {
  vector<Usuario *> users = biblioteca.get_usuarios();
  int counter = 0;
  for (auto i : users) {
    cout << "[" << counter << "]: " << i->get_nome()
         << "   CPF: " << i->get_cpf() << endl;
    counter++;
  }
  cout << "Insira o indice do usuario de referencia: ";
  string us;
  getline(cin >> ws, us);
  int idx = stoi(us);
  return users.at(idx);
}

Emprestimo *Interface::find_emprestimo() {
  vector<Emprestimo *> emps = biblioteca.get_emprestimos();
  for (auto i : emps) {
    cout << *i << endl;
  }
  cout << "Insira o numero do Emprestimo referente: ";
  string us;
  getline(cin >> ws, us);
  int idx = stoi(us);
  return emps.at(idx);
}

Publicacao *Interface::find_livro() {
  vector<Publicacao *> publis = biblioteca.get_publicacoes();
  int counter = 0;
  for (auto i : publis) {
    Livro *lv = dynamic_cast<Livro *>(i);
    if (lv != nullptr) {
      cout << "[" << counter << "]: " << lv->get_codigo() << " - "
           << lv->get_titulo() << ". " << lv->get_autores() << ". "
           << lv->get_editora() << ". " << lv->get_ano() << endl;
    }
    counter++;
  }
  cout << "Insira o indice do Livro de referencia: ";
  string us;
  getline(cin >> ws, us);
  int idx = stoi(us);
  return publis.at(idx);
}

Publicacao *Interface::find_periodico() {
  vector<Publicacao *> publis = biblioteca.get_publicacoes();
  int counter = 0;
  for (auto i : publis) {
    Periodico *lv = dynamic_cast<Periodico *>(i);
    if (lv != nullptr) {
      cout << "[" << counter << "]: " << lv->get_codigo() << " - "
           << lv->get_titulo() << ". " << lv->get_mes() << ". "
           << lv->get_numEdicao() << ". " << lv->get_editora() << ". "
           << lv->get_ano() << endl;
    }
    counter++;
  }
  cout << "Insira o indice do Periodico de referencia: ";
  string us;
  getline(cin >> ws, us);
  int idx = stoi(us);
  return publis.at(idx);
}

string const Interface::TEXTO_MENU =
    "Menu da Biblioteca\n[E] : Cadastrar um novo usuario\n[R] : Cadastrar um "
    "novo livro\n[T] : Cadastrar um novo periodico\n[Y] : Cadastrar um novo "
    "emprestimo\n[U] : Inserir um novo item de emprestimo\n[I] : Excluir um "
    "usuário\n[O] : Excluir um livro\n[P] : Excluir um "
    "periodico\n[A] : Excluir um emprestimo\n[S] : Excluir um item "
    "de emprestimo\n[D] : Devolver todos os livros do emprestimo\n[F] : "
    "Devolver um livro do emprestimo\n[G] : Pesquisar publicacoes por "
    "titulo\n[H] : Pesquisar livros por autor\n[J] : Listar todos os "
    "usuarios\n[K] : Listar todas as publicacoes (livros e periodicos)\n[L] : "
    "Listar todos os emprestimos\n[Q] : Sair do programa\n\nInsira o comando "
    "desejado: ";

int Interface::menu() {
  int quit = 1;
  cout << TEXTO_MENU;
  char choice;
  cin >> choice;
  choice = char(tolower(choice));
  cout << endl;
  switch (choice) {
    case 'e':
      add_usuario();
      break;
    case 'r':
      try {
        add_livro();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 't':
      try {
        add_periodico();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'y':
      try {
        add_emprestimo();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'u':
      try {
        add_item_emprestimo();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'i':
      try {
        exclui_usuario();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'o':
      try {
        exclui_livro();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'p':
      try {
        exclui_periodico();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'a':
      try {
        exclui_emprestimo();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 's':
      try {
        exclui_item_emprestimo();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'd':
      try {
        devolve_todos_livro();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'f':
      try {
        devolve_livro();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'g':
      try {
        search_titulo();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'h':
      try {
        search_autor();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'j':
      try {
        print_usuarios();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'k':
      try {
        print_publicacoes();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'l':
      try {
        print_emprestimos();
      } catch (BibliotecaException &e) {
        cout << e.what() << endl;
      } catch (const exception &e) {
        cout << "ERRO: " << e.what() << endl;
      }
      break;
    case 'q':
      quit = 0;
      break;

    default:
      break;
  }
  if (quit) {
    string dummy;
    cin.clear();
    cin.ignore();
    cout << "\nPressione qualquer tecla para voltar ao menu...";
    getline(cin, dummy);
    system("clear");
  }
  return quit;
}
#endif