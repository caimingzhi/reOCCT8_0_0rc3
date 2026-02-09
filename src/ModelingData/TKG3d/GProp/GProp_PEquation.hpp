#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

enum GProp_EquaType
{
  GProp_Plane,
  GProp_Line,
  GProp_Point,
  GProp_Space,
  GProp_None
};

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
class gp_Pln;
class gp_Lin;

class GProp_PEquation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GProp_PEquation(const NCollection_Array1<gp_Pnt>& Pnts, const double Tol);

  Standard_EXPORT bool IsPlanar() const;

  Standard_EXPORT bool IsLinear() const;

  Standard_EXPORT bool IsPoint() const;

  Standard_EXPORT bool IsSpace() const;

  Standard_EXPORT gp_Pln Plane() const;

  Standard_EXPORT gp_Lin Line() const;

  Standard_EXPORT gp_Pnt Point() const;

  Standard_EXPORT void Box(gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const;

private:
  GProp_EquaType type;
  gp_Pnt         g;
  gp_Vec         v1;
  gp_Vec         v2;
  gp_Vec         v3;
};
