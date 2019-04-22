#ifndef PROCESSING_H
#define PROCESSING_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<exception>
#include<cmath>

#if defined(_WIN32) || defined(_MSC_VER)
// Frickin windows API macros
#include"../win32src/win32fwd.h"
#undef max
#undef min
#endif

// processing reference
// https://processing.org/reference/

namespace prxx {
  namespace __private { /* Implementation-defined */
	class base_path;
  }
  enum class arcmode {
	  OPEN, CHORD, PIE
  };
  // Processing
  
  // Drawing
  
  // 2d primitive, all implemented
  void createCanvas(double, double);
  void arc(double, double, double, double, double, double);
  void arc(double, double, double, double, double, double, arcmode);
  void ellipse(double, double, double, double);
  void quad(double, double, double, double, double, double, double, double);
  void point(double, double);
  void line(double, double, double, double);
  void rect(double, double, double, double);
  void triangle(double, double, double, double, double, double);
  
  // drawing modes, all implemented except fill() and stroke()
  enum class quadMode_t {
    CENTER, RADIUS, CORNER, CORNERS
  };
  void ellipseMode(quadMode_t);
  void rectMode(quadMode_t);
  void strokeWeight(double);
  
  // 2d curves (probably not supported soon)
  void bezier(double, double, double, double, double, double, double, double);
  double bezierPoint(double, double, double, double, double);
  double bezierTangent(double, double, double, double, double);
  
  // Color
  struct color_t {
    unsigned int r : 8;
    unsigned int g : 8;
    unsigned int b : 8;
    unsigned int a : 8;
  };
  
  void background(int, int, int, int = 0);
  void background(color_t);
  void fill(int, int, int, int = 0);
  void fill(color_t);
  void noFill(void);
  void stroke(int, int, int, int = 0);
  void stroke(color_t);
  void noStroke(void);
  color_t color(int, int, int, int = 0);
  int alpha(color_t);
  int red(color_t);
  int green(color_t);
  int blue(color_t);
  
  // Imaging
  class image_t {
    std::string src;
    std::vector<std::vector<color_t> > bmp;
  public:
    image_t();
    image_t(std::string src);
    image_t(int, int);
    image_t(image_t&);
    
    // Access
    std::string& source();
    std::vector<std::vector<color_t> >& bitmap();
    
    void load(void);
	color_t querypixel(int, int);
  };
  
  void image(image_t, double, double);
  void imageMode(quadMode_t);
  
  // Text
  void text(std::wstring, double, double);
  void textSize(double);
  
  // debug/control
  void print(std::string);
  void println(std::string);
  
  // Math
  double abs(double);
  double ceil(double);
  double constrain(double, double, double);
  double dist(double, double, double, double);
  double exp(double);
  double floor(double);
  double lerp(double, double, double);
  double log(double);
  double log10(double);
  double mag(double, double);
  double map(double, double, double, double, double);
  template<class T>
  T max(std::initializer_list<T> l);
  template<class T>
  T max(std::vector<T> v);
  template<class T>
  T min(std::initializer_list<T> l);
  template<class T>
  T min(std::vector<T> v);
  double norm(double, double, double);
  double pow(double, double);
  double round(double);
  double sq(double);
  double sqrt(double);
  
  // Constants
  constexpr double PI = 3.141592653589;
  constexpr double TWO_PI = PI * 2;
  constexpr double TAU = TWO_PI;
  constexpr double HALF_PI = PI / 2;
  constexpr double QUARTER_PI = PI / 4;
  constexpr double E = 2.718281828459;
  
  // Trig
  double sin(double);
  double cos(double);
  double tan(double);
  double asin(double);
  double acos(double);
  double atan(double);
  double atan2(double);
  double degrees(double);
  double radians(double);
  enum class trigMode_t {
	  deg, rad
  };
  double trigMode(trigMode_t);
  
  // File handling
  enum class openmode : int {
    read = 0x1,
    write = 0x2,
    append = 0x4,
    trunc = 0x8,
    binary = 0x10
  };
  class file_t {
    std::fstream fp;
  public:
    file_t();
    file_t(std::string, openmode);
	// Not Copy-constructible
    
    void open(std::string, openmode);
    
    std::string read();
    std::string read(unsigned int);
    
    template<class T>
    void write(T);
    
    void close();
  };
  
  // Extensions
  void windowTitle(std::string);
  void windowIcon(std::string);
  class path_t {
    __private::base_path p; // Implementation
  public:
    path_t();
    ~path_t();
    
    void open();
    void close();
    void bezier(double, double, double, double, double, double);
    void curve(double, double);
    void line(double, double);
    void draw();
  };  
  // Exceptions (implemented)
  
  class argument_error : public std::exception {
    std::string pw;
  public:
    argument_error(std::string w);
    ~argument_error(void) override;
    
    std::string what();
  };
  
  class xfunction_error : public std::exception {
    std::string pw;
  public:
    xfunction_error(std::string w);
    ~xfunction_error(void) override;
    
    std::string what();
  };
  
  class not_implemented_error : public std::exception {
    std::string pw;
  public:
    not_implemented_error(std::string w);
    ~not_implemented_error(void) override;
    
    std::string what();
  };
  
  class drawing_error : public std::exception {
    std::string pw;
  public:
    drawing_error(std::string w);
    ~drawing_error(void) override;
    
    std::string what();
  };
}

#ifdef _WIN32
#define EXT
#include"../win32src/win32private.h"
#endif

// Events

int setup(void);
void draw(void);
void windowResized(unsigned int x, unsigned int y);

void mouseClicked(unsigned int, unsigned int);
void mouseReleased(unsigned int, unsigned int);
void mouseMoved(unsigned int, unsigned int);

void keyPressed(char);
void keyReleased(char);

#endif
