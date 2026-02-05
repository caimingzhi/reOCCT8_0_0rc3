#include <HLRBRep_ThePolygonOfInterCSurf.hpp>

#include <Bnd_Box.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <HLRBRep_LineTool.hpp>
#include "../../TKGeomAlgo/IntCurveSurface/IntCurveSurface_PolygonUtils.hpp"
#include <Standard_OutOfRange.hpp>

//==================================================================================================

HLRBRep_ThePolygonOfInterCSurf::HLRBRep_ThePolygonOfInterCSurf(const gp_Lin& Curve, const int NbPnt)
    : ThePnts(1, (NbPnt < 5) ? 5 : NbPnt),
      ClosedPolygon(false)
{
  NbPntIn = (NbPnt < 5) ? 5 : NbPnt;
  Binf    = HLRBRep_LineTool::FirstParameter(Curve);
  Bsup    = HLRBRep_LineTool::LastParameter(Curve);
  Init(Curve);
}

//==================================================================================================

HLRBRep_ThePolygonOfInterCSurf::HLRBRep_ThePolygonOfInterCSurf(const gp_Lin& Curve,
                                                               const double  U1,
                                                               const double  U2,
                                                               const int     NbPnt)
    : ThePnts(1, (NbPnt < 5) ? 5 : NbPnt),
      ClosedPolygon(false),
      Binf(U1),
      Bsup(U2)
{
  NbPntIn = (NbPnt < 5) ? 5 : NbPnt;
  Init(Curve);
}

//==================================================================================================

HLRBRep_ThePolygonOfInterCSurf::HLRBRep_ThePolygonOfInterCSurf(
  const gp_Lin&                     Curve,
  const NCollection_Array1<double>& Upars)
    : ThePnts(1, Upars.Length()),
      ClosedPolygon(false),
      Binf(Upars(Upars.Lower())),
      Bsup(Upars(Upars.Upper()))
{
  NbPntIn = Upars.Length();
  Init(Curve, Upars);
}

//==================================================================================================

void HLRBRep_ThePolygonOfInterCSurf::Init(const gp_Lin& Curve)
{
  IntCurveSurface_PolygonUtils::InitUniform<gp_Lin, HLRBRep_LineTool>(Curve,
                                                                      Binf,
                                                                      Bsup,
                                                                      NbPntIn,
                                                                      ThePnts,
                                                                      TheBnd,
                                                                      TheDeflection);
  ClosedPolygon = false;
}

//==================================================================================================

void HLRBRep_ThePolygonOfInterCSurf::Init(const gp_Lin&                     Curve,
                                          const NCollection_Array1<double>& Upars)
{
  IntCurveSurface_PolygonUtils::InitWithParams<gp_Lin, HLRBRep_LineTool>(Curve,
                                                                         Upars,
                                                                         NbPntIn,
                                                                         ThePnts,
                                                                         TheBnd,
                                                                         TheDeflection,
                                                                         myParams);
  ClosedPolygon = false;
}

//==================================================================================================

double HLRBRep_ThePolygonOfInterCSurf::ApproxParamOnCurve(const int    Index,
                                                          const double ParamOnLine) const
{
  return IntCurveSurface_PolygonUtils::ApproxParamOnCurve(Index,
                                                          ParamOnLine,
                                                          Binf,
                                                          Bsup,
                                                          NbPntIn,
                                                          myParams);
}

//==================================================================================================

void HLRBRep_ThePolygonOfInterCSurf::Dump() const {}
