#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <ShapeUpgrade_SplitSurface.hpp>

class ShapeUpgrade_SplitSurfaceArea : public ShapeUpgrade_SplitSurface
{

public:
  Standard_EXPORT ShapeUpgrade_SplitSurfaceArea();

  int& NbParts();

  void SetSplittingIntoSquares(const bool theIsSplittingIntoSquares);

  void SetNumbersUVSplits(const int theNbUsplits, const int theNbVsplits);

  Standard_EXPORT void Compute(const bool Segment = true) override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurfaceArea, ShapeUpgrade_SplitSurface)

private:
  int  myNbParts;
  int  myUnbSplit;
  int  myVnbSplit;
  bool myIsSplittingIntoSquares;
};

inline int& ShapeUpgrade_SplitSurfaceArea::NbParts()
{
  return myNbParts;
}

inline void ShapeUpgrade_SplitSurfaceArea::SetSplittingIntoSquares(
  const bool theIsSplittingIntoSquares)
{
  myIsSplittingIntoSquares = theIsSplittingIntoSquares;
}

inline void ShapeUpgrade_SplitSurfaceArea::SetNumbersUVSplits(const int theNbUsplits,
                                                              const int theNbVsplits)
{
  myUnbSplit = theNbUsplits;
  myVnbSplit = theNbVsplits;
  if (myUnbSplit > 0 && myVnbSplit > 0)
    myNbParts = myUnbSplit * myVnbSplit;
}
