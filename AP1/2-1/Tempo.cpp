#include "Tempo.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <tuple>
using namespace std;    

Tempo::Tempo(int t_dia, int t_hora, int t_min, int t_seg){
  tie(dia, hora, min, seg) = make_consistent(t_dia, t_hora, t_min, t_seg);
}

Tempo::~Tempo(){
  cout << endl << "Deleted" << endl;
}

void Tempo::print_tempo(){
  cout << endl << dia << " Dias, " << hora << " h " << min << " min " << seg << " s " << endl;
}

void Tempo::set_tempo(int t_dia, int t_hora, int t_min, int t_seg){
  tie(dia, hora, min, seg) = make_consistent(t_dia, t_hora, t_min, t_seg);
}

void Tempo::sum_tempo(Tempo t2){
  tie(dia, hora, min, seg) = make_consistent(dia + t2.dia, hora + t2.hora, min + t2.min, seg + t2.seg);
  cout << "Resultado da soma:";
  print_tempo();
}

void Tempo::increase(){
  tie(dia, hora, min, seg) = make_consistent(dia, hora, min, seg + 1);
}

void Tempo::decrease(){
  tie(dia, hora, min, seg) = make_consistent(dia, hora, min, seg - 1);
}

tuple<int, int, int, int> Tempo::make_consistent(int t_dia, int t_hora, int t_min, int t_seg){
  div_t seg_ = div(t_seg * (t_seg > 0), 60);
  t_seg = (int)seg_.rem;
  div_t min_ = div(t_min * (t_min > 0) + seg_.quot, 60);
  t_min = (int)min_.rem;
  div_t hora_ = div(t_hora * (t_hora > 0) + min_.quot, 24);
  t_hora = (int)hora_.rem;
  t_dia = t_dia * (t_dia > 0) + (int)hora_.quot;
  return make_tuple(t_dia, t_hora, t_min, t_seg);
}