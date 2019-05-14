#ifndef DEBUG_H
#define DEBUG_H
#include<Windows.h>
#include"strings.h"

template<class T>
void debuglog(T obj){
  tstring str = to_tstring(obj);
  OutputDebugString(str.c_str());
}

#endif