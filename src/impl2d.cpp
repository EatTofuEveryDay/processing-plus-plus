// processing v0.0

#include "../include/processing.h"

#define EXT
#include "private.h"

// For SafeRelease
#include "basewin.h"
#include "debug.h"

bool prxx::__private::operator!=(prxx::__private::runningFunc a, prxx::__private::runningFunc b) {
	return !(a == b);
}

// Just the 2d primitives in this file
void prxx::createCanvas(double w, double h){
  __private::aquire_lock();
  if(__private::cfn != __private::runningFunc::setup)
    throw XFunctionError("Must call createCanvas() in setup()");
  __private::width = w;
  __private::height = h;
  __private::staticvarlock.unlock();
}
void prxx::arc(double x, double y, double w, double h, double start, double stop){
  arc(x, y, w, h, start, stop, arcmode::OPEN);
}
void prxx::arc(double x, double y, double w, double h, double start, double stop, prxx::arcmode m){
  // I was honestly blown away by the amount of code required to make a simple arc.
  // Use the (to be implemented) PPath class to store long sequences of arc commands.
  // Try not to call this func alone, it introduces much overhead
  __private::aquire_lock();
  if (__private::cfn != __private::runningFunc::draw) throw XFunctionError("Must draw only in draw()");
  __private::staticvarlock.unlock();
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
  auto startpoint = D2D1::Point2F(FLOAT(x + cosst * radst), FLOAT(y + sinst * radst));
  // Repeat process for endpoint
  double cossp = std::cos(stop);
  double sinsp = std::sin(stop);
  double radsp = (w * h) / std::sqrt(w * w * cossp * cossp + h * h * sinsp * sinsp);
  auto stoppoint = D2D1::Point2F(FLOAT(x + cossp * radsp), FLOAT(y + sinsp * radsp));
  // Size of ellipse is the arguments supplied
  auto size = D2D1::SizeF(FLOAT(w), FLOAT(h));
  auto dr = D2D1::ArcSegment(stoppoint, size, 0, D2D1_SWEEP_DIRECTION_CLOCKWISE, arcSize);
  // Begin creating the geometry
  ID2D1PathGeometry* path;
  hr = __private::pFactory->CreatePathGeometry(&path);
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::arc failed");
  ID2D1GeometrySink* sink;
  hr = path->Open(&sink);
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::arc failed");
  sink->BeginFigure(startpoint, D2D1_FIGURE_BEGIN_FILLED);
  // Add the arc
  sink->AddArc(dr);
  if(m == arcmode::CHORD){
    sink->AddLine(startpoint);
  }else if(m == arcmode::PIE){
    sink->AddLine(D2D1::Point2F(FLOAT(x), FLOAT(y)));
    sink->AddLine(startpoint);
  }
  sink->EndFigure(D2D1_FIGURE_END_OPEN);
  hr = sink->Close();
  SafeRelease(&sink);
  __private::aquire_lock();
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::arc failed");
  __private::pRenderTarget->DrawGeometry(path, __private::strokebrush, FLOAT(__private::strokewidth), NULL);
  __private::pRenderTarget->DrawGeometry(path, __private::fillbrush);
  __private::staticvarlock.unlock();
}
void prxx::ellipse(double p1, double p2, double p3, double p4){
  __private::aquire_lock();
  if (__private::cfn != __private::runningFunc::draw) throw XFunctionError("Must draw only in draw()");
  __private::staticvarlock.unlock();
  D2D1_ELLIPSE ellipse;
  D2D_POINT_2F point;
  switch(__private::ellipsemode){
    case QuadMode::CENTER:
      point.x = FLOAT(p1);
      point.y = FLOAT(p2);
      ellipse = D2D1::Ellipse(point, FLOAT(p3), FLOAT(p4));
      break;
    case QuadMode::RADIUS:
      point.x = FLOAT(p1);
      point.y = FLOAT(p2);
      ellipse = D2D1::Ellipse(point, FLOAT(p3 / 2), FLOAT(p4 / 2));
      break;
    case QuadMode::CORNER:
      point.x = FLOAT(p1 + p3 / 2);
      point.y = FLOAT(p2 + p4 / 2);
      ellipse = D2D1::Ellipse(point, FLOAT(p3), FLOAT(p4));
      break;
    case QuadMode::CORNERS:
      point.x = FLOAT(p1 + (p3 - p1) / 2);
      point.y = FLOAT(p2 + (p4 - p2) / 2);
      ellipse = D2D1::Ellipse(point, FLOAT(p3 - p1), FLOAT(p4 - p2));
      break;
    default:
      throw XFunctionError("Invalid ellipseMode");
  }
  __private::pRenderTarget->DrawEllipse(ellipse, __private::strokebrush, FLOAT(__private::strokewidth), NULL);
  __private::pRenderTarget->FillEllipse(ellipse, __private::fillbrush);
  __private::staticvarlock.unlock();
}
void prxx::quad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
  // The problem here is also with overhead.
  // Use the (to be implemented) PPath
  HRESULT hr; // C-style error handling, I hate winapi
  __private::aquire_lock();
  if (__private::cfn != __private::runningFunc::draw) throw XFunctionError("Must draw only in draw()");
  __private::staticvarlock.unlock();
  ID2D1PathGeometry *path;
  hr = __private::pFactory->CreatePathGeometry(&path);
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::quad failed");
  ID2D1GeometrySink *sink;
  hr = path->Open(&sink);
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::quad failed");
  sink->BeginFigure(D2D1::Point2F(FLOAT(x1), FLOAT(y1)), D2D1_FIGURE_BEGIN::D2D1_FIGURE_BEGIN_FILLED);
  sink->AddLine(D2D1::Point2F(FLOAT(x2), FLOAT(y2)));
  sink->AddLine(D2D1::Point2F(FLOAT(x3), FLOAT(y3)));
  sink->AddLine(D2D1::Point2F(FLOAT(x4), FLOAT(y4)));
  sink->AddLine(D2D1::Point2F(FLOAT(x1), FLOAT(y1)));
  sink->EndFigure(D2D1_FIGURE_END_OPEN);
  hr = sink->Close();
  if (!SUCCEEDED(hr)) throw DrawingError("prxx::quad failed");
  __private::aquire_lock();
  __private::pRenderTarget->DrawGeometry(path, __private::strokebrush, FLOAT(__private::strokewidth), NULL);
  __private::pRenderTarget->FillGeometry(path, __private::fillbrush);
  __private::staticvarlock.unlock();
}
void prxx::point(double x, double y){
  __private::aquire_lock();
  if(__private::cfn != __private::runningFunc::draw) throw XFunctionError("Must draw only in draw()");
  __private::staticvarlock.unlock();
  line(x, y, x+1, y+1); // No other way to draw a point.
}
void prxx::line(double x1, double y1, double x2, double y2){
  __private::aquire_lock();
  if (__private::cfn != __private::runningFunc::draw) throw XFunctionError("Must draw only in draw()");
  __private::pRenderTarget->DrawLine(D2D1::Point2F(FLOAT(x1), FLOAT(y1)), D2D1::Point2F(FLOAT(x2), FLOAT(y2)), __private::strokebrush, FLOAT(__private::strokewidth), NULL);
  __private::staticvarlock.unlock();
}
void prxx::rect(double p1, double p2, double p3, double p4){
  using namespace prxx::__private;
  aquire_lock();
  if(cfn != runningFunc::draw) throw XFunctionError("Must draw only in draw()");
  D2D1_RECT_F rct;
  switch(__private::rectmode){
    case QuadMode::CENTER:
      rct = D2D1::RectF(FLOAT(p1 - p3/2), FLOAT(p2 - p4/2), FLOAT(p1 + p3/2), FLOAT(p2 + p4/2));
      break;
    case QuadMode::RADIUS:
      rct = D2D1::RectF(FLOAT(p1 - p3), FLOAT(p2 - p4), FLOAT(p1 + p3), FLOAT(p2 + p4));
      break;
    case QuadMode::CORNER:
      rct = D2D1::RectF(FLOAT(p1), FLOAT(p2), FLOAT(p1 + p3), FLOAT(p2 + p4));
      break;
    case QuadMode::CORNERS:
      rct = D2D1::RectF(FLOAT(p1), FLOAT(p2), FLOAT(p3), FLOAT(p4));
      break;
    default:
      throw XFunctionError("Invalid rectMode");
  }
  pRenderTarget->DrawRectangle(rct, strokebrush, FLOAT(strokewidth));
  pRenderTarget->FillRectangle(rct, fillbrush);
  /*tstring dbgstr = to_tstring(reinterpret_cast<long long>(ptr));
  OutputDebugString(dbgstr.c_str());
  ptr->DrawRectangle(rct, strokebrush, FLOAT(strokewidth));
  ptr->FillRectangle(rct, fillbrush);//*/
  staticvarlock.unlock();
}

