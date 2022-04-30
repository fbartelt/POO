#include "Ponto2D.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
using namespace std;

// Declaracao do vetor estatico de IDs.
vector<int> Ponto2D::id_list;

random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
uniform_int_distribution<> uni_dist(MIN_ID, MAX_ID);

Ponto2D::~Ponto2D(){
  // Encontra o iterador que aponta para o indice de <id> em <id_list>.
  auto it = find(id_list.begin(), id_list.end(), id);
  // Remove <id> de <id_list>, liberando o valor para outro objeto.
  id_list.erase(it);
  cout << "Deleted Object." << endl;
}

int Ponto2D::getNextId(){
  cout << "\tcurrent id_list: [";
  for (int i: id_list){
    cout << i << ' ';
  }
  cout << "]" << endl;
  // Gera um inteiro aleatorio com distribuicao uniforme no intervalo [MIN_ID, MAX_ID].
  int rand_id = uni_dist(gen);
  // Procura por pesquisa binaria se <rand_id> ja eh utilizado por algum objeto, caso
  // seja, chama esta funcao recursivamente ate que <rand_id> seja unico.
  if(binary_search(id_list.begin(), id_list.end(), rand_id)){
    rand_id = getNextId();
  }
  // Caso contrario adiciona <rand_id> em <id_list> e ordena o vetor para permitir
  // uma pesquisa binaria.
  else{
    id_list.push_back(rand_id);
    sort(id_list.begin(), id_list.end());
  }
  return rand_id;
}

