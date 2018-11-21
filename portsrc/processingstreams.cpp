#include "../include/processing.h"
#include<iostream>
#include<fstream>
#include<string>

std::ostream& operator<<(std::ostream& out, prxx::color_t c){
  out << "Color r: " << red(c) << ", g: " << green(c) << ", b: " << blue(c);
  if(alpha(c)) out << ", a: " << alpha(c);
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::argument_error e){
  out << "Caught prxx::argument_error: " << e.what();
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::xfunction_error e){
  out << "Caught prxx::xfunction_error: " << e.what();
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::not_implemented_error e){
  out << "Caught prxx::not_implemented_error: " << e.what();
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::drawing_error e){
  out << "Caught prxx::drawing_error: " << e.what();
  return out;
}

void prxx::println(std::string s){
  std::cout << s << std::endl;
}

void prxx::print(std::string s){
  std::cout << s;
  std::cout.flush();
}

prxx::file_t::file_t(){}

prxx::file_t::file_t(std::string path, prxx::openmode o){
  open(path, o);
}

prxx::file_t::file_t(file_t f){
  fp = f.fp;
}

void prxx::file_t::open(std::string path, prxx::openmode o){
  std::ios_base::openmode openm;
  if(o & prxx::openmode::read)
    openm |= std::ios::in;
  if(o & prxx::openmode::write)
    openm |= std::ios::out;
  if(o & prxx::openmode::append)
    openm |= std::ios::app;
  if(o & prxx::openmode::trunc)
    openm |= std::ios::trunc;
  if(o & prxx::openmode::binary)
    openm |= std::ios::binary;
  fp = std::fstream(path, openm);
}

std::string prxx::file_t::read(){
  std::string buf;
  std::string tmp;
  while(fp.getline(tmp)){
    buf += tmp;
  }
  return buf;
}

std::string prxx::file_t::read(unsigned int sz){
  std::string buf;
  fp.read(buf.c_str(), sz);
  return buf;
}

template<class T>
void prxx::file_t::write(T str){
  fp << str;
}

void prxx::file_t::close(){
  fp.close();
}
