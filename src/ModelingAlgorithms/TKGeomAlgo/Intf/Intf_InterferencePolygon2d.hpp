#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Intf_Interference.hpp>
class Intf_Polygon2d;
class gp_Pnt2d;

class Intf_InterferencePolygon2d : public Intf_Interference
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Intf_InterferencePolygon2d();

  Standard_EXPORT Intf_InterferencePolygon2d(const Intf_Polygon2d& Obje1,
                                             const Intf_Polygon2d& Obje2);

  Standard_EXPORT Intf_InterferencePolygon2d(const Intf_Polygon2d& Obje);

  Standard_EXPORT void Perform(const Intf_Polygon2d& Obje1, const Intf_Polygon2d& Obje2);

  Standard_EXPORT void Perform(const Intf_Polygon2d& Obje);

  Standard_EXPORT gp_Pnt2d Pnt2dValue(const int Index) const;

private:
  Standard_EXPORT void Interference(const Intf_Polygon2d& Obje1, const Intf_Polygon2d& Obje2);

  Standard_EXPORT void Interference(const Intf_Polygon2d& Obje);

  Standard_EXPORT void Clean();

  Standard_EXPORT void Intersect(const int       iO,
                                 const int       iT,
                                 const gp_Pnt2d& BegO,
                                 const gp_Pnt2d& EndO,
                                 const gp_Pnt2d& BegT,
                                 const gp_Pnt2d& EndT);

  bool oClos;
  bool tClos;
  int  nbso;
};
