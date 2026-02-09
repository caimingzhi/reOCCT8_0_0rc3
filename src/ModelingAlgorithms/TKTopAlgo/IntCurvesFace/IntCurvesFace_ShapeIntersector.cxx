#include <IntCurvesFace_ShapeIntersector.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Bnd_BoundSortBox.hpp>
#include <gp_Lin.hpp>
#include <IntCurvesFace_Intersector.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>

IntCurvesFace_ShapeIntersector::IntCurvesFace_ShapeIntersector()
    : myIsDone(false),
      myNbFaces(0)
{
}

void IntCurvesFace_ShapeIntersector::Load(const TopoDS_Shape& theShape, const double theTol)
{
  TopExp_Explorer Ex;
  int             i;
  for (myNbFaces = 0, i = 0, Ex.Init(theShape, TopAbs_FACE); Ex.More(); ++i, Ex.Next())
  {
    ++myNbFaces;
    TopoDS_Face aCurrentFace = TopoDS::Face(Ex.Current());
    myIntersector.Append(new IntCurvesFace_Intersector(aCurrentFace, theTol));
  }
}

void IntCurvesFace_ShapeIntersector::Perform(const gp_Lin& theL,
                                             const double  theParMin,
                                             const double  theParMax)
{
  myIsDone = false;
  for (int i = 1; i <= myNbFaces; ++i)
  {
    myIntersector.ChangeValue(i)->Perform(theL, theParMin, theParMax);
  }
  SortResult();
}

void IntCurvesFace_ShapeIntersector::PerformNearest(const gp_Lin& theL,
                                                    const double  theParMin,
                                                    const double  theParMax)
{
  int i = 0;
  if (myNbFaces > 2)
  {
    if (myPtrNums.IsEmpty())
    {
      myPtrNums      = NCollection_HArray1<int>(0, myNbFaces - 1);
      myPtrIndexNums = NCollection_HArray1<int>(0, myNbFaces - 1);
      for (; i < myNbFaces; ++i)
      {
        myPtrNums.ChangeValue(i)      = 0;
        myPtrIndexNums.ChangeValue(i) = i + 1;
      }
    }
  }

  int    anIndexFace = -1;
  double aParMax     = theParMax;
  myIsDone           = false;
  for (int ii = 1; ii <= myNbFaces; ++ii)
  {
    if (!myPtrNums.IsEmpty())
    {
      i = myPtrIndexNums.Value(ii - 1);
    }
    else
    {
      i = ii;
    }
    occ::handle<IntCurvesFace_Intersector> anIntersector = myIntersector.ChangeValue(i);
    if (theParMin < aParMax)
    {
      anIntersector->Perform(theL, theParMin, aParMax);
      if (anIntersector->IsDone())
      {
        int n = anIntersector->NbPnt();
        for (int j = 1; j <= n; ++j)
        {
          double w = anIntersector->WParameter(j);
          if (w < aParMax)
          {
            aParMax     = w;
            anIndexFace = ii - 1;
          }
        }
      }
      else
      {
        myIsDone = false;
        return;
      }
    }
  }
  if (!myPtrNums.IsEmpty() && anIndexFace >= 0)
  {
    myPtrNums.ChangeValue(anIndexFace) += 1;
    int im1;
    for (im1 = anIndexFace - 1, i = anIndexFace;
         i >= 1 && myPtrNums.Value(i) > myPtrNums.Value(im1);
         --i, --im1)
    {
      std::swap(myPtrIndexNums.ChangeValue(i), myPtrIndexNums.ChangeValue(im1));
      std::swap(myPtrNums.ChangeValue(i), myPtrNums.ChangeValue(im1));
    }
  }
  SortResult();
}

void IntCurvesFace_ShapeIntersector::Perform(const occ::handle<Adaptor3d_Curve>& theHCurve,
                                             const double                        theParMin,
                                             const double                        theParMax)
{
  myIsDone = false;
  for (int i = 1; i <= myNbFaces; ++i)
  {
    occ::handle<IntCurvesFace_Intersector> anIntersector = myIntersector.ChangeValue(i);
    anIntersector->Perform(theHCurve, theParMin, theParMax);
  }
  SortResult();
}

void IntCurvesFace_ShapeIntersector::SortResult()
{
  myIsDone   = true;
  int aNbPnt = 0;
  myIndexPt.Clear();
  myIndexFace.Clear();
  myIndexIntPnt.Clear();
  myIndexPar.Clear();

  for (int f = 1; f <= myNbFaces; ++f)
  {
    occ::handle<IntCurvesFace_Intersector> anIntersector = myIntersector.ChangeValue(f);
    if (anIntersector->IsDone())
    {
      int n = anIntersector->NbPnt();
      for (int j = 1; j <= n; ++j)
      {
        myIndexPt.Append(++aNbPnt);
        myIndexFace.Append(f);
        myIndexIntPnt.Append(j);
        myIndexPar.Append(anIntersector->WParameter(j));
      }
    }
    else
    {
      myIsDone = false;
      return;
    }
  }

  bool isOK;
  do
  {
    isOK = true;
    for (int ind0 = 1; ind0 < aNbPnt; ind0++)
    {
      int ind   = myIndexPt(ind0);
      int indp1 = myIndexPt(ind0 + 1);
      if (myIndexPar(ind) > myIndexPar(indp1))
      {
        myIndexPt(ind0)     = indp1;
        myIndexPt(ind0 + 1) = ind;
        isOK                = false;
      }
    }
  } while (!isOK);
}

IntCurvesFace_ShapeIntersector::~IntCurvesFace_ShapeIntersector() = default;
