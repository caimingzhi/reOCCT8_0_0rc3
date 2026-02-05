#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <GeomFill_TgtField.hpp>
class GeomFill_CoonsAlgPatch;
class gp_Vec;

//! Defines an algorithmic tangents field on a
//! boundary of a CoonsAlgPatch.
class GeomFill_TgtOnCoons : public GeomFill_TgtField
{

public:
  Standard_EXPORT GeomFill_TgtOnCoons(const occ::handle<GeomFill_CoonsAlgPatch>& K, const int I);

  //! Computes the value of the field of tangency at
  //! parameter W.
  Standard_EXPORT gp_Vec Value(const double W) const override;

  //! Computes the derivative of the field of tangency at
  //! parameter W.
  Standard_EXPORT gp_Vec D1(const double W) const override;

  //! Computes the value and the derivative of the field of
  //! tangency at parameter W.
  Standard_EXPORT void D1(const double W, gp_Vec& T, gp_Vec& DT) const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_TgtOnCoons, GeomFill_TgtField)

private:
  occ::handle<GeomFill_CoonsAlgPatch> myK;
  int                                 ibound;
};
