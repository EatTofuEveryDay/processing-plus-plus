#include"../include/processing.h"

#include"basewin.h"
#include<d2d1.h>

#undef EXT
#include"win32private.h"

void ellipseMode(quadMode_t t){
  __private::staticvarlock.aquire();
  __private::ellipsemode = t;
  __private::staticvarlock.release();
}
void rectMode(quadMode_t t){
  __private::staticvarlock.aquire();
  __private::rectmode = t;
  __private::staticvarlock.release();
}
void strokeWeight(double w){
  __private::staticvarlock.aquire();
  __private::strokewidth = w;
  __private::staticvarlock.release();
}

void background(int r, int g, int b, int a = 0){
  __private::staticvarlock.aquire();
  double w = __private::width;
  double h = __private::height;
  __private::staticvarlock.release();
  fill(r, g, b, a);
  rect(0, 0, w, h);
}
void fill(int r, int g, int b, int a = 0){
  __private::staticvarlock.aquire();
  HRESULT hr = __private::pRenderTarget->CreateSolidColorBrush(
    D2D1::ColorF(D2D1::ColorF(r / 255,  g / 255, b / 255, 1 - (a / 255) )),
    &__private::fillbrush
  );
  if(!SUCCEEDED(hr)){
    throw xfunction_error("prxx::fill failed");
  }
  __private::staticvarlock.release();
}
void noFill(void){
  fill(0, 0, 0, 255);
}
void stroke(int r, int g, int b, int a = 0){
  __private::staticvarlock.aquire();
  HRESULT hr = __private::pRenderTarget->CreateSolidColorBrush(
    D2D1::ColorF(D2D1::ColorF(r / 255,  g / 255, b / 255, 1 - (a / 255) )),
    &__private::strokebrush
  );
  if(!SUCCEEDED(hr)){
    throw xfunction_error("prxx::stroke failed");
  }
  __private::staticvarlock.release();
}
void noStroke(void){
  stroke(0, 0, 0, 255);
}
