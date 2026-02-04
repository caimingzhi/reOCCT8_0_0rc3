#include <Standard_OutOfRange.hpp>

//======================================================================
inline double IntCurve_Polygon2dGen::DeflectionOverEstimation() const
{
  return (TheDeflection);
} //======================================================================

inline void IntCurve_Polygon2dGen::SetDeflectionOverEstimation(const double x)
{
  TheDeflection = x;
  myBox.Enlarge(TheDeflection);
}

//======================================================================
inline void IntCurve_Polygon2dGen::Closed(const bool flag)
{
  ClosedPolygon = flag;
}

//======================================================================
inline int IntCurve_Polygon2dGen::NbSegments() const
{
  return ((ClosedPolygon) ? NbPntIn : NbPntIn - 1);
}

//======================================================================
inline double IntCurve_Polygon2dGen::InfParameter() const
{
  return (TheParams.Value(TheIndex(1)));
}

//======================================================================
inline double IntCurve_Polygon2dGen::SupParameter() const
{
  return (TheParams.Value(TheIndex(NbPntIn)));
}

//======================================================================

//======================================================================
inline int IntCurve_Polygon2dGen::CalculRegion(const double x,
                                               const double y,
                                               const double x1,
                                               const double x2,
                                               const double y1,
                                               const double y2) const
{
  int r;
  if (x < x1)
  {
    r = 1;
  }
  else
  {
    if (x > x2)
    {
      r = 2;
    }
    else
    {
      r = 0;
    }
  }
  if (y < y1)
  {
    r |= 4;
  }
  else
  {
    if (y > y2)
    {
      r |= 8;
    }
  }
  return (r);
}
