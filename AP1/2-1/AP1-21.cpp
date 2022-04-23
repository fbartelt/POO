#include <vector>
#include <iostream>
#include <cstdlib>
#include <tuple>
#include "Tempo.h"
using namespace std;    
/**
Crie uma classe denominada Tempo que contenha 4 atributos inteiros chamados dia (variação de 0 a um valor máximo não limitado) hora (variação de 0 a 23), min (0 a 59) e seg (0 a 59). Separe a definição da classe em um .h e a implementação das funções em um .cpp.

    (a) Crie uma função membro da classe para checar a consistência dos atributos e modificá-los caso não sejam consistentes. Por exemplo, caso dia = 45, hora = 30, min = 56 e seg = 65, estes valores devem ser transformados em dia = 46 , hora = 6, min = 57 e seg = 5. Nas funções a seguir a consistência do objeto Tempo resultante deve ser sempre mantida (use esta função para isto)!

    (b) Crie um único construtor para esta classe, que possa ser usado para criar variáveis do tipo Tempo através de declarações como: Tempo t, t1(72), t2(90,3), t3(4, 7,55), t4(45, 30, 56, 65). O primeiro parâmetro é o número de dias, o segundo o número de horas, o terceiro o de minutos e o quarto o de segundos. Repare que no objeto t4, os parâmetros passados não configuram um objeto válido. Você deve usar a função de (a) para torná-lo válido.

    (c) Crie uma função membro para somar dois objetos do tipo Tempo. Use a função da letra (a) para manter a consistência do resultado;

    (d) Crie funções membro para leitura e impressão de dados via entrada padrão. (novamente, letra (a) ...);

    (e) Crie funções membro que permitam incrementar e decrementar 1 segundo a um objeto do tipo tempo. (novamente, letra (a) ...);

Dica: Você deve usar os recursos aprendidos até o momento para tornar o programa eficiente:

    encapsulamento
    inicialização e destruição de objetos com contrutores e destrutor
    sobrecarga de construtores e funções membro
    argumentos default em construtores e funções membro 
**/

int main(){
  cout << ">Tempo t(10, 25, 61, 61); t.print_tempo :" << endl;
  Tempo t(10, 25, 61, 61);
  t.print_tempo();
  cout << endl << ">Tempo t2; t2.print_tempo :" << endl;
  Tempo t2;
  t2.print_tempo();
  cout << endl << ">t2.increase(); t2.print_tempo():" << endl;
  t2.increase();
  t2.print_tempo();
  cout << endl << ">t2.decrease(); t2.print_tempo():" << endl;
  t2.decrease();
  t2.print_tempo();
  cout << endl << ">t2.set_tempo(5, 3, 60, 59); t2.print_tempo():" << endl;
  t2.set_tempo(5, 3, 60, 59);
  t2.print_tempo();
  cout << endl << ">t.sum_tempo(t2) :" << endl;
  t.sum_tempo(t2);
  
  return 0;
}