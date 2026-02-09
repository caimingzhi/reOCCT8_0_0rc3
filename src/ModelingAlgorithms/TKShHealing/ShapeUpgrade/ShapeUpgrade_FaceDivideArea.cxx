

#include <BRep_Builder.hpp>
#include <BRepGProp.hpp>
#include <GProp_GProps.hpp>
#include <Precision.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <ShapeExtend.hpp>
#include <ShapeUpgrade_FaceDivideArea.hpp>
#include <ShapeUpgrade_SplitSurfaceArea.hpp>
#include <Standard_Type.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_FaceDivideArea, ShapeUpgrade_FaceDivide)

ShapeUpgrade_FaceDivideArea::ShapeUpgrade_FaceDivideArea()
{
  myMaxArea  = Precision::Infinite();
  myNbParts  = 0;
  myUnbSplit = myVnbSplit = -1;
  myIsSplittingByNumber   = false;
  SetPrecision(1.e-5);
  SetSplitSurfaceTool(new ShapeUpgrade_SplitSurfaceArea);
}

ShapeUpgrade_FaceDivideArea::ShapeUpgrade_FaceDivideArea(const TopoDS_Face& F)
{
  myMaxArea  = Precision::Infinite();
  myNbParts  = 0;
  myUnbSplit = myVnbSplit = -1;
  myIsSplittingByNumber   = false;
  SetPrecision(1.e-5);
  SetSplitSurfaceTool(new ShapeUpgrade_SplitSurfaceArea);
  Init(F);
}

bool ShapeUpgrade_FaceDivideArea::Perform(const double)
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  GProp_GProps aGprop;

  BRepGProp::SurfaceProperties(myFace, aGprop, Precision());
  double anArea = aGprop.Mass();

  int anbParts = 0;
  if (myMaxArea == -1)
  {
    anbParts  = myNbParts;
    myMaxArea = anArea / anbParts;
  }

  if ((anArea - myMaxArea) < Precision::Confusion())
    return false;

  if (anbParts == 0)
    anbParts = RealToInt(ceil(anArea / myMaxArea));

  occ::handle<ShapeUpgrade_SplitSurfaceArea> aSurfTool =
    occ::down_cast<ShapeUpgrade_SplitSurfaceArea>(GetSplitSurfaceTool());
  if (aSurfTool.IsNull())
    return false;
  aSurfTool->NbParts() = anbParts;
  if (myIsSplittingByNumber)
  {
    aSurfTool->SetSplittingIntoSquares(true);
    aSurfTool->SetNumbersUVSplits(myUnbSplit, myVnbSplit);
  }
  if (!ShapeUpgrade_FaceDivide::Perform(anArea))
    return false;

  TopoDS_Shape aResult = Result();
  if (aResult.ShapeType() == TopAbs_FACE)
    return false;
  int aStatus = myStatus;

  if (!myIsSplittingByNumber)
  {
    TopExp_Explorer aExpF(aResult, TopAbs_FACE);
    TopoDS_Shape    aCopyRes = aResult.EmptyCopied();

    bool isModified = false;
    for (; aExpF.More(); aExpF.Next())
    {
      TopoDS_Shape aSh   = Context()->Apply(aExpF.Current());
      TopoDS_Face  aFace = TopoDS::Face(aSh);
      Init(aFace);
      BRep_Builder aB;
      if (Perform())
      {
        isModified           = true;
        TopoDS_Shape    aRes = Result();
        TopExp_Explorer aExpR(aRes, TopAbs_FACE);
        for (; aExpR.More(); aExpR.Next())
          aB.Add(aCopyRes, aExpR.Current());
      }
      else
        aB.Add(aCopyRes, aFace);
    }
    if (isModified)
    {
      if (aCopyRes.ShapeType() == TopAbs_WIRE || aCopyRes.ShapeType() == TopAbs_SHELL)
        aCopyRes.Closed(BRep_Tool::IsClosed(aCopyRes));
      Context()->Replace(aResult, aCopyRes);
    }
  }

  myStatus |= aStatus;
  myResult = Context()->Apply(aResult);
  return Status(ShapeExtend_DONE);
}
