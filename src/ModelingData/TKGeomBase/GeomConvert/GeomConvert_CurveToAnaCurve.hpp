#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <GeomConvert_ConvType.hpp>
#include <GeomAbs_CurveType.hpp>

class Geom_Curve;
class Geom_Line;
class gp_Lin;
class gp_Pnt;
class gp_Circ;

class GeomConvert_CurveToAnaCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_CurveToAnaCurve();

  Standard_EXPORT GeomConvert_CurveToAnaCurve(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT bool ConvertToAnalytical(const double             theTol,
                                           occ::handle<Geom_Curve>& theResultCurve,
                                           const double             F,
                                           const double             L,
                                           double&                  newF,
                                           double&                  newL);

  Standard_EXPORT static occ::handle<Geom_Curve> ComputeCurve(
    const occ::handle<Geom_Curve>& curve,
    const double                   tolerance,
    const double                   c1,
    const double                   c2,
    double&                        cf,
    double&                        cl,
    double&                        theGap,
    const GeomConvert_ConvType     theCurvType = GeomConvert_MinGap,
    const GeomAbs_CurveType        theTarget   = GeomAbs_Line);

  Standard_EXPORT static occ::handle<Geom_Curve> ComputeCircle(const occ::handle<Geom_Curve>& curve,
                                                               const double tolerance,
                                                               const double c1,
                                                               const double c2,
                                                               double&      cf,
                                                               double&      cl,
                                                               double&      Deviation);

  Standard_EXPORT static occ::handle<Geom_Curve> ComputeEllipse(
    const occ::handle<Geom_Curve>& curve,
    const double                   tolerance,
    const double                   c1,
    const double                   c2,
    double&                        cf,
    double&                        cl,
    double&                        Deviation);

  Standard_EXPORT static occ::handle<Geom_Line> ComputeLine(const occ::handle<Geom_Curve>& curve,
                                                            const double tolerance,
                                                            const double c1,
                                                            const double c2,
                                                            double&      cf,
                                                            double&      cl,
                                                            double&      Deviation);

  Standard_EXPORT static bool IsLinear(const NCollection_Array1<gp_Pnt>& aPoints,
                                       const double                      tolerance,
                                       double&                           Deviation);

  Standard_EXPORT static gp_Lin GetLine(const gp_Pnt& P1, const gp_Pnt& P2, double& cf, double& cl);

  Standard_EXPORT static bool GetCircle(gp_Circ&      Circ,
                                        const gp_Pnt& P0,
                                        const gp_Pnt& P1,
                                        const gp_Pnt& P2);

  double Gap() const { return myGap; }

  GeomConvert_ConvType GetConvType() const { return myConvType; }

  void SetConvType(const GeomConvert_ConvType theConvType) { myConvType = theConvType; }

  GeomAbs_CurveType GetTarget() const { return myTarget; }

  void SetTarget(const GeomAbs_CurveType theTarget) { myTarget = theTarget; }

private:
  occ::handle<Geom_Curve> myCurve;
  double                  myGap;
  GeomConvert_ConvType    myConvType;
  GeomAbs_CurveType       myTarget;
};
