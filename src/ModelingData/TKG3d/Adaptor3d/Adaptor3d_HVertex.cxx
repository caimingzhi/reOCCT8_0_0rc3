

#include <Adaptor3d_HVertex.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <ElCLib.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Adaptor3d_HVertex, Standard_Transient)

Adaptor3d_HVertex::Adaptor3d_HVertex()
    : myTol(0.0)
{
}

Adaptor3d_HVertex::Adaptor3d_HVertex(const gp_Pnt2d&          P,
                                     const TopAbs_Orientation Or,
                                     const double             Resolution)
    : myPnt(P),
      myTol(Resolution),
      myOri(Or)
{
}

gp_Pnt2d Adaptor3d_HVertex::Value()
{
  return myPnt;
}

double Adaptor3d_HVertex::Parameter(const occ::handle<Adaptor2d_Curve2d>& C)
{
  return ElCLib::Parameter(C->Line(), myPnt);
}

double Adaptor3d_HVertex::Resolution(const occ::handle<Adaptor2d_Curve2d>&)
{
  return myTol;
}

TopAbs_Orientation Adaptor3d_HVertex::Orientation()
{
  return myOri;
}

bool Adaptor3d_HVertex::IsSame(const occ::handle<Adaptor3d_HVertex>& Other)
{
  return (myPnt.Distance(Other->Value()) <= Precision::Confusion());
}
