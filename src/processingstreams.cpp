#include "../include/processing.h"
#include"private.h"
#include<iostream>
#include<fstream>
#include<string>

std::ostream& operator<<(std::ostream& out, prxx::color_t c){
  out << "Color r: " << red(c) << ", g: " << green(c) << ", b: " << blue(c);
  if(alpha(c)) out << ", a: " << alpha(c);
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::ArgumentError e){
  out << "Caught prxx::ArgumentError: " << e.what();
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::XFunctionError e){
  out << "Caught prxx::XFunctionError: " << e.what();
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::NotImplementedError e){
  out << "Caught prxx::NotImplementedError: " << e.what();
  return out;
}

std::ostream& operator<<(std::ostream& out, prxx::DrawingError e){
  out << "Caught prxx::DrawingError: " << e.what();
  return out;
}

void prxx::println(std::string s){
  std::cout << s << std::endl;
}

void prxx::print(std::string s){
  std::cout << s;
  std::cout.flush();
}

prxx::PFile::PFile(){}

prxx::PFile::PFile(std::string path, prxx::openmode o){
  open(path, o);
}

void prxx::PFile::open(std::string path, prxx::openmode o){
  int i = int(o);
  std::ios_base::openmode openm;
  if(i & int(prxx::openmode::read))
    openm |= std::ios::in;
  if(i & int(prxx::openmode::write))
    openm |= std::ios::out;
  if(i & int(prxx::openmode::append))
    openm |= std::ios::app;
  if(i & int(prxx::openmode::trunc))
    openm |= std::ios::trunc;
  if(i & int(prxx::openmode::binary))
    openm |= std::ios::binary;
  fp = std::fstream(path, openm);
}

std::string prxx::PFile::read(){
  std::string buf;
  std::string tmp;
  while(std::getline(fp, tmp)){
    buf += tmp;
  }
  return buf;
}

std::string prxx::PFile::read(unsigned int sz){
  char* buf = new char[sz];
  fp.read(buf, sz);
  std::string ret(buf);
  delete[] buf;
  return ret;
}

template<class T>
void prxx::PFile::write(T str){
  fp << str;
}

void prxx::PFile::close(){
  fp.close();
}
