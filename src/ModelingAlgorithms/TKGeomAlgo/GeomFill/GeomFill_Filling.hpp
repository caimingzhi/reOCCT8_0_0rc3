#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Integer.hpp>

class GeomFill_Filling
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_Filling();

  Standard_EXPORT int NbUPoles() const;

  Standard_EXPORT int NbVPoles() const;

  Standard_EXPORT void Poles(NCollection_Array2<gp_Pnt>& Poles) const;

  Standard_EXPORT bool isRational() const;

  Standard_EXPORT void Weights(NCollection_Array2<double>& Weights) const;

protected:
  bool                                     IsRational;
  occ::handle<NCollection_HArray2<gp_Pnt>> myPoles;
  occ::handle<NCollection_HArray2<double>> myWeights;
};
