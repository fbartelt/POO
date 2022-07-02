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
  void main();
  void add_usuario();
  void add_livro();
  void add_periodico();
  void add_emprestimo();
  void exclui_usuario();
  void print_usuarios();
  void print_publicacoes();
  Usuario find_usuario();
};

void Interface::main() {
  string in;

  int quit = 1;

  while (quit) {
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
        add_livro();
        break;
      case 't':
        add_periodico();
        break;
      case 'y':
        add_emprestimo();
        break;
      case 'u':
        /* code */
        break;
      case 'i':
        /* code */
        break;
      case 'o':
        /* code */
        break;
      case 'p':
        /* code */
        break;
      case 'a':
        /* code */
        break;
      case 's':
        /* code */
        break;
      case 'd':
        /* code */
        break;
      case 'f':
        /* code */
        break;
      case 'g':
        /* code */
        break;
      case 'h':
        /* code */
        break;
      case 'j':
        print_usuarios();
        break;
      case 'k':
        print_publicacoes();
        break;
      case 'l':
        /* code */
        break;
      case 'q':
        quit = 0;
        break;

      default:
        break;
    }
    string dummy;
    cin.clear();
    cin.ignore();
    cout << "\nPressione qualquer tecla para voltar ao menu...";
    getline(cin, dummy);
    system("clear");
  }
}

void Interface::add_usuario() {
  cout << "Insira o nome do usuario: ";
  string t_nome;
  getline(cin>>ws, t_nome);
  cout << "Insira o cpf de " << t_nome << ": ";
  string t_cpf;
  getline(cin>>ws, t_cpf);
  cout  << "Insira o endereco de " << t_nome << ": ";
  string t_endereco;
  getline(cin>>ws, t_endereco);
  //cin >> t_endereco;
  cout << "Insira o telefone de " << t_nome << ": ";
  string t_fone;
  getline(cin>>ws, t_fone);
  Usuario user = Usuario(t_nome, t_cpf, t_endereco, t_fone);
  biblioteca.add_usuario(user);
}

void Interface::add_livro() {
  cout << "Insira o codigo de publicacao: ";
  string scod;
  getline(cin>>ws, scod);
  int t_cod = stoi(scod);
  cout << "Insira o titulo do livro: ";
  string t_titulo;
  getline(cin>>ws, t_titulo);
  cout << "Insira a editora de " << t_titulo << ": ";
  string t_editora;
  getline(cin>>ws, t_editora);
  cout << "Insira o ano de publicacao de " << t_titulo << ": ";
  string sano;
  getline(cin>>ws, sano);
  int t_ano = stoi(sano);
  cout << "Insira os autores de " << t_titulo << ": ";
  string t_autores;
  getline(cin>>ws, t_autores);
  cout << "Deseja inserir a quantidade de exemplares? [S]im/[N]ao: ";
  char confirma;
  cin >> confirma;

  if (char(tolower(confirma)) == 'n') {
    Livro livro = Livro(t_cod, t_titulo, t_editora, t_ano, t_autores);
    biblioteca.add_publicacao(livro);
  } else {
    cout << "Insira a quantidade de exemplares de " << t_titulo << ": ";
    string sqty;
    cin >> sqty;
    int qty = stoi(sqty);
    Livro livro = Livro(t_cod, t_titulo, t_editora, t_ano, t_autores, qty);
    biblioteca.add_publicacao(livro);
  }
}

void Interface::add_periodico() {
  cout << "Insira o codigo de publicacao: ";
  string scod;
  getline(cin>>ws, scod);
  int t_cod = stoi(scod);
  cout << "Insira o titulo do periodico: ";
  string t_titulo;
  getline(cin>>ws, t_titulo);
  cout << "Insira a editora de " << t_titulo << ": ";
  string t_editora;
  getline(cin>>ws, t_editora);
  cout << "Insira o ano de publicacao de " << t_titulo << ": ";
  string sano;
  getline(cin>>ws, sano);
  int t_ano = stoi(sano);
  cout << "Insira o mes de " << t_titulo << ": ";
  string t_mes;
  getline(cin>>ws, t_mes);
  cout << "Insira o numero de edicao de " << t_titulo << ": ";
  string sed;
  getline(cin>>ws, sed);
  int t_numEdicao = stoi(sed);
  Periodico t_periodico =
      Periodico(t_cod, t_titulo, t_editora, t_ano, t_mes, t_numEdicao);
  biblioteca.add_publicacao(t_periodico);
}

