#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTrans_CurveTransition.hpp>
#include <TopAbs_Orientation.hpp>
class gp_Dir;

class TopCnx_EdgeFaceTransition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopCnx_EdgeFaceTransition();

  Standard_EXPORT void Reset(const gp_Dir& Tgt, const gp_Dir& Norm, const double Curv);

  Standard_EXPORT void Reset(const gp_Dir& Tgt);

  Standard_EXPORT void AddInterference(const double             Tole,
                                       const gp_Dir&            Tang,
                                       const gp_Dir&            Norm,
                                       const double             Curv,
                                       const TopAbs_Orientation Or,
                                       const TopAbs_Orientation Tr,
                                       const TopAbs_Orientation BTr);

  Standard_EXPORT TopAbs_Orientation Transition() const;

  Standard_EXPORT TopAbs_Orientation BoundaryTransition() const;

private:
  TopTrans_CurveTransition myCurveTransition;
  int                      nbBoundForward;
  int                      nbBoundReversed;
};
