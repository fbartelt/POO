#ifndef TEMPO_H
#define TEMPO_H
#include <tuple>
using namespace std; 

class Tempo{
  int dia, hora, min, seg;
  public:
    Tempo(int t_dia=0, int t_hora=0, int t_min=0, int t_seg=0);
    ~Tempo();
    void print_tempo(); // Imprime os valores atuais do objeto
    void set_tempo(int t_dia=0, int t_hora=0, int t_min=0, int t_seg=0); // Altera os valores do objeto
    void sum_tempo(Tempo t2); // Soma o tempo atual do objeto com os valores de t2, armazenando o resultado no objeto atual
    void increase(); // Aumenta o valor de tempo do objeto em 1 segundo
    void decrease(); // Reduz o valor de tempo do objeto em 1 segundo
    
    // Padroniza os elementos temporais, ignorando valores negativos e restringindo-os dentro dos intervalos:
    // dia: [0, inf), hora: [0, 24), min: [0, 60), seg: [0, 60)  
    tuple<int, int, int, int> make_consistent(int t_dia, int t_hora, int t_min, int t_seg);
};

#endif