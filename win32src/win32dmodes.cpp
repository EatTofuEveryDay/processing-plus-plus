#include"../include/processing.h"

#include"basewin.h"
#include<d2d1.h>
#include<cmath>

#undef EXT
#include"win32private.h"

void prxx::ellipseMode(prxx::quadMode_t t){
  __private::staticvarlock.lock();
  __private::ellipsemode = t;
  __private::staticvarlock.unlock();
}
void prxx::rectMode(prxx::quadMode_t t){
  __private::staticvarlock.lock();
  __private::rectmode = t;
  __private::staticvarlock.unlock();
}
void prxx::strokeWeight(double w){
  __private::staticvarlock.lock();
  __private::strokewidth = w;
  __private::staticvarlock.unlock();
}

void prxx::background(int r, int g, int b, int a = 0){
  __private::staticvarlock.lock();
  double w = __private::width;
  double h = __private::height;
  __private::staticvarlock.unlock();
  fill(r, g, b, a);
  rect(0, 0, std::floor(w), std::floor(h));
}
void prxx::fill(int r, int g, int b, int a = 0){
  __private::staticvarlock.lock();
  HRESULT hr = __private::pRenderTarget->CreateSolidColorBrush(
    D2D1::ColorF(D2D1::ColorF(r / 255,  g / 255, b / 255, 1 - (a / 255) )),
    &__private::fillbrush
  );
  if(!SUCCEEDED(hr)){
    throw xfunction_error("prxx::fill failed");
  }
  __private::staticvarlock.unlock();
}
void prxx::noFill(void){
  fill(0, 0, 0, 255);
}
void prxx::stroke(int r, int g, int b, int a = 0){
  __private::staticvarlock.lock();
  HRESULT hr = __private::pRenderTarget->CreateSolidColorBrush(
    D2D1::ColorF(D2D1::ColorF(r / 255,  g / 255, b / 255, 1 - (a / 255) )),
    &__private::strokebrush
  );
  if(!SUCCEEDED(hr)){
    throw xfunction_error("prxx::stroke failed");
  }
  __private::staticvarlock.unlock();
}
void prxx::noStroke(void){
  stroke(0, 0, 0, 255);
}
