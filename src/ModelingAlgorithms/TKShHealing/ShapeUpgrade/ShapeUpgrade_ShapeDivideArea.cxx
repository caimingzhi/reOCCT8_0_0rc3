

#include <Precision.hpp>
#include <ShapeUpgrade_FaceDivide.hpp>
#include <ShapeUpgrade_FaceDivideArea.hpp>
#include <ShapeUpgrade_ShapeDivideArea.hpp>
#include <TopoDS_Shape.hpp>

ShapeUpgrade_ShapeDivideArea::ShapeUpgrade_ShapeDivideArea()

{
  myMaxArea  = Precision::Infinite();
  myNbParts  = 0;
  myUnbSplit = myVnbSplit = -1;
  myIsSplittingByNumber   = false;
}

ShapeUpgrade_ShapeDivideArea::ShapeUpgrade_ShapeDivideArea(const TopoDS_Shape& S)
    : ShapeUpgrade_ShapeDivide(S)

{
  myMaxArea  = Precision::Infinite();
  myNbParts  = 0;
  myUnbSplit = myVnbSplit = -1;
  myIsSplittingByNumber   = false;
}

occ::handle<ShapeUpgrade_FaceDivide> ShapeUpgrade_ShapeDivideArea::GetSplitFaceTool() const
{
  occ::handle<ShapeUpgrade_FaceDivideArea> aFaceTool = new ShapeUpgrade_FaceDivideArea;
  aFaceTool->MaxArea()                               = myMaxArea;
  aFaceTool->NbParts()                               = myNbParts;
  aFaceTool->SetNumbersUVSplits(myUnbSplit, myVnbSplit);
  aFaceTool->SetSplittingByNumber(myIsSplittingByNumber);
  return aFaceTool;
}
