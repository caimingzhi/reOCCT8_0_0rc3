#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Pnt.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class GeomFill_Boundary;
class Law_Function;
class gp_Vec;

//! Provides evaluation methods on an algorithmic
//! patch (based on 4 Curves) defined by its boundaries and blending
//! functions.
class GeomFill_CoonsAlgPatch : public Standard_Transient
{

public:
  //! Constructs the algorithmic patch. By Default the
  //! constructed blending functions are linear.
  //! Warning: No control is done on the bounds.
  //! B1/B3 and B2/B4 must be same range and well oriented.
  Standard_EXPORT GeomFill_CoonsAlgPatch(const occ::handle<GeomFill_Boundary>& B1,
                                         const occ::handle<GeomFill_Boundary>& B2,
                                         const occ::handle<GeomFill_Boundary>& B3,
                                         const occ::handle<GeomFill_Boundary>& B4);

  //! Give the blending functions.
  Standard_EXPORT void Func(occ::handle<Law_Function>& f1, occ::handle<Law_Function>& f2) const;

  //! Set the blending functions.
  Standard_EXPORT void SetFunc(const occ::handle<Law_Function>& f1,
                               const occ::handle<Law_Function>& f2);

  //! Computes the value on the algorithmic patch at
  //! parameters U and V.
  Standard_EXPORT gp_Pnt Value(const double U, const double V) const;

  //! Computes the d/dU partial derivative on the
  //! algorithmic patch at parameters U and V.
  Standard_EXPORT gp_Vec D1U(const double U, const double V) const;

  //! Computes the d/dV partial derivative on the
  //! algorithmic patch at parameters U and V.
  Standard_EXPORT gp_Vec D1V(const double U, const double V) const;

  //! Computes the d2/dUdV partial derivative on the
  //! algorithmic patch made with linear blending functions
  //! at parameter U and V.
  Standard_EXPORT gp_Vec DUV(const double U, const double V) const;

  Standard_EXPORT const gp_Pnt& Corner(const int I) const;

  Standard_EXPORT const occ::handle<GeomFill_Boundary>& Bound(const int I) const;

  Standard_EXPORT const occ::handle<Law_Function>& Func(const int I) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_CoonsAlgPatch, Standard_Transient)

private:
  occ::handle<GeomFill_Boundary> bound[4];
  gp_Pnt                         c[4];
  occ::handle<Law_Function>      a[2];
};

