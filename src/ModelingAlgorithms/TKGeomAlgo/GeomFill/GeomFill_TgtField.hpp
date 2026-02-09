#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Real.hpp>
class Law_BSpline;
class gp_Vec;

class GeomFill_TgtField : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool IsScalable() const;

  Standard_EXPORT virtual void Scale(const occ::handle<Law_BSpline>& Func);

  Standard_EXPORT virtual gp_Vec Value(const double W) const = 0;

  Standard_EXPORT virtual gp_Vec D1(const double W) const = 0;

  Standard_EXPORT virtual void D1(const double W, gp_Vec& V, gp_Vec& DV) const = 0;

  DEFINE_STANDARD_RTTIEXT(GeomFill_TgtField, Standard_Transient)
};
