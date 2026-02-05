#include <BRepSweep_Revol.hpp>
#include <BRepSweep_Rotation.hpp>
#include <gp_Ax1.hpp>
#include <gp_Trsf.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Sweep_NumShape.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepSweep_Revol::BRepSweep_Revol(const TopoDS_Shape& S,
                                 const gp_Ax1&       Ax,
                                 const double        D,
                                 const bool          C)
    : myRotation(S.Oriented(TopAbs_FORWARD), NumShape(D), Location(Ax, D), Axe(Ax, D), Angle(D), C)
{
  Standard_ConstructionError_Raise_if(Angle(D) <= Precision::Angular(),
                                      "BRepSweep_Revol::Constructor");
}

//=================================================================================================

BRepSweep_Revol::BRepSweep_Revol(const TopoDS_Shape& S, const gp_Ax1& Ax, const bool C)
    : myRotation(S.Oriented(TopAbs_FORWARD),
                 NumShape(2 * M_PI),
                 Location(Ax, 2 * M_PI),
                 Axe(Ax, 2 * M_PI),
                 Angle(2 * M_PI),
                 C)

{
}

//=================================================================================================

TopoDS_Shape BRepSweep_Revol::Shape()
{
  return myRotation.Shape();
}

//=================================================================================================

TopoDS_Shape BRepSweep_Revol::Shape(const TopoDS_Shape& aGenS)
{
  return myRotation.Shape(aGenS);
}

//=================================================================================================

TopoDS_Shape BRepSweep_Revol::FirstShape()
{
  return myRotation.FirstShape();
}

//=================================================================================================

TopoDS_Shape BRepSweep_Revol::FirstShape(const TopoDS_Shape& aGenS)
{
  return myRotation.FirstShape(aGenS);
}

//=================================================================================================

TopoDS_Shape BRepSweep_Revol::LastShape()
{
  return myRotation.LastShape();
}

//=================================================================================================

TopoDS_Shape BRepSweep_Revol::LastShape(const TopoDS_Shape& aGenS)
{
  return myRotation.LastShape(aGenS);
}

//=================================================================================================

Sweep_NumShape BRepSweep_Revol::NumShape(const double D) const
{
  Sweep_NumShape N;
  if (std::abs(Angle(D) - 2 * M_PI) <= Precision::Angular())
  {
    N.Init(2, TopAbs_EDGE, true, false, false);
  }
  else
  {
    N.Init(2, TopAbs_EDGE);
  }
  return N;
}

//=================================================================================================

TopLoc_Location BRepSweep_Revol::Location(const gp_Ax1& Ax, const double D) const
{
  gp_Trsf gpt;
  gpt.SetRotation(Axe(Ax, D), Angle(D));
  TopLoc_Location L(gpt);
  return L;
}

//=================================================================================================

gp_Ax1 BRepSweep_Revol::Axe(const gp_Ax1& Ax, const double D) const
{
  gp_Ax1 A = Ax;
  if (D < 0.)
    A.Reverse();
  return A;
}

//=================================================================================================

double BRepSweep_Revol::Angle(const double D) const
{
  double d = std::abs(D);
  while (d > (2 * M_PI + Precision::Angular()))
  {
    d = d - 2 * M_PI;
  }
  return d;
}

//=================================================================================================

double BRepSweep_Revol::Angle() const
{
  return myRotation.Angle();
}

//=================================================================================================

gp_Ax1 BRepSweep_Revol::Axe() const
{
  return myRotation.Axe();
}

//=================================================================================================

bool BRepSweep_Revol::IsUsed(const TopoDS_Shape& aGenS) const
{
  return myRotation.IsUsed(aGenS);
}
