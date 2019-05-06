#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<exception>
#include<string>

class D2DCreateResourceError : public std::exception {
  std::string msg;
public:
  D2DCreateResourceError(std::string);
  const char* what();
};

class D2DNullAccessError : public std::exception {
  const char* what();
};

#endif