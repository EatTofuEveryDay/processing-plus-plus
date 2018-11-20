#include"../include/processing.h"

#include"basewin.h"

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
void background(color_t){
  __private::staticvarlock.aquire();
  double w = __private::width;
  double h = __private::height;
  __private::staticvarlock.release();
  fill(r, g, b, a);
  rect(0, 0, w, h);
}
void fill(int r, int g, int b, int a = 0){
  __private::staticvarlock.aquire();
  // .... Might need to research how later
  __private::staticvarlock.release();
}
void fill(color_t c){
  fill(red(c), green(c), blue(c), alpha(c));
}
void noFill(void){
  fill(0, 0, 0, 255);
}
void stroke(int r, int g, int b, int a = 0){
  __private::staticvarlock.aquire();
  // .... Might need to research how later
  __private::staticvarlock.release();
}
void stroke(color_t c){
  stroke(red(c), green(c), blue(c), alpha(c));
}
void noStroke(void){
  stroke(0, 0, 0, 255);
}
color_t color(int r, int g, int b, int a = 0){
  color_t ret;
  ret.r = r;
  ret.g = g;
  ret.b = b;
  ret.a = a;
  return ret;
}
int alpha(color_t c){
  return c.a;
}
int red(color_t c){
  return c.r;
}
int green(color_t c){
  return c.g;
}
int blue(color_t c){
  return c.b;
}
