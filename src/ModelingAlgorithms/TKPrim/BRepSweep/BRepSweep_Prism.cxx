#include <BRepSweep_Prism.hpp>
#include <BRepSweep_Translation.hpp>
#include <gp_Dir.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Sweep_NumShape.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Shape.hpp>

BRepSweep_Prism::BRepSweep_Prism(const TopoDS_Shape& S,
                                 const gp_Vec&       V,
                                 const bool          C,
                                 const bool          Canonize)
    : myTranslation(S, NumShape(), Location(V), V, C, Canonize)
{
  Standard_ConstructionError_Raise_if(V.Magnitude() <= Precision::Confusion(),
                                      "BRepSweep_Prism::Constructor");
}

BRepSweep_Prism::BRepSweep_Prism(const TopoDS_Shape& S,
                                 const gp_Dir&       D,
                                 const bool          Inf,
                                 const bool          C,
                                 const bool          Canonize)
    : myTranslation(S, NumShape(Inf), Location(D), D, C, Canonize)
{
}

TopoDS_Shape BRepSweep_Prism::Shape()
{
  return myTranslation.Shape();
}

TopoDS_Shape BRepSweep_Prism::Shape(const TopoDS_Shape& aGenS)
{
  return myTranslation.Shape(aGenS);
}

TopoDS_Shape BRepSweep_Prism::FirstShape()
{
  return myTranslation.FirstShape();
}

TopoDS_Shape BRepSweep_Prism::FirstShape(const TopoDS_Shape& aGenS)
{
  return myTranslation.FirstShape(aGenS);
}

TopoDS_Shape BRepSweep_Prism::LastShape()
{
  return myTranslation.LastShape();
}

TopoDS_Shape BRepSweep_Prism::LastShape(const TopoDS_Shape& aGenS)
{
  return myTranslation.LastShape(aGenS);
}

gp_Vec BRepSweep_Prism::Vec() const
{
  return myTranslation.Vec();
}

Sweep_NumShape BRepSweep_Prism::NumShape() const
{
  return Sweep_NumShape(2, TopAbs_EDGE);
}

Sweep_NumShape BRepSweep_Prism::NumShape(const bool Inf) const
{
  Sweep_NumShape N;
  if (Inf)
  {
    N.Init(0, TopAbs_EDGE, false, true, true);
  }
  else
  {
    N.Init(1, TopAbs_EDGE, false, false, true);
  }
  return N;
}

TopLoc_Location BRepSweep_Prism::Location(const gp_Vec& V) const
{
  gp_Trsf gpt;
  gpt.SetTranslation(V);
  TopLoc_Location L(gpt);
  return L;
}

bool BRepSweep_Prism::IsUsed(const TopoDS_Shape& aGenS) const
{
  return myTranslation.IsUsed(aGenS);
}

bool BRepSweep_Prism::GenIsUsed(const TopoDS_Shape& aGenS) const
{
  return myTranslation.GenIsUsed(aGenS);
}
