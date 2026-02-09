#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <ShapeUpgrade_ShapeDivide.hpp>
class TopoDS_Shape;
class ShapeUpgrade_FaceDivide;

class ShapeUpgrade_ShapeDivideArea : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShapeDivideArea();

  Standard_EXPORT ShapeUpgrade_ShapeDivideArea(const TopoDS_Shape& S);

  double& MaxArea();

  int& NbParts();

  void SetNumbersUVSplits(const int theNbUsplits, const int theNbVsplits);

  void SetSplittingByNumber(const bool theIsSplittingByNumber);

protected:
  Standard_EXPORT occ::handle<ShapeUpgrade_FaceDivide> GetSplitFaceTool() const override;

private:
  double myMaxArea;
  int    myNbParts;
  int    myUnbSplit;
  int    myVnbSplit;
  bool   myIsSplittingByNumber;
};

inline double& ShapeUpgrade_ShapeDivideArea::MaxArea()
{
  return myMaxArea;
}

inline int& ShapeUpgrade_ShapeDivideArea::NbParts()
{
  return myNbParts;
}

inline void ShapeUpgrade_ShapeDivideArea::SetSplittingByNumber(const bool theIsSplittingByNumber)
{
  myIsSplittingByNumber = theIsSplittingByNumber;
  if (myIsSplittingByNumber)
    myMaxArea = -1;
}

inline void ShapeUpgrade_ShapeDivideArea::SetNumbersUVSplits(const int theNbUsplits,
                                                             const int theNbVsplits)
{
  myIsSplittingByNumber = true;
  myMaxArea             = -1;
  myUnbSplit            = theNbUsplits;
  myVnbSplit            = theNbVsplits;
  if (myUnbSplit > 0 && myVnbSplit > 0)
    myNbParts = myUnbSplit * myVnbSplit;
}
