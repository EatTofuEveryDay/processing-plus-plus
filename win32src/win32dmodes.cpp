#include"basewin.h"

#undef EXT
#include"win32private.h"

enum class quadMode_t {
  CENTER, RADIUS, CORNER, CORNERS
};
void ellipseMode(quadMode_t);
void rectMode(quadMode_t);
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
