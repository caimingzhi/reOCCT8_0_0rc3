#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Real.hpp>

class Law_Function : public Standard_Transient
{

public:
  Standard_EXPORT virtual GeomAbs_Shape Continuity() const = 0;

  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const = 0;

  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const = 0;

  Standard_EXPORT virtual double Value(const double X) = 0;

  Standard_EXPORT virtual void D1(const double X, double& F, double& D) = 0;

  Standard_EXPORT virtual void D2(const double X, double& F, double& D, double& D2) = 0;

  Standard_EXPORT virtual occ::handle<Law_Function> Trim(const double PFirst,
                                                         const double PLast,
                                                         const double Tol) const = 0;

  Standard_EXPORT virtual void Bounds(double& PFirst, double& PLast) = 0;

  DEFINE_STANDARD_RTTIEXT(Law_Function, Standard_Transient)
};