void prxx::triangle(double x1, double y1, double x2, double y2, double x3, double y3){
  // The problem here is also with overhead.
  // Use the (to be implemented) PPath
  HRESULT hr; // C-style error handling
  __private::aquire_lock();
  if(__private::cfn != __private::runningFunc::draw) throw XFunctionError("Must draw only in draw()");
  __private::staticvarlock.unlock();
  ID2D1PathGeometry *path;
  hr = __private::pFactory->CreatePathGeometry(&path);
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::triangle failed");
  ID2D1GeometrySink *sink;
  hr = path->Open(&sink);
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::triangle failed");
  sink->BeginFigure(D2D1::Point2F(FLOAT(x1), FLOAT(y1)), D2D1_FIGURE_BEGIN::D2D1_FIGURE_BEGIN_FILLED);
  sink->AddLine(D2D1::Point2F(FLOAT(x2), FLOAT(y2)));
  sink->AddLine(D2D1::Point2F(FLOAT(x3), FLOAT(y3)));
  sink->AddLine(D2D1::Point2F(FLOAT(x1), FLOAT(y1)));
  sink->EndFigure(D2D1_FIGURE_END_OPEN);
  hr = sink->Close();
  __private::aquire_lock();
  if(!SUCCEEDED(hr)) throw DrawingError("prxx::triangle failed");
  __private::pRenderTarget->DrawGeometry(path, __private::strokebrush, FLOAT(__private::strokewidth));
  __private::pRenderTarget->FillGeometry(path, __private::fillbrush);
  __private::staticvarlock.unlock();
}

void prxx::text(tstring str, double x, double y) {
  __private::aquire_lock();
	__private::pRenderTarget->DrawText(str.c_str(), (UINT32)str.size(), NULL, D2D1::RectF(FLOAT(x), FLOAT(y), 100, 100), __private::fillbrush);
  __private::staticvarlock.unlock();
}