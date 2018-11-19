#include "../include/processing.h"
#include<iostream>
#include<string>
#include<cmath>

prxx::color_t prxx::color(int r, int g, int b, int a = 0){
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

std::ostream& operator<<(std::ostream& out, prxx::color_t c){
  out << "Color r: " << red(c) << ", g: " << green(c) << ", b: " << blue(c);
  if(alpha(c)) out << ", a: " << alpha(c);
  return out;
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
double prxx::log10(double){
  return std::log10(x);
}
double prxx::mag(double x, double y){
  return dist(0, 0, x, y);
}
double prxx::map(double x, double start1, double stop1, double start2, double stop2){
  double rng1 = fabs(start1 - stop1);
  double rng2 = fabs(start2 - stop2);
  double 
}
double prxx::max(...);
double prxx::max(std::vector<double>);
double prxx::min(...);
double prxx::min(std::vector<double>);
double prxx::norm(double, double, double);
double prxx::pow(double, double);
double prxx::round(double);
unsigned double prxx::sq(double);
double prxx::sqrt(unsigned double);

constexpr prxx::argument_error::argument_error(std::string w) : pw {w}, {}

prxx::argument_error::~argument_error(void) override {}

constexpr std::string prxx::argument_error::what(){
  return pw;
}

std::ostream& operator<<(std::ostream& out, prxx::argument_error e){
  out << "Caught prxx::argument_error: " << e.what();
  return out;
}

constexpr prxx::xfunction_error::xfunction_error(std::string w) : pw{w}, {}

prxx::xfunction_error::~xfunction_error(void) override {}

constexpr std::string prxx::xfunction_error::what(){
  return pw;
}

std::ostream& operator<<(std::ostream& out, prxx::xfunction_error e){
  out << "Caught prxx::xfunction_error: " << e.what();
  return out;
}

constexpr prxx::not_implemented_error::not_implemented_error(std::string w) : pw{w}, {}

prxx::not_implemented_error::~not_implemented_error(void) override {}

constexpr std::string prxx::not_implemented_error::what(){
  return pw;
}

std::ostream& operator<<(std::ostream& out, prxx::not_implemented_error e){
  out << "Caught prxx::not_implemented_error: " << e.what();
  return out;
}

constexpr prxx::drawing_error::drawing_error(std::string w) : pw{w}, {}

prxx::drawing_error::~drawing_error(void) override {}

constexpr std::string prxx::drawing_error::what(){
  return pw;
}

std::ostream& operator<<(std::ostream& out, prxx::drawing_error e){
  out << "Caught prxx::drawing_error: " << e.what();
  return out;
}