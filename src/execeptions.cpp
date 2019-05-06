#include"exceptions.h"

D2DCreateResourceError::D2DCreateResourceError(std::string str)
{
  msg = str;
}

const char* D2DCreateResourceError::what() {
  return msg.c_str();
}

const char* D2DNullAccessError::what() {
  return "D2DNullAccessError: attempt to access null resource";
}