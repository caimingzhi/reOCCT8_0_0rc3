#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Law_Function.hpp>
#include <NCollection_List.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>

class Law_Composite : public Law_Function
{

public:
  Standard_EXPORT Law_Composite();

  Standard_EXPORT Law_Composite(const double First, const double Last, const double Tol);

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT double Value(const double X) override;

  Standard_EXPORT void D1(const double X, double& F, double& D) override;

  Standard_EXPORT void D2(const double X, double& F, double& D, double& D2) override;

  Standard_EXPORT occ::handle<Law_Function> Trim(const double PFirst,
                                                 const double PLast,
                                                 const double Tol) const override;

  Standard_EXPORT void Bounds(double& PFirst, double& PLast) override;

  Standard_EXPORT occ::handle<Law_Function>& ChangeElementaryLaw(const double W);

  Standard_EXPORT NCollection_List<occ::handle<Law_Function>>& ChangeLaws();

  Standard_EXPORT bool IsPeriodic() const;

  Standard_EXPORT void SetPeriodic();

  DEFINE_STANDARD_RTTIEXT(Law_Composite, Law_Function)

private:
  Standard_EXPORT void Prepare(double& W);

  double                                      first;
  double                                      last;
  occ::handle<Law_Function>                   curfunc;
  NCollection_List<occ::handle<Law_Function>> funclist;
  bool                                        periodic;
  double                                      TFirst;
  double                                      TLast;
  double                                      PTol;
};
