

#include <BRepClass_FaceClassifier.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <BRepClass_FaceExplorer.hpp>
#include <BRepTools.hpp>
#include <Extrema_ExtPS.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <TopoDS_Face.hpp>

BRepClass_FaceClassifier::BRepClass_FaceClassifier() = default;

BRepClass_FaceClassifier::BRepClass_FaceClassifier(BRepClass_FaceExplorer& F,
                                                   const gp_Pnt2d&         P,
                                                   const double            Tol)
    : BRepClass_FClassifier(F, P, Tol)
{
}

BRepClass_FaceClassifier::BRepClass_FaceClassifier(const TopoDS_Face& theF,
                                                   const gp_Pnt&      theP,
                                                   const double       theTol,
                                                   const bool         theUseBndBox,
                                                   const double       theGapCheckTol)
{
  Perform(theF, theP, theTol, theUseBndBox, theGapCheckTol);
}

BRepClass_FaceClassifier::BRepClass_FaceClassifier(const TopoDS_Face& theF,
                                                   const gp_Pnt2d&    theP,
                                                   const double       theTol,
                                                   const bool         theUseBndBox,
                                                   const double       theGapCheckTol)
{
  Perform(theF, theP, theTol, theUseBndBox, theGapCheckTol);
}

void BRepClass_FaceClassifier::Perform(const TopoDS_Face& theF,
                                       const gp_Pnt2d&    theP,
                                       const double       theTol,
                                       const bool         theUseBndBox,
                                       const double       theGapCheckTol)
{
  BRepClass_FaceExplorer aFex(theF);
  aFex.SetMaxTolerance(theGapCheckTol);
  aFex.SetUseBndBox(theUseBndBox);
  BRepClass_FClassifier::Perform(aFex, theP, theTol);
}

void BRepClass_FaceClassifier::Perform(const TopoDS_Face& theF,
                                       const gp_Pnt&      theP,
                                       const double       theTol,
                                       const bool         theUseBndBox,
                                       const double       theGapCheckTol)
{
  int           aNbExt, aIndice, i;
  double        aU1, aU2, aV1, aV2, aMaxDist, aD;
  gp_Pnt2d      aPuv;
  Extrema_ExtPS aExtrema;

  aMaxDist = RealLast();
  aIndice  = 0;

  BRepAdaptor_Surface aSurf(theF, false);
  BRepTools::UVBounds(theF, aU1, aU2, aV1, aV2);
  aExtrema.Initialize(aSurf, aU1, aU2, aV1, aV2, theTol, theTol);

  rejected = true;

  aExtrema.Perform(theP);
  if (!aExtrema.IsDone())
  {
    return;
  }

  aNbExt = aExtrema.NbExt();
  if (!aNbExt)
  {
    return;
  }

  for (i = 1; i <= aNbExt; ++i)
  {
    aD = aExtrema.SquareDistance(i);
    if (aD < aMaxDist)
    {
      aMaxDist = aD;
      aIndice  = i;
    }
  }

  if (aIndice)
  {
    aExtrema.Point(aIndice).Parameter(aU1, aU2);
    aPuv.SetCoord(aU1, aU2);
    Perform(theF, aPuv, theTol, theUseBndBox, theGapCheckTol);
  }
}
