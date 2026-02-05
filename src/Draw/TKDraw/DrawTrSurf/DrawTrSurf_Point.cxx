#include <DrawTrSurf_Point.hpp>

#include <Draw_Color.hpp>
#include <Draw_Display.hpp>
#include <DrawTrSurf.hpp>
#include <DrawTrSurf_Params.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawTrSurf_Point, Draw_Drawable3D)

//=================================================================================================

DrawTrSurf_Point::DrawTrSurf_Point(const gp_Pnt&          P,
                                   const Draw_MarkerShape Shape,
                                   const Draw_Color&      Col)
    : myPoint(P),
      is3D(true),
      myShape(Shape),
      myColor(Col)
{
}

//=================================================================================================

DrawTrSurf_Point::DrawTrSurf_Point(const gp_Pnt2d&        P,
                                   const Draw_MarkerShape Shape,
                                   const Draw_Color&      Col)
    : myPoint(P.X(), P.Y(), 0.),
      is3D(false),
      myShape(Shape),
      myColor(Col)
{
}

//=================================================================================================

bool DrawTrSurf_Point::Is3D() const
{
  return is3D;
}

//=================================================================================================

void DrawTrSurf_Point::DrawOn(Draw_Display& dis) const
{
  dis.SetColor(myColor);
  if (is3D)
    dis.DrawMarker(myPoint, myShape);
  else
    dis.DrawMarker(Point2d(), myShape);
}

//=================================================================================================

void DrawTrSurf_Point::Point(const gp_Pnt& P)
{
  myPoint = P;
  is3D    = true;
}

//=================================================================================================

void DrawTrSurf_Point::Point2d(const gp_Pnt2d& P)
{
  myPoint.SetCoord(P.X(), P.Y(), 0);
  is3D = false;
}

//=================================================================================================

occ::handle<Draw_Drawable3D> DrawTrSurf_Point::Copy() const
{
  occ::handle<DrawTrSurf_Point> P;
  if (is3D)
    P = new DrawTrSurf_Point(myPoint, myShape, myColor);
  else
    P = new DrawTrSurf_Point(Point2d(), myShape, myColor);

  return P;
}

//=================================================================================================

void DrawTrSurf_Point::Dump(Standard_OStream& S) const
{
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  std::ios::fmtflags F = S.flags();
  S.setf(std::ios::scientific, std::ios::floatfield);
  S.precision(15);
#else
  long            form = S.setf(std::ios::scientific);
  std::streamsize prec = S.precision(15);
#endif
  if (is3D)
    S << "Point : " << myPoint.X() << ", " << myPoint.Y() << ", " << myPoint.Z() << std::endl;
  else
    S << "Point 2d : " << myPoint.X() << ", " << myPoint.Y() << std::endl;
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  S.setf(F);
#else
  S.setf(form);
  S.precision(prec);
#endif
}

//=================================================================================================

void DrawTrSurf_Point::Save(Standard_OStream& theStream) const
{
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  std::ios::fmtflags aFlags = theStream.flags();
  theStream.setf(std::ios::scientific, std::ios::floatfield);
  theStream.precision(15);
#else
  long            aForm = theStream.setf(std::ios::scientific);
  std::streamsize aPrec = theStream.precision(15);
#endif
  if (is3D)
  {
    theStream << "1 " << myPoint.X() << " " << myPoint.Y() << " " << myPoint.Z() << "\n";
  }
  else
  {
    theStream << "0 " << myPoint.X() << " " << myPoint.Y() << "\n";
  }
#if !defined(_MSC_VER) && !defined(__sgi) && !defined(IRIX)
  theStream.setf(aFlags);
#else
  theStream.setf(aForm);
  theStream.precision(aPrec);
#endif
}

//=================================================================================================

occ::handle<Draw_Drawable3D> DrawTrSurf_Point::Restore(Standard_IStream& theStream)
{
  const DrawTrSurf_Params& aParams = DrawTrSurf::Parameters();
  int                      is3d    = 0;
  theStream >> is3d;
  double x, y, z = 0.0;
  if (is3d)
  {
    theStream >> x >> y >> z;
  }
  else
  {
    theStream >> x >> y;
  }
  occ::handle<DrawTrSurf_Point> aDrawPoint;
  if (is3d)
  {
    aDrawPoint = new DrawTrSurf_Point(gp_Pnt(x, y, z), aParams.PntMarker, aParams.PntColor);
  }
  else
  {
    aDrawPoint = new DrawTrSurf_Point(gp_Pnt2d(x, y), aParams.PntMarker, aParams.PntColor);
  }
  return aDrawPoint;
}

//=================================================================================================

void DrawTrSurf_Point::Whatis(Draw_Interpretor& S) const
{
  S << "point";
}
