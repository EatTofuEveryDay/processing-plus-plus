#ifndef TCHAR_STRINGS_H
#define TCHAR_STRINGS_H

#include<string>
#include<tchar.h>

// Extending std::string methods to TCHAR

// This is enough to make member functions use tchar
typedef std::basic_string<TCHAR> tstring;

// Now to convert some non-member functions
tstring to_tstring(char x);
tstring to_tstring(int x);
tstring to_tstring(long x);
tstring to_tstring(long long x);
tstring to_tstring(double x);
tstring to_tstring(long double x);
tstring to_tstring(std::string x);
tstring to_tstring(std::wstring x);
tstring to_tstring(void* x);

// Conversion to and from tstring
std::string normalize_string(tstring t);
std::wstring normalize_wstring(tstring t);

#endif