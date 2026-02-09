

#include <BRepBlend_PointOnRst.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <IntSurf_Transition.hpp>

BRepBlend_PointOnRst::BRepBlend_PointOnRst()
    : prm(0.0)
{
}

BRepBlend_PointOnRst::BRepBlend_PointOnRst(const occ::handle<Adaptor2d_Curve2d>& A,
                                           const double                          Param,
                                           const IntSurf_Transition&             TLine,
                                           const IntSurf_Transition&             TArc)
    :

      arc(A),
      traline(TLine),
      traarc(TArc),
      prm(Param)
{
}

void BRepBlend_PointOnRst::SetArc(const occ::handle<Adaptor2d_Curve2d>& A,
                                  const double                          Param,
                                  const IntSurf_Transition&             TLine,
                                  const IntSurf_Transition&             TArc)
{
  arc     = A;
  prm     = Param;
  traline = TLine;
  traarc  = TArc;
}
