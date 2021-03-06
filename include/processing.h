#ifndef PROCESSING_H
#define PROCESSING_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<exception>
#include<cmath>
#include"../src/strings.h"

#if defined(_WIN32) || defined(_MSC_VER)
#include"../src/prxxfwd.h"
// Frickin stupid windows API macros
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
  enum class QuadMode {
    CENTER, RADIUS, CORNER, CORNERS
  };
  void ellipseMode(QuadMode);
  void rectMode(QuadMode);
  void strokeWeight(double);
  
  // 2d curves (probably not supported soon)
  void bezier(double, double, double, double, double, double, double, double);
  double bezierPoint(double, double, double, double, double);
  double bezierTangent(double, double, double, double, double);
  
  // Color
  struct PColor {
    PColor();
    unsigned int r : 8;
    unsigned int g : 8;
    unsigned int b : 8;
    unsigned int a : 8;
  };
  
  void background(int, int, int, int = 255);
  void background(PColor);
  void fill(int, int, int, int = 255);
  void fill(PColor);
  void noFill(void);
  void stroke(int, int, int, int = 255);
  void stroke(PColor);
  void noStroke(void);
  PColor color(int, int, int, int = 255);
  int alpha(PColor);
  int red(PColor);
  int green(PColor);
  int blue(PColor);
  
  // Imaging
  class PImage {
    std::string src;
    std::vector<std::vector<PColor> > bmp;
  public:
    PImage();
    PImage(tstring src);
    PImage(int, int);
    PImage(PImage&);
    
    // Access
    std::string& source();
    std::vector<std::vector<PColor> >& bitmap();
    
    void load(void);
	  PColor& querypixel(int, int);
  };
  
  void image(PImage, double, double);
  void imageMode(QuadMode);
  PImage getImage(std::string);
  
  // Text
  void text(tstring, double, double);
  void textSize(double);
  
  // debug/control
  void print(std::string);
  void println(std::string);
  long long millis(void);
  
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
  double random();
  double random(double);
  double random(double, double);
  
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
  class PFile {
    std::fstream fp;
  public:
    PFile();
    PFile(std::string, openmode);
	// Not Copy-constructible
    
    void open(std::string, openmode);
    
    std::string read();
    std::string read(unsigned int);
    
    template<class T>
    void write(T);
    
    void close();
  };
  
  // Extensions
  void windowTitle(tstring);
  void windowIcon(tstring);
  class PPath {
    __private::base_path& p; // Implementation
  public:
    PPath();
    ~PPath();
    
    void open();
    void close();
    void bezier(double, double, double, double, double, double);
    void curve(double, double);
    void line(double, double);
    void draw();
  };

  // Exceptions (implemented)
  class ArgumentError : public std::exception {
    std::string pw;
  public:
    ArgumentError(std::string w);
    ~ArgumentError(void) override;
    
    std::string what();
  };
  
  class XFunctionError : public std::exception {
    std::string pw;
  public:
    XFunctionError(std::string w);
    ~XFunctionError(void) override;
    
    std::string what();
  };
  
  class NotImplementedError : public std::exception {
    std::string pw;
  public:
    NotImplementedError(std::string w);
    ~NotImplementedError(void) override;
    
    std::string what();
  };
  
  class DrawingError : public std::exception {
    std::string pw;
  public:
    DrawingError(std::string w);
    ~DrawingError(void) override;
    
    std::string what();
  };
}

#ifdef _WIN32
#define EXT

#endif

// Events

int setup(void);
void draw(void);
void windowResized(unsigned int x, unsigned int y);

void mousePressed(unsigned int, unsigned int);
void mouseReleased(unsigned int, unsigned int);
void mouseMoved(unsigned int, unsigned int);

void keyPressed(char);
void keyReleased(char);

#endif
