

#include <GeomAdaptor_Surface.hpp>
#include <ShapeUpgrade_SplitSurfaceArea.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurfaceArea, ShapeUpgrade_SplitSurface)

ShapeUpgrade_SplitSurfaceArea::ShapeUpgrade_SplitSurfaceArea()

{
  myNbParts  = 1;
  myUnbSplit = myVnbSplit  = -1;
  myIsSplittingIntoSquares = false;
}

void ShapeUpgrade_SplitSurfaceArea::Compute(const bool)
{
  if (myNbParts <= 1)
    return;

  GeomAdaptor_Surface ads(mySurface,
                          myUSplitValues->Value(1),
                          myUSplitValues->Value(2),
                          myVSplitValues->Value(1),
                          myVSplitValues->Value(2));
  double              aKoefU = ads.UResolution(1.);
  double              aKoefV = ads.VResolution(1.);
  if (aKoefU == 0)
    aKoefU = 1.;
  if (aKoefV == 0)
    aKoefV = 1.;
  double aUSize = fabs(myUSplitValues->Value(2) - myUSplitValues->Value(1)) / aKoefU;
  double aVSize = fabs(myVSplitValues->Value(2) - myVSplitValues->Value(1)) / aKoefV;
  double aNbUV  = aUSize / aVSize;
  occ::handle<NCollection_HSequence<double>> aFirstSplit =
    (aNbUV < 1. ? myVSplitValues : myUSplitValues);
  occ::handle<NCollection_HSequence<double>> aSecondSplit =
    (aNbUV < 1. ? myUSplitValues : myVSplitValues);
  bool anIsUFirst = (aNbUV > 1.);
  if (aNbUV < 1)
    aNbUV = 1. / aNbUV;

  bool anIsFixedUVnbSplits = (myUnbSplit > 0 && myVnbSplit > 0);
  int  nbSplitF, nbSplitS;
  if (myIsSplittingIntoSquares && myNbParts > 0)
  {
    if (!anIsFixedUVnbSplits)
    {
      double aSquareSize = std::sqrt(myArea / myNbParts);
      myUnbSplit         = (int)(myUsize / aSquareSize);
      myVnbSplit         = (int)(myVsize / aSquareSize);
      if (myUnbSplit == 0)
        myUnbSplit = 1;
      if (myVnbSplit == 0)
        myVnbSplit = 1;
    }

    if (anIsUFirst)
    {
      nbSplitF = myUnbSplit;
      nbSplitS = myVnbSplit;
    }
    else
    {
      nbSplitF = myVnbSplit;
      nbSplitS = myUnbSplit;
    }
  }
  else
  {
    nbSplitF = (aNbUV >= myNbParts ? myNbParts : RealToInt(ceil(sqrt(myNbParts * ceil(aNbUV)))));
    nbSplitS = (aNbUV >= myNbParts ? 0 : RealToInt(ceil((double)myNbParts / (double)nbSplitF)));
  }
  if (nbSplitS == 1 && !anIsFixedUVnbSplits)
    nbSplitS++;
  if (!nbSplitF)
    return;
  double aStep    = (aFirstSplit->Value(2) - aFirstSplit->Value(1)) / nbSplitF;
  double aPrevPar = aFirstSplit->Value(1);
  int    i        = 1;
  for (; i < nbSplitF; i++)
  {
    double aNextPar = aPrevPar + aStep;
    aFirstSplit->InsertBefore(i + 1, aNextPar);
    aPrevPar = aNextPar;
  }

  if (nbSplitS)
  {
    aStep    = (aSecondSplit->Value(2) - aSecondSplit->Value(1)) / nbSplitS;
    aPrevPar = aSecondSplit->Value(1);
    for (i = 1; i < nbSplitS; i++)
    {
      double aNextPar = aPrevPar + aStep;
      aSecondSplit->InsertBefore(i + 1, aNextPar);
      aPrevPar = aNextPar;
    }
  }
}
