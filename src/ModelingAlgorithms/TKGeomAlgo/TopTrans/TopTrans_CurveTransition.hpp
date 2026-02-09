#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Dir.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>

class TopTrans_CurveTransition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopTrans_CurveTransition();

  Standard_EXPORT void Reset(const gp_Dir& Tgt, const gp_Dir& Norm, const double Curv);

  Standard_EXPORT void Reset(const gp_Dir& Tgt);

  Standard_EXPORT void Compare(const double             Tole,
                               const gp_Dir&            Tang,
                               const gp_Dir&            Norm,
                               const double             Curv,
                               const TopAbs_Orientation S,
                               const TopAbs_Orientation Or);

  Standard_EXPORT TopAbs_State StateBefore() const;

  Standard_EXPORT TopAbs_State StateAfter() const;

private:
  Standard_EXPORT bool IsBefore(const double  Tole,
                                const double  Angl,
                                const gp_Dir& Nor1,
                                const double  Cur1,
                                const gp_Dir& Nor2,
                                const double  Cur2) const;

  Standard_EXPORT int Compare(const double Ang1, const double Ang2, const double Tole) const;

  gp_Dir             myTgt;
  gp_Dir             myNorm;
  double             myCurv;
  bool               Init;
  gp_Dir             TgtFirst;
  gp_Dir             NormFirst;
  double             CurvFirst;
  TopAbs_Orientation TranFirst;
  gp_Dir             TgtLast;
  gp_Dir             NormLast;
  double             CurvLast;
  TopAbs_Orientation TranLast;
};
