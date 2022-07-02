#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "biblioteca.h"
#include "date.h"
#include "emprestimo.h"
#include "interface.h"
#include "publicacao.h"
#include "usuario.h"
using namespace std;

// TODO -> publicacao p/ abstrata
//          --> arrumar o print de publicacao
//          --> vetor de ponteiros Publicacao na Biblioteca


int main() {
  // // Date(d);
  // // d.print_date();
  // Date dd = Date(2021, 5, 27);
  // dd.print_date();
  // // Date ddd = d - dd;
  // // ddd.print_date();
  // // Date d4 = Date(dd);
  // // d4 = d4 + 30;
  // // d4.print_date();
  // // if (d > dd)
  // //   cout << "MAIOR" << endl;
  // // else
  // //   cout << "MENOR" << endl;
  // Usuario felps = Usuario("FELPS", "06066", "contagem", "999");
  // Usuario felps1 = Usuario("igor", "1333", "bh", "111");
  // Usuario chikin = Usuario("chikin", "0000", "GOiania", "5");
  // cout << "felps " << felps.get_nome() << felps.get_cpf()
  //      << felps.get_endereco() << felps.get_fone() << endl;
  // if (felps1 == felps)
  //   cout << "igual" << endl;
  // else
  //   cout << "diff" << endl;
  // Livro l1 = Livro(10, "titulo", "editora", 2022, "Napolis, V. Napao, N.",
  // 3); Livro l2 = Livro(12, "LIVRAo", "SN", 1998, "AAAA");
  // //l1.emprestimo();
  // cout << l1.get_autores() << endl;
  // //l1.devolucao();
  // cout << l2.get_autores() << endl;
  // Biblioteca(b1);
  // b1.add_usuario(felps);
  // b1.add_usuario(felps1);
  // b1.add_usuario(chikin);
  // b1.add_publicacao(l1);
  // b1.add_publicacao(l2);
  // Emprestimo e1 = Emprestimo(dd, felps);
  // ItemEmprestimo ie1 = ItemEmprestimo(l2);
  // ItemEmprestimo ie2 = ItemEmprestimo(l1);
  // b1.add_emprestimo(e1);
  // b1.add_item_emprestimo(e1,ie1);
  // b1.add_item_emprestimo(e1,ie2);
  // //e1.empresta_livro(l1);
  // b1.remove_usuario(felps1);
  // felps.set_dataPenalizacao(Date(2022, 1, 1));
  // for(auto i:b1.get_usuarios()){
  //   cout << i << endl;
  // }
  // auto a = b1.get_publicacoes();
  // auto b = b1.get_emprestimos();
  // b1.devolve_livro(e1,l1);
  // cout << b1.get_emprestimos().size() << endl;
  // string s("tit");
  // for (auto i: b1.pesquisa_titulo(s)){
  //   cout << i ;
  // }
  // b1.add_item_emprestimo(e1, ie1);
  Biblioteca(b1);
  Interface i3 = Interface(b1);
  i3.main();
  return 0;
}