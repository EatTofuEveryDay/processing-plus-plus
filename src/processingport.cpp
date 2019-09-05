#include "../include/processing.h"
#include"private.h"
#include<iostream>
#include<string>
#include<cmath>
#include<chrono>

prxx::PColor prxx::color(int r, int g, int b, int a){
  prxx::PColor c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;
  return c;
}

int prxx::red(PColor c){
  return c.r;
}

int prxx::green(PColor c){
  return c.g;
}

int prxx::blue(PColor c){
  return c.b;
}

int prxx::alpha(PColor c){
  return c.a;
}

void prxx::background(PColor c){
  background(c.r, c.g, c.b, c.a);
}

void prxx::fill(PColor c){
  fill(c.r, c.g, c.b, c.a);
}

void prxx::stroke(PColor c){
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

double prxx::norm(double val, double lower, double upper) {
  return map(val, lower, upper, 0, 1);
}

double prxx::pow(double x, double y) {
  return std::pow(x, y);
}

double prxx::round(double x) {
  return std::round(x);
}

double prxx::sq(double x){
  return std::pow(x, 2);
}

double prxx::sqrt(double x) {
  return std::sqrt(x);
}

long long prxx::millis() {
  using namespace std::chrono;
  return (time_point_cast<milliseconds>(high_resolution_clock::now()) - prxx::__private::programstart).count();
}

prxx::ArgumentError::ArgumentError(std::string w) : pw {w} {}

prxx::ArgumentError::~ArgumentError(void) {}

std::string prxx::ArgumentError::what(){
  return pw;
}

prxx::XFunctionError::XFunctionError(std::string w) : pw{w} {}

prxx::XFunctionError::~XFunctionError(void) {}

std::string prxx::XFunctionError::what(){
  return pw;
}

prxx::NotImplementedError::NotImplementedError(std::string w) : pw{w} {}

prxx::NotImplementedError::~NotImplementedError(void) {}

std::string prxx::NotImplementedError::what(){
  return pw;
}

prxx::DrawingError::DrawingError(std::string w) : pw{w} {}

prxx::DrawingError::~DrawingError(void) {}

std::string prxx::DrawingError::what(){
  return pw;
}

