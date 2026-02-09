#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <AppParCurves_MultiPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
class AppParCurves_MultiPoint;
class gp_Pnt;
class gp_Pnt2d;
class gp_Vec;
class gp_Vec2d;

class AppParCurves_MultiCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppParCurves_MultiCurve();

  Standard_EXPORT AppParCurves_MultiCurve(const int NbPol);

  Standard_EXPORT AppParCurves_MultiCurve(const NCollection_Array1<AppParCurves_MultiPoint>& tabMU);
  Standard_EXPORT virtual ~AppParCurves_MultiCurve();

  Standard_EXPORT void SetNbPoles(const int nbPoles);

  Standard_EXPORT void SetValue(const int Index, const AppParCurves_MultiPoint& MPoint);

  Standard_EXPORT int NbCurves() const;

  Standard_EXPORT virtual int NbPoles() const;

  Standard_EXPORT virtual int Degree() const;

  Standard_EXPORT int Dimension(const int CuIndex) const;

  Standard_EXPORT void Curve(const int CuIndex, NCollection_Array1<gp_Pnt>& TabPnt) const;

  Standard_EXPORT void Curve(const int CuIndex, NCollection_Array1<gp_Pnt2d>& TabPnt) const;

  Standard_EXPORT const AppParCurves_MultiPoint& Value(const int Index) const;

  Standard_EXPORT const gp_Pnt& Pole(const int CuIndex, const int Nieme) const;

  Standard_EXPORT const gp_Pnt2d& Pole2d(const int CuIndex, const int Nieme) const;

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

  Standard_EXPORT virtual void Value(const int CuIndex, const double U, gp_Pnt& Pt) const;

  Standard_EXPORT virtual void Value(const int CuIndex, const double U, gp_Pnt2d& Pt) const;

  Standard_EXPORT virtual void D1(const int CuIndex, const double U, gp_Pnt& Pt, gp_Vec& V1) const;

  Standard_EXPORT virtual void D1(const int    CuIndex,
                                  const double U,
                                  gp_Pnt2d&    Pt,
                                  gp_Vec2d&    V1) const;

  Standard_EXPORT virtual void D2(const int    CuIndex,
                                  const double U,
                                  gp_Pnt&      Pt,
                                  gp_Vec&      V1,
                                  gp_Vec&      V2) const;

  Standard_EXPORT virtual void D2(const int    CuIndex,
                                  const double U,
                                  gp_Pnt2d&    Pt,
                                  gp_Vec2d&    V1,
                                  gp_Vec2d&    V2) const;

  Standard_EXPORT virtual void Dump(Standard_OStream& o) const;

protected:
  occ::handle<NCollection_HArray1<AppParCurves_MultiPoint>> tabPoint;
};
