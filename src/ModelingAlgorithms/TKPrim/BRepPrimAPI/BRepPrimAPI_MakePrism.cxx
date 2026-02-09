#include <BRepLib.hpp>
#include <BRepPrimAPI_MakePrism.hpp>
#include <BRepSweep_Prism.hpp>
#include <gp_Dir.hpp>
#include <gp_Vec.hpp>
#include <TopoDS_Shape.hpp>

static const TopoDS_Shape& check(const TopoDS_Shape& S)
{
  BRepLib::BuildCurves3d(S);
  return S;
}

BRepPrimAPI_MakePrism::BRepPrimAPI_MakePrism(const TopoDS_Shape& S,
                                             const gp_Vec&       V,
                                             const bool          Copy,
                                             const bool          Canonize)
    : myPrism(check(S), V, Copy, Canonize)
{
  Build();
}

BRepPrimAPI_MakePrism::BRepPrimAPI_MakePrism(const TopoDS_Shape& S,
                                             const gp_Dir&       D,
                                             const bool          Inf,
                                             const bool          Copy,
                                             const bool          Canonize)
    : myPrism(check(S), D, Inf, Copy, Canonize)
{
  Build();
}

const BRepSweep_Prism& BRepPrimAPI_MakePrism::Prism() const
{
  return myPrism;
}

void BRepPrimAPI_MakePrism::Build(const Message_ProgressRange&)
{
  myShape = myPrism.Shape();
  Done();
}

TopoDS_Shape BRepPrimAPI_MakePrism::FirstShape()
{
  return myPrism.FirstShape();
}

TopoDS_Shape BRepPrimAPI_MakePrism::LastShape()
{
  return myPrism.LastShape();
}

const NCollection_List<TopoDS_Shape>& BRepPrimAPI_MakePrism::Generated(const TopoDS_Shape& S)
{
  myGenerated.Clear();
  if (myPrism.IsUsed(S) && myPrism.GenIsUsed(S))
  {
    myGenerated.Append(myPrism.Shape(S));
  }
  return myGenerated;
}

TopoDS_Shape BRepPrimAPI_MakePrism::FirstShape(const TopoDS_Shape& theShape)
{
  return myPrism.FirstShape(theShape);
}

TopoDS_Shape BRepPrimAPI_MakePrism::LastShape(const TopoDS_Shape& theShape)
{
  return myPrism.LastShape(theShape);
}

bool BRepPrimAPI_MakePrism::IsDeleted(const TopoDS_Shape& S)
{
  return !myPrism.IsUsed(S);
}
