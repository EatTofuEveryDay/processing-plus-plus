// processing v0.0

#include "../include/processing.h"

// Without defining EXT macro we are extern
// Just in case
#undef EXT
#include "win32private.h"

// For SafeRelease
#include "basewin.h"

void reload_brushes(){
  fill(__private::fillcol);
  stroke(__private::strokecol);
}

// Just the 2d primitives in this file
void prxx::createCanvas(unsigned int w, unsigned int h){
  if(__private::cfn != runningFunc::setup)
    throw xfunction_error("Must call createCanvas() in setup()");
  __private::staticvarlock.aquire();
  __private::width = w;
  __private::height = h;
  __private::staticvarlock.release();
}
void prxx::arc(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int start, unsigned int stop){
  arc(x, y, w, h, start, stop, OPEN);
}
void prxx::arc(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int start, unsigned int stop, prxx::arcmode m){
  // I was honestly blown away by the amount of code required to make a simple arc.
  // Use the (to be implemented) path_t class to store long sequences of arc commands.
  // Try not to call this func alone, it introduces much overhead
  __private::staticvarlock.aquire();
  if(__private::cfn != runningFunc::draw) throw xfunction_error("Must draw only in draw()");
  __private::staticvarlock.release();
  HRESULT hr; // C-style error handling
  // Make the arc
  D2D1_ARC_SIZE arcSize;
  if(stop - start > 180)
    arcSize = D2D1_ARC_SIZE_LARGE;
  else 
    arcSize = D2D1_ARC_SIZE_SMALL;
  // https://math.stackexchange.com/a/432907
  // Find the radius of the ellipse at the start angle
  double cosst = std::cos(start);
  double sinst = std::sin(start);
  double radst = (w * h) / std::sqrt(w * w * cosst * cosst + h * h * sinst * sinst);
  // Use trig to calculate the startpoint
  auto startpoint = D2D1::Point2F(x + cosst * radst, y + sinst * radst);
  // Repeat process for endpoint
  double cossp = std::cos(stop);
  double sinsp = std::sin(stop);
  double radsp = (w * h) / std::sqrt(w * w * cossp * cossp + h * h * sinsp * sinsp);
  auto stoppoint = D2D1::Point2F(x + cossp * radsp, y + sinsp * radsp);
  // Size of ellipse is the arguments supplied
  auto size = D2D1::SizeF(w, h);
  auto dr = D2D1::ArcSegment(stoppoint, size, 0, D2D1_SWEEP_DIRECTION_CLOCKWISE, arcSize);
  // Begin creating the geometry
  ID2D1PathGeometry* path;
  hr = __private::pFactory->CreatePathGeometry(&path);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::arc failed");
  ID2D1GeometrySink* sink;
  hr = path->Open(&sink);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::arc failed");
  sink->BeginFigure(startpoint, D2D1_FIGURE_BEGIN_FILLED);
  // Add the arc
  sink->AddArc(dr);
  if(m == arcmode::CHORD){
    sink->AddLine(startpoint);
  }else if(m == arcmode::PIE){
    sink->AddLine(D2D1::Point2F(x, y));
    sink->AddLine(startpoint);
  }
  sink->EndFigure(D2D1_FIGURE_END_OPEN);
  hr = sink->Close();
  SafeRelease(&sink);
  __private::staticvarlock.aquire();
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::arc failed");
  hr = __private::pRenderTarget->DrawGeometry(path, __private::strokebrush, __private::strokewidth, NULL);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::arc failed");
  hr = __private::pRenderTarget->DrawGeometry(path, __private::fillbrush);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::arc failed");
  __private::staticvarlock.release();
}
void prxx::ellipse(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4){
  HRESULT hr; // C-style error handling
  __private::staticvarlock.aquire();
  if(__private::cfn != runningFunc::draw) throw xfunction_error("Must draw only in draw()");
  D2D1_ELLIPSE ellipse;
  switch(__private::ellipsemode){
    case quadMode_t::CENTER:
      D2D_POINT_2F point;
      point.x = p1;
      point.y = p2;
      ellipse = D2D1::ellipse(point, p3, p4);
      break;
    case quadMode_t::RADIUS:
      D2D_POINT_2F point;
      point.x = p1;
      point.y = p2;
      ellipse = D2D1::ellipse(point, p3 / 2, p4 / 2);
      break;
    case quadMode_t::CORNER:
      D2D_POINT_2F point;
      point.x = p1 + p3 / 2;
      point.y = p2 + p4 / 2;
      ellipse = D2D1::ellipse(point, p3, p4);
      break;
    case quadMode_t::CORNERS:
      D2D_POINT_2F point;
      point.x = p1 + (p3 - p1) / 2;
      point.y = p2 + (p4 - p2) / 2;
      ellipse = D2D1::ellipse(point, p3 - p1, p4 - p2);
      break;
    default:
      throw xfunction_error("Invalid ellipseMode");
  }
  hr = __private::pRenderTarget->DrawEllipse(ellipse, __private::strokebrush, __private::strokewidth, NULL);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::ellipse failed");
  hr = __private::pRenderTarget->FillEllipse(ellipse, __private::fillbrush);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::ellipse failed");
  __private::staticvarlock.release();
}
void prxx::quad(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, unsigned int x4, unsigned int y4){
  // The problem here is also with overhead.
  // Use the (to be implemented) path_t
  HRESULT hr; // C-style error handling, I hate winapi
  __private::staticvarlock.aquire();
  if(__private::cfn != runningFunc::draw) throw xfunction_error("Must draw only in draw()");
  __private::staticvarlock.release();
  ID2D1PathGeometry *path;
  hr = __private::pFactory->CreatePathGeometry(&path);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::quad failed");
  ID2D1GeometrySink *sink;
  hr = path->OpenSink(&sink);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::quad failed");
  sink->BeginFigure(D2D1::PointF(x1, y1));
  sink->AddLine(D2D1::PointF(x2, y2));
  sink->AddLine(D2D1::PointF(x3, y3));
  sink->AddLine(D2D1::PointF(x4, y4));
  sink->AddLine(D2D1::PointF(x1, y1));
  sink->EndFigure(D2D1_FIGURE_END_OPEN);
  hr = sink->Close();
  __private::staticvarlock.aquire();
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::quad failed");
  hr = __private::pRenderTarget->DrawGeometry(path, __private::strokebrush, __private::strokewidth, NULL);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::quad failed");
  hr = __private::pRenderTarget->FillGeometry(path, __private::fillbrush);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::quad failed");
  __private::staticvarlock.release();
}
void prxx::point(unsigned int x, unsigned int y){
  __private::staticvarlock.aquire();
  if(__private::cfn != runningFunc::draw) throw xfunction_error("Must draw only in draw()");
  __private::staticvarlock.release();
  line(x, y, x+1, y+1); // No other way to draw a point.
}
void prxx::line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
  HRESULT hr; // C-style error handling
  __private::staticvarlock.aquire();
  if(__private::cfn != runningFunc::draw) throw xfunction_error("Must draw only in draw()");
  hr = pRenderTarget->DrawLine(D2D1::PointF(x1, y1), D2D1::PointF(x2, y2), __private::strokebrush, __private::strokewidth);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::line failed");
  __private::staticvarlock.release();
}
void prxx::rect(unsigned int p1, unsigned int p2, unsigned int p3, unsigned int, p4){
  HRESULT hr; // C-style error handling
  __private::staticvarlock.aquire();
  if(__private::cfn != runningFunc::draw) throw xfunction_error("Must draw only in draw()");
  D2D1_RECT_F rct;
  switch(__private::rectMode){
    case rectMode::CENTER:
      rct = D2D1::RectF(p1 - p3/2, p2 - p4/2, p1 + p3/2, p2 + p4/2);
      break;
    case rectMode::RADIUS:
      rct = D2D1::RectF(p1 - p3, p2 - p4, p1 + p3, p2 + p4);
      break;
    case rectMode::CORNER:
      rct = D2D1::RectF(p1, p2, p1 + p3, p2 + p4);
      break;
    case rectMode::CORNERS:
      rct = D2D1::RectF(p1, p2, p3, p4);
      break;
    default:
      throw xfunction_error("Invalid rectMode");
  }
  hr = __private::pRenderTarget->DrawRect(rct, __private::strokebrush, __private::strokewidth, NULL);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::ellipse failed");
  hr = __private::pRenderTarget->FillRect(rct, __private::fillbrush);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::ellipse failed");
  __private::staticvarlock.release();
}
void prxx::triangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3){
  // The problem here is also with overhead.
  // Use the (to be implemented) path_t
  HRESULT hr; // C-style error handling
  __private::staticvarlock.aquire();
  if(__private::cfn != runningFunc::draw) throw xfunction_error("Must draw only in draw()");
  __private::staticvarlock.release();
  ID2D1PathGeometry *path;
  hr = __private::pFactory->CreatePathGeometry(&path);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::triangle failed");
  ID2D1GeometrySink *sink;
  hr = path->OpenSink(&sink);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::triangle failed");
  sink->BeginFigure(D2D1::PointF(x1, y1));
  sink->AddLine(D2D1::PointF(x2, y2));
  sink->AddLine(D2D1::PointF(x3, y3));
  sink->AddLine(D2D1::PointF(x1, y1));
  sink->EndFigure(D2D1_FIGURE_END_OPEN);
  hr = sink->Close();
  __private::staticvarlock.aquire();
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::triangle failed");
  hr = __private::pRenderTarget->DrawGeometry(path, __private::strokebrush, __private::strokewidth, NULL);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::triangle failed");
  hr = __private::pRenderTarget->FillGeometry(path, __private::fillbrush);
  if(!SUCCEEDED(hr)) throw drawing_error("prxx::triangle failed");
  __private::staticvarlock.release();
}

