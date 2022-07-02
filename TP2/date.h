#ifndef DATE_H
#define DATE_H

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Date {
  int ano, mes, dia;

 public:
  // Constructors & Destructor
  Date() {
    time_t t = time(0);
    tm *now = localtime(&t);
    ano = now->tm_year + 1900;
    mes = now->tm_mon + 1;
    dia = now->tm_mday;
  };
  Date(int t_ano, int t_mes, int t_dia) : ano(t_ano), mes(t_mes), dia(t_dia){};
  Date(Date const &t_data)
      : ano(t_data.ano), mes(t_data.mes), dia(t_data.dia){};
  ~Date(){};
  void print_date() const;
  int days_elapsed() const;       // converte ano, mes, dia par dias corridos.
                                  // Considerando 365dias/ano e 30dias/mes
  Date days2ymd(int days) const;  // converte dias corridos para ano, mes, dia.
                                  // Considerando 365dias/ano e 30dias/mes

  // Operators
  Date &operator=(const Date &t_data);
  bool operator==(const Date &t_data) const;
  Date operator+(const Date &t_data) const;
  Date operator+(int days) const;
  Date operator-(const Date &t_data) const;
  Date operator-(int days) const;
  bool operator>(const Date &t_data) const;

  // Padroniza os elementos temporais, ignorando valores negativos e
  // restringindo-os dentro dos intervalos: dia: [0, inf), hora: [0, 24), min:
  // [0, 60), seg: [0, 60)
};

void Date::print_date() const {
  cout << this->dia << " " << this->mes << " " << this->ano << " " << endl;
}

int Date::days_elapsed() const {
  int tot_days = dia;
  tot_days += (mes * 30 + ano * 365);
  return tot_days;
}

Date Date::days2ymd(int days) const {
  int y = days / 365;
  int d = days % 365;
  int m = d / 30;
  d %= 30;
  return Date(y, m, d);
}

Date &Date::operator=(const Date &t_data) {
  ano = t_data.ano;
  mes = t_data.mes;
  dia = t_data.dia;
  return *this;
}

bool Date::operator==(const Date &t_data) const{
  bool r = (ano == t_data.ano) && (mes == t_data.mes) && (dia == t_data.dia);
  return r;
}

Date Date::operator+(const Date &t_data) const {
  int days1 = this->days_elapsed();
  int days2 = t_data.days_elapsed();
  days1 += days2;
  return this->days2ymd(days1);
}

Date Date::operator+(int days) const {
  int days1 = this->days_elapsed();
  days1 += days;
  return this->days2ymd(days1);
}

Date Date::operator-(const Date &t_data) const {
  int days1 = this->days_elapsed();
  int days2 = t_data.days_elapsed();
  days1 -= days2;
  return this->days2ymd(days1);
}

Date Date::operator-(int days) const {
  int days1 = this->days_elapsed();
  days1 -= days;
  return this->days2ymd(days1);
}

bool Date::operator>(const Date &t_data) const {
  if (t_data.ano > this->ano) {
    return true;
  } else if (t_data.mes > this->mes) {
    return true;
  } else {
    if (t_data.dia > this->dia) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

#endif