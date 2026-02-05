#include <IntCurveSurface_ThePolygonOfHInter.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Bnd_Box.hpp>
#include <gp_Pnt.hpp>
#include "IntCurveSurface_PolygonUtils.hpp"
#include <IntCurveSurface_TheHCurveTool.hpp>
#include <Standard_OutOfRange.hpp>

//==================================================================================================

IntCurveSurface_ThePolygonOfHInter::IntCurveSurface_ThePolygonOfHInter(
  const occ::handle<Adaptor3d_Curve>& Curve,
  const int                           NbPnt)
    : ThePnts(1, (NbPnt < 5) ? 5 : NbPnt),
      ClosedPolygon(false)
{
  NbPntIn = (NbPnt < 5) ? 5 : NbPnt;
  Binf    = IntCurveSurface_TheHCurveTool::FirstParameter(Curve);
  Bsup    = IntCurveSurface_TheHCurveTool::LastParameter(Curve);
  Init(Curve);
}

//==================================================================================================

IntCurveSurface_ThePolygonOfHInter::IntCurveSurface_ThePolygonOfHInter(
  const occ::handle<Adaptor3d_Curve>& Curve,
  const double                        U1,
  const double                        U2,
  const int                           NbPnt)
    : ThePnts(1, (NbPnt < 5) ? 5 : NbPnt),
      ClosedPolygon(false),
      Binf(U1),
      Bsup(U2)
{
  NbPntIn = (NbPnt < 5) ? 5 : NbPnt;
  Init(Curve);
}

//==================================================================================================

IntCurveSurface_ThePolygonOfHInter::IntCurveSurface_ThePolygonOfHInter(
  const occ::handle<Adaptor3d_Curve>& Curve,
  const NCollection_Array1<double>&   Upars)
    : ThePnts(1, Upars.Length()),
      ClosedPolygon(false),
      Binf(Upars(Upars.Lower())),
      Bsup(Upars(Upars.Upper()))
{
  NbPntIn = Upars.Length();
  Init(Curve, Upars);
}

//==================================================================================================

void IntCurveSurface_ThePolygonOfHInter::Init(const occ::handle<Adaptor3d_Curve>& Curve)
{
  IntCurveSurface_PolygonUtils::InitUniform<occ::handle<Adaptor3d_Curve>,
                                            IntCurveSurface_TheHCurveTool>(Curve,
                                                                           Binf,
                                                                           Bsup,
                                                                           NbPntIn,
                                                                           ThePnts,
                                                                           TheBnd,
                                                                           TheDeflection);
  ClosedPolygon = false;
}

//==================================================================================================

void IntCurveSurface_ThePolygonOfHInter::Init(const occ::handle<Adaptor3d_Curve>& Curve,
                                              const NCollection_Array1<double>&   Upars)
{
  IntCurveSurface_PolygonUtils::InitWithParams<occ::handle<Adaptor3d_Curve>,
                                               IntCurveSurface_TheHCurveTool>(Curve,
                                                                              Upars,
                                                                              NbPntIn,
                                                                              ThePnts,
                                                                              TheBnd,
                                                                              TheDeflection,
                                                                              myParams);
  ClosedPolygon = false;
}

//==================================================================================================

double IntCurveSurface_ThePolygonOfHInter::ApproxParamOnCurve(const int    Index,
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

void IntCurveSurface_ThePolygonOfHInter::Dump() const {}
