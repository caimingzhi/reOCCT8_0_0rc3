#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Dir.hpp>
#include <NCollection_Array2.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>

class TopTrans_SurfaceTransition
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopTrans_SurfaceTransition();

  Standard_EXPORT void Reset(const gp_Dir& Tgt,
                             const gp_Dir& Norm,
                             const gp_Dir& MaxD,
                             const gp_Dir& MinD,
                             const double  MaxCurv,
                             const double  MinCurv);

  Standard_EXPORT void Reset(const gp_Dir& Tgt, const gp_Dir& Norm);

  Standard_EXPORT void Compare(const double             Tole,
                               const gp_Dir&            Norm,
                               const gp_Dir&            MaxD,
                               const gp_Dir&            MinD,
                               const double             MaxCurv,
                               const double             MinCurv,
                               const TopAbs_Orientation S,
                               const TopAbs_Orientation O);

  Standard_EXPORT void Compare(const double             Tole,
                               const gp_Dir&            Norm,
                               const TopAbs_Orientation S,
                               const TopAbs_Orientation O);

  Standard_EXPORT TopAbs_State StateBefore() const;

  Standard_EXPORT TopAbs_State StateAfter() const;

  Standard_EXPORT static TopAbs_State GetBefore(const TopAbs_Orientation Tran);

  Standard_EXPORT static TopAbs_State GetAfter(const TopAbs_Orientation Tran);

private:
  Standard_EXPORT void UpdateReference(const double             Tole,
                                       const bool               isInfRef,
                                       double&                  CosInf,
                                       double&                  CosSup,
                                       const TopAbs_Orientation Tran,
                                       TopAbs_Orientation&      TranRef);

  Standard_EXPORT double ComputeCos(const double             Tole,
                                    const gp_Dir&            Norm,
                                    const TopAbs_Orientation O,
                                    bool&                    isleft) const;

  gp_Dir                                 myTgt;
  gp_Dir                                 myNorm;
  gp_Dir                                 beafter;
  double                                 myCurvRef;
  NCollection_Array2<double>             myAng;
  NCollection_Array2<double>             myCurv;
  NCollection_Array2<TopAbs_Orientation> myOri;
  bool                                   myTouchFlag;
};
