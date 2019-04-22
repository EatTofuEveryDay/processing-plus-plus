#include "../include/processing.h"
#include<iostream>
#include<string>
#include<cmath>

prxx::color_t prxx::color(int r, int g, int b, int a){
  prxx::color_t c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;
  return c;
}

int prxx::red(color_t c){
  return c.r;
}

int prxx::green(color_t c){
  return c.g;
}

int prxx::blue(color_t c){
  return c.b;
}

int prxx::alpha(color_t c){
  return c.a;
}

void prxx::background(color_t c){
  background(c.r, c.g, c.b, c.a);
}

void prxx::fill(color_t c){
  fill(c.r, c.g, c.b, c.a);
}

void prxx::stroke(color_t c){
  stroke(c.r, c.g, c.b, c.a);
}

double prxx::abs(double x){
  return std::fabs(x);
}
double prxx::ceil(double x){
  return std::ceil(x);
}
double prxx::constrain(double x, double start, double stop){
  if(x < start) return start;
  if(x > stop) return stop;
  return x;
}
double prxx::dist(double x1, double y1, double x2, double y2){
  return std::sqrt(std::fabs(x1 - x2) + std::fabs(y1 - y2));
}
double prxx::exp(double x){
  return std::pow(prxx::E, x);
}
double prxx::floor(double x){
  return std::floor(x);
}
double prxx::lerp(double x, double start, double stop){
  return start + (x * fabs(start - stop));
}
double prxx::log(double x){
  return std::log(x);
}
double prxx::log10(double x){
  return std::log10(x);
}
double prxx::mag(double x, double y){
  return dist(0, 0, x, y);
}
double prxx::map(double x, double start1, double stop1, double start2, double stop2){
  double rng1 = fabs(start1 - stop1);
  double rng2 = fabs(start2 - stop2);
  double unmapped = (x - start1) / rng1;
  return unmapped * rng2 + start2;
}

template<class T>
T prxx::max(std::initializer_list<T> l){
  std::vector<T> v;
  v.insert(v.end(), l.begin(), l.end());
  return prxx::max(v);
}

template<class T>
T prxx::max(std::vector<T> v){
  // If the vector has no elements
  if(!v.size()) return T();
  // Make sure objects of type T are comparable.
  bool check = (T() > T()) || (T() == T());
  T curr = v[0];
  for(T i : v){
    if(i > curr){
      curr = i;
    }
  }
  return curr;
}

template<class T>
T prxx::min(std::initializer_list<T> l){
  std::vector<T> v;
  v.insert(v.end(), l.begin(), l.end());
  return prxx::min(v);
}

template<class T>
T prxx::min(std::vector<T> v){
  // If the vector has no elements
  if(!v.size()) return T();
  // Make sure objects of type T are comparable.
  bool check = (T() > T()) || (T() == T());
  T curr = v[0];
  for(T i : v){
    if(i < curr){
      curr = i;
    }
  }
  return curr;
}

double prxx::norm(double, double, double);
double prxx::pow(double, double);
double prxx::round(double);
double prxx::sq(double);
double prxx::sqrt(double);

prxx::argument_error::argument_error(std::string w) : pw {w} {}

prxx::argument_error::~argument_error(void) {}

std::string prxx::argument_error::what(){
  return pw;
}

prxx::xfunction_error::xfunction_error(std::string w) : pw{w} {}

prxx::xfunction_error::~xfunction_error(void) {}

std::string prxx::xfunction_error::what(){
  return pw;
}

prxx::not_implemented_error::not_implemented_error(std::string w) : pw{w} {}

prxx::not_implemented_error::~not_implemented_error(void) {}

std::string prxx::not_implemented_error::what(){
  return pw;
}

prxx::drawing_error::drawing_error(std::string w) : pw{w} {}

prxx::drawing_error::~drawing_error(void) {}

std::string prxx::drawing_error::what(){
  return pw;
}

