#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>

class Geom_BSplineCurve;

class HelixGeom_Tools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int ApprHelix(const double                    aT1,
                                       const double                    aT2,
                                       const double                    aPitch,
                                       const double                    aRStart,
                                       const double                    aTaperAngle,
                                       const bool                      aIsCW,
                                       const double                    aTol,
                                       occ::handle<Geom_BSplineCurve>& theBSpl,
                                       double&                         theMaxError);

  Standard_EXPORT static int ApprCurve3D(const occ::handle<Adaptor3d_Curve>& theHC,
                                         const double                        theTol,
                                         const GeomAbs_Shape                 theCont,
                                         const int                           theMaxSeg,
                                         const int                           theMaxDeg,
                                         occ::handle<Geom_BSplineCurve>&     theBSpl,
                                         double&                             theMaxError);
};
