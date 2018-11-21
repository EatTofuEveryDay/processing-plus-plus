#ifndef PROCESSING_H
#define PROCESSING_H

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<exception>
#include<cmath>

// processing reference
// https://processing.org/reference/

namespace prxx {
  namespace __private { /* Implementation-defined */ }
  enum class arcmode {
    OPEN, CHORD, PIE
  }
  // Processing
  
  // Drawing
  
  // 2d primitive, all implemented
  void createCanvas(unsigned int, unsigned int);
  void arc(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
  void arc(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, arcmode);
  void ellipse(unsigned int, unsigned int, unsigned int, unsigned int);
  void quad(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
  void point(unsigned int, unsigned int);
  void line(unsigned int, unsigned int, unsigned int, unsigned int);
  void rect(unsigned int, unsigned int, unsigned int, unsigned int);
  void triangle(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
  
  // drawing modes, all implemented except fill() and stroke()
  enum class quadMode_t {
    CENTER, RADIUS, CORNER, CORNERS
  };
  void ellipseMode(quadMode_t);
  void rectMode(quadMode_t);
  void strokeWeight(double);
  
  // 2d curves (probably not supported soon)
  void bezier(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
  double bezierPoint(unsigned int, unsigned int, unsigned int, unsigned int, double);
  double bezierTangent(unsigned int, unsigned int, unsigned int, unsigned int, double);
  
  // Color
  struct color_t {
    unsigned int r : 8;
    unsigned int g : 8;
    unsigned int b : 8;
    unsigned int a : 8;
  };
  
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
  
  // Imaging
  class image_t {
    std::string src;
    std::vector<std::vector<color_t> > bmp;
  public
    image_t();
    image_t(std::string src);
    image_t(int, int);
    image_t(image_t);
    
    // Access
    std::string& source();
    std::vector<std::vector<color_t> >& bitmap();
    
    void load(void);
  }
  
  void image(image_t, unsigned int, unsigned int);
  void imageMode(quadMode_t);
  
  // Text
  void text(std::string, unsigned int, unsigned int);
  void textSize(unsigned int);
  
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
  double max(std::initializer_list<double>);
  double max(std::vector<double>);
  double min(std::initializer_list<double>);
  double min(std::vector<double>);
  double norm(double, double, double);
  double pow(double, double);
  double round(double);
  unsigned double sq(double);
  double sqrt(unsigned double);
  
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
  enum class trigMode {
    deg, rad
  }
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
    file_t(file_t); // Copy-constructible
    
    void open(std::string, openmode);
    
    std::string read();
    std::string read(unsigned int);
    
    template<class T>
    void write(T);
    
    void close();
  }
  
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
    void bezier(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
    void curve(unsigned int, unsigned int);
    void line(unsigned int, unsigned int);
    void draw();
  };  
  // Exceptions (implemented)
  
  class argument_error : public std::exception {
    std::string pw;
  public:
    argument_error(std::string w);
    ~argument_error(void) override;
    
    std::string what();
  }
  
  class xfunction_error : public std::exception {
    std::string pw;
  public:
    xfunction_error(std::string w);
    ~xfunction_error(void) override;
    
    std::string what();
  }
  
  class not_implemented_error : public std::exception {
    std::string pw;
  public:
    not_implemented_error(std::string w);
    ~not_implemented_error(void) override;
    
    std::string what();
  }
  
  class drawing_error : public std::exception {
    std::string pw;
  public:
    drawing_error(std::string w);
    ~drawing_error(void) override;
    
    std::string what();
  }
}

// Events

int setup(std::vector<std::string> cmdLine);
void draw(void);
void windowResized(unsigned int x, unsigned int y);

void mouseClicked();
void mouseReleased();
void mouseMoved();

void keyPressed(char);
void keyReleased(char);

// If functions don't exist
// Avoid undefined reference errors
// Note: draw and setup must exist
void mouseClicked(...){}
void mouseReleased(...){}
void mouseMoved(...){}

void keyPressed(...){}
void keyReleased(...){}
void windowResized(...){}

#endif
