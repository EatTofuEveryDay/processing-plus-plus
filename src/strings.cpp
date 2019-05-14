#include<locale>
#include<codecvt>
#include<cstdint>
#include"strings.h"

tstring to_tstring(long double x) {
#if defined(UNICODE) || defined(_UNICODE)
  return std::to_wstring(x);
#else
  return std::to_string(x);
#endif
}

tstring to_tstring(long x) {
#if defined(UNICODE) || defined(_UNICODE)
  return std::to_wstring(x);
#else
  return std::to_string(x);
#endif
}

tstring to_tstring(double x) {
#if defined(UNICODE) || defined(_UNICODE)
  return std::to_wstring(x);
#else
  return std::to_string(x);
#endif
}

tstring to_tstring(long long x) {
#if defined(UNICODE) || defined(_UNICODE)
  return std::to_wstring(x);
#else
  return std::to_string(x);
#endif
}

tstring to_tstring(char x) {
#if defined(UNICODE) || defined(_UNICODE)
  return std::to_wstring(x);
#else
  return std::to_string(x);
#endif
}

tstring to_tstring(int x) {
#if defined(UNICODE) || defined(_UNICODE)
  return std::to_wstring(x);
#else
  return std::to_string(x);
#endif
}

tstring to_tstring(std::string t) {
#if defined(UNICODE) || defined(_UNICODE)
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;

  //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
  std::wstring converted_str = converter.from_bytes(t);
  return converted_str;
#else
  return t;
#endif
}

tstring to_tstring(std::wstring t) {
#if defined(UNICODE) || defined(_UNICODE)
  return t;
#else
  using convert_type = std::codecvt_utf8<char>;
  std::wstring_convert<convert_type, char> converter;

  //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
  std::wstring converted_str = converter.from_bytes(t);
  return converted_str;
#endif
}

tstring to_tstring(void* x)
{
#if defined(UNICODE) || defined(_UNICODE)
  return std::to_wstring(reinterpret_cast<intptr_t>(x));
#else
  return std::to_string(reinterpret_cast<intptr_t>(x));
#endif
}

std::string normalize_string(tstring t) {
#if defined(UNICODE) || defined(_UNICODE)
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;

  //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
  std::string converted_str = converter.to_bytes(t);
  return converted_str;
#else
  return t;
#endif
}

std::wstring normalize_wstring(tstring t) {
#if defined(UNICODE) || defined(_UNICODE)
  return t;
#else
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;

  //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
  std::wstring converted_str = converter.from_bytes(t);
  return converted_str;
#endif
}