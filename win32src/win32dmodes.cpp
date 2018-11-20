#include"basewin.h"

#undef EXT
#include"win32private.h"

void ellipseMode(quadMode_t t){
  __private::staticvarlock.aquire();
  __private::ellipsemode = t;
}
void rectMode(quadMode_t t){
  __private::rectmode = t;
}
void strokeWeight(double);

void background(int, int, int, int);
void background(color_t);
void fill(int, int, int, int);
void fill(color_t);
void noFill(void);
void stroke(int, int, int, int);
void stroke(color_t);
void noStroke(void);
color_t color(int, int, int, int);
int alpha(color_t);
int red(color_t);
int green(color_t);
int blue(color_t);
