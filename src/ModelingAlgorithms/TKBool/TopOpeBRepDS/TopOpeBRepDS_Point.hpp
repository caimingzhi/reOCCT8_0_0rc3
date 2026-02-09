#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
class TopoDS_Shape;

class TopOpeBRepDS_Point
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Point();

  Standard_EXPORT TopOpeBRepDS_Point(const gp_Pnt& P, const double T);

  Standard_EXPORT TopOpeBRepDS_Point(const TopoDS_Shape& S);

  Standard_EXPORT bool IsEqual(const TopOpeBRepDS_Point& other) const;

  Standard_EXPORT const gp_Pnt& Point() const;

  Standard_EXPORT gp_Pnt& ChangePoint();

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT void Tolerance(const double Tol);

  Standard_EXPORT bool Keep() const;

  Standard_EXPORT void ChangeKeep(const bool B);

private:
  gp_Pnt myPoint;
  double myTolerance;
  bool   myKeep;
};