void Interface::add_emprestimo(){
  cout << "IMPLEMENTAR" << endl;
  //biblioteca.add_emprestimo();
}

void Interface::print_usuarios() {
  cout << "Lista de Usuários" << endl;
  cout << "-------------------------------------------------------------" << endl;
  vector<Usuario> users = biblioteca.get_usuarios();
  for (auto i : users) {
    cout << i << endl;
  }
}

void Interface::print_publicacoes(){
  cout << "Lista de Publicacoes" << endl;
  cout << "-------------------------------------------------------------" << endl;
  vector<Publicacao> publis = biblioteca.get_publicacoes();
  for(auto i:publis){
    cout << i << endl;
  }
}

Usuario Interface::find_usuario(){
  vector<Usuario> users = biblioteca.get_usuarios();
  int counter =0;
  for(auto i : users){
    cout << "[" << counter << "]: " << i.get_nome() << "   CPF: " << i.get_cpf() << endl; 
    counter++;
  }
  cout << "Insira o indice do usuario de referencia: ";
  string us;
  getline(cin>>ws, us);
  int idx = stoi(us);
  return users.at(idx);
}

string const Interface::TEXTO_MENU =
    "Menu da Biblioteca\n[E] : Cadastrar um novo usuario\n[R] : Cadastrar um "
    "novo livro\n[T] : Cadastrar um novo periodico\n[Y] : Cadastrar um novo "
    "emprestimo\n[U] : Inserir um novo item de emprestimo\n[I] : Excluir um "
    "usuário\n[O] : Excluir um livro\n[P] : Excluir um "
    "periodico\n[A] : Excluir um novo emprestimo\n[S] : Excluir um novo item "
    "de emprestimo\n[D] : Devolver todos os livros do emprestimo\n[F] : "
    "Devolver um livro do emprestimo\n[G] : Pesquisar publicacoes por "
    "titulo\n[H] : Pesquisar livros por autor\n[J] : Listar todos os "
    "usuarios\n[K] : Listar todas as publicacoes (livros e periodicos)\n[L] : "
    "Listar todos os emprestimos\n[Q] : Sair do programa\n\nInsira o comando "
    "desejado: ";

// cout << "Menu da Biblioteca" << endl;
//   cout << "[E] : Cadastrar um novo usuário" << endl;
//   cout << "[R] : Cadastrar um novo livro" << endl;
//   cout << "[T] : Cadastrar um novo periodico" << endl;
//   cout << "[Y] : Cadastrar um novo emprestimo" << endl;
//   cout << "[U] : Inserir um novo item de emprestimo" << endl;
//   cout << "[I] : Excluir um novo usuário" << endl;
//   cout << "[O] : Excluir um novo livro" << endl;
//   cout << "[P] : Excluir um novo periodico" << endl;
//   cout << "[A] : Excluir um novo emprestimo" << endl;
//   cout << "[S] : Excluir um novo item de emprestimo" << endl;
//   cout << "[D] : Devolver todos os livros do emprestimo" << endl;
//   cout << "[F] : Devolver um livro do emprestimo" << endl;
//   cout << "[G] : Pesquisar publicacoes por titulo" << endl;
//   cout << "[H] : Pesquisar livros por autor" << endl;
//   cout << "[J] : Listar todos os usuarios" << endl;
//   cout << "[K] : Listar todas as publicacoes (livros e periodicos)" << endl;
//   cout << "[L] : Listar todos os emprestimos" << endl;
//   cout << "[Q] : Sair do programa" << endl;
//   cout << "Insira o comando desejado: ";

#endif