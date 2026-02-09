#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class Standard_Transient;
class gp_Pnt;
class gp_Pnt2d;

class AppParCurves_MultiPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppParCurves_MultiPoint();

  Standard_EXPORT AppParCurves_MultiPoint(const int NbPoints, const int NbPoints2d);

  Standard_EXPORT AppParCurves_MultiPoint(const NCollection_Array1<gp_Pnt>& tabP);

  Standard_EXPORT AppParCurves_MultiPoint(const NCollection_Array1<gp_Pnt2d>& tabP2d);

  Standard_EXPORT AppParCurves_MultiPoint(const NCollection_Array1<gp_Pnt>&   tabP,
                                          const NCollection_Array1<gp_Pnt2d>& tabP2d);
  Standard_EXPORT virtual ~AppParCurves_MultiPoint();

  Standard_EXPORT void SetPoint(const int Index, const gp_Pnt& Point);

  Standard_EXPORT const gp_Pnt& Point(const int Index) const;

  Standard_EXPORT void SetPoint2d(const int Index, const gp_Pnt2d& Point);

  Standard_EXPORT const gp_Pnt2d& Point2d(const int Index) const;

  int Dimension(const int Index) const;

  int NbPoints() const;

  int NbPoints2d() const;

  Standard_EXPORT void Transform(const int    CuIndex,
                                 const double x,
                                 const double dx,
                                 const double y,
                                 const double dy,
                                 const double z,
                                 const double dz);

  Standard_EXPORT void Transform2d(const int    CuIndex,
                                   const double x,
                                   const double dx,
                                   const double y,
                                   const double dy);

  Standard_EXPORT virtual void Dump(Standard_OStream& o) const;

protected:
  occ::handle<Standard_Transient> ttabPoint;
  occ::handle<Standard_Transient> ttabPoint2d;
  int                             nbP;
  int                             nbP2d;
};

#include <Standard_OutOfRange.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>

inline Standard_OStream& operator<<(Standard_OStream& o, const AppParCurves_MultiPoint& M)
{
  M.Dump(o);
  return o;
}

inline int AppParCurves_MultiPoint::NbPoints() const
{
  return nbP;
}

inline int AppParCurves_MultiPoint::NbPoints2d() const
{
  return nbP2d;
}

inline int AppParCurves_MultiPoint::Dimension(const int Index) const
{
  if (Index < 0 || Index > (nbP + nbP2d))
  {
    throw Standard_OutOfRange();
  }
  if (Index <= nbP)
  {
    return 3;
  }
  else
  {
    return 2;
  }
}
