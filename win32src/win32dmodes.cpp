#include"../include/processing.h"

#include"basewin.h"
#include<d2d1.h>
#include<cmath>

#define EXT
#include"win32private.h"

void prxx::ellipseMode(prxx::quadMode_t t){
  __private::aquire_lock();
  __private::ellipsemode = t;
  __private::staticvarlock.unlock();
}
void prxx::rectMode(prxx::quadMode_t t){
  __private::aquire_lock();
  __private::rectmode = t;
  __private::staticvarlock.unlock();
}
void prxx::strokeWeight(double w){
  __private::aquire_lock();
  __private::strokewidth = w;
  __private::staticvarlock.unlock();
}

void prxx::background(int r, int g, int b, int a){
  __private::aquire_lock();
  double w = __private::width;
  double h = __private::height;
  __private::staticvarlock.unlock();
  fill(r, g, b, a);
  rect(0, 0, (int)std::floor(w), (int)std::floor(h));
}
void prxx::fill(int r, int g, int b, int a){
  __private::aquire_lock();
  HRESULT hr = __private::pRenderTarget->CreateSolidColorBrush(
    D2D1::ColorF(FLOAT(r) / 255, FLOAT(g) / 255, FLOAT(b) / 255, 1 - (FLOAT(a) / 255) ),
    D2D1::BrushProperties(),
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
void prxx::stroke(int r, int g, int b, int a){
  __private::aquire_lock();
  HRESULT hr = __private::pRenderTarget->CreateSolidColorBrush(
    D2D1::ColorF(D2D1::ColorF(FLOAT(r) / 255, FLOAT(g) / 255, FLOAT(b) / 255, 1 - (FLOAT(a) / 255) )),
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
