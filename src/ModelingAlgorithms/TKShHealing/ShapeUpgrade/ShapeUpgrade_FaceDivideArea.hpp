#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeUpgrade_FaceDivide.hpp>
class TopoDS_Face;

class ShapeUpgrade_FaceDivideArea : public ShapeUpgrade_FaceDivide
{

public:
  Standard_EXPORT ShapeUpgrade_FaceDivideArea();

  Standard_EXPORT ShapeUpgrade_FaceDivideArea(const TopoDS_Face& F);

  Standard_EXPORT bool Perform(const double theArea = 0.) override;

  double& MaxArea();

  int& NbParts();

  void SetNumbersUVSplits(const int theNbUsplits, const int theNbVsplits);

  void SetSplittingByNumber(const bool theIsSplittingByNumber);

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_FaceDivideArea, ShapeUpgrade_FaceDivide)

private:
  double myMaxArea;
  int    myNbParts;
  int    myUnbSplit;
  int    myVnbSplit;
  bool   myIsSplittingByNumber;
};

inline double& ShapeUpgrade_FaceDivideArea::MaxArea()
{
  return myMaxArea;
}

inline int& ShapeUpgrade_FaceDivideArea::NbParts()
{
  return myNbParts;
}

inline void ShapeUpgrade_FaceDivideArea::SetSplittingByNumber(const bool theIsSplittingByNumber)
{
  myIsSplittingByNumber = theIsSplittingByNumber;
}

inline void ShapeUpgrade_FaceDivideArea::SetNumbersUVSplits(const int theNbUsplits,
                                                            const int theNbVsplits)
{
  myUnbSplit = theNbUsplits;
  myVnbSplit = theNbVsplits;
  if (myUnbSplit > 0 && myVnbSplit > 0)
    myNbParts = myUnbSplit * myVnbSplit;
}
