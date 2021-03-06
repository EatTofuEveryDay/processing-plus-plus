#include"../include/processing.h"
#include"private.h"

#include"basewin.h"
#include"debug.h"
#include<d2d1.h>
#include<cmath>

#define EXT
#include"private.h"

prxx::PColor::PColor() {
  r = 0;
  g = 0;
  b = 0;
  a = 255;
}

void prxx::ellipseMode(prxx::QuadMode t){
  __private::aquire_lock();
  __private::ellipsemode = t;
  __private::staticvarlock.unlock();
}
void prxx::rectMode(prxx::QuadMode t){
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
  __private::fillbrush->SetColor(
    D2D1::ColorF(FLOAT(r) / 255, FLOAT(g) / 255, FLOAT(b) / 255, FLOAT(a) / 255)
  );
  __private::fillcol.r = r;
  __private::fillcol.g = g;
  __private::fillcol.b = b;
  __private::fillcol.a = a;
  __private::staticvarlock.unlock();
}
void prxx::noFill(void){
  fill(0, 0, 0, 255);
}
void prxx::stroke(int r, int g, int b, int a){
  __private::aquire_lock();
  __private::strokebrush->SetColor(
    D2D1::ColorF(FLOAT(r) / 255, FLOAT(g) / 255, FLOAT(b) / 255, FLOAT(a) / 255)
  );
  __private::strokecol.r = r;
  __private::strokecol.g = g;
  __private::strokecol.b = b;
  __private::strokecol.a = a;
  __private::staticvarlock.unlock();
}
void prxx::noStroke(void){
  stroke(0, 0, 0, 255);
}
