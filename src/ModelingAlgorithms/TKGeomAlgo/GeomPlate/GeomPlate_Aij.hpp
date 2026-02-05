#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>

//! A structure containing indexes of two normals and its cross product
class GeomPlate_Aij
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomPlate_Aij();

  Standard_EXPORT GeomPlate_Aij(const int anInd1, const int anInd2, const gp_Vec& aVec);

  friend class GeomPlate_BuildAveragePlane;

private:
  int    Ind1;
  int    Ind2;
  gp_Vec Vec;
};
