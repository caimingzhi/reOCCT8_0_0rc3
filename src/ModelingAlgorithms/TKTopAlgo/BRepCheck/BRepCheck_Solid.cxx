#include <BRep_Tool.hpp>
#include <BRepCheck.hpp>
#include <BRepCheck_Status.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <BRepCheck_Solid.hpp>
#include <BRepClass3d_SolidClassifier.hpp>
#include <Geom_Curve.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Vector.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Builder.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepCheck_Solid, BRepCheck_Result)

class BRepCheck_HSC : public Standard_Transient
{
public:
  Standard_EXPORT BRepCheck_HSC() = default;

  Standard_EXPORT ~BRepCheck_HSC() override = default;

  Standard_EXPORT BRepClass3d_SolidClassifier& SolidClassifier() { return mySC; };

  DEFINE_STANDARD_RTTI_INLINE(BRepCheck_HSC, Standard_Transient);

protected:
  BRepClass3d_SolidClassifier mySC;
};

class BRepCheck_ToolSolid
{

public:
  DEFINE_STANDARD_ALLOC

  BRepCheck_ToolSolid()
  {
    myIsHole = false;
    myPntTol = Precision::Confusion();
    myPnt.SetCoord(-1., -1., -1.);
  };

  virtual ~BRepCheck_ToolSolid() = default;

  void SetSolid(const TopoDS_Solid& aZ) { mySolid = aZ; };

  const TopoDS_Solid& Solid() const { return mySolid; };

  bool IsHole() const { return myIsHole; };

  const gp_Pnt& InnerPoint() { return myPnt; }

  double CheckTol() const { return myPntTol; };

  bool IsOut(BRepCheck_ToolSolid& aOther)
  {
    bool         bFlag;
    TopAbs_State aState;

    BRepClass3d_SolidClassifier& aSC = myHSC->SolidClassifier();

    aSC.Perform(aOther.InnerPoint(), aOther.CheckTol());
    aState = aSC.State();
    bFlag  = (aState == TopAbs_OUT);

    return bFlag;
  };

  void Init()
  {
    double          aT, aT1, aT2, aPAR_T;
    TopExp_Explorer aExp;

    myHSC = new BRepCheck_HSC();

    BRepClass3d_SolidClassifier& aSC = myHSC->SolidClassifier();

    aSC.Load(mySolid);

    aSC.PerformInfinitePoint(::RealSmall());
    myIsHole = (aSC.State() == TopAbs_IN);

    aPAR_T = 0.43213918;
    aExp.Init(mySolid, TopAbs_EDGE);
    for (; aExp.More(); aExp.Next())
    {
      const TopoDS_Edge& aE = *((TopoDS_Edge*)&aExp.Current());
      if (!BRep_Tool::Degenerated(aE))
      {
        occ::handle<Geom_Curve> aC3D = BRep_Tool::Curve(aE, aT1, aT2);
        aT                           = (1. - aPAR_T) * aT1 + aPAR_T * aT2;
        myPnt                        = aC3D->Value(aT);
        myPntTol                     = BRep_Tool::Tolerance(aE);
        break;
      }
    }
  };

protected:
  bool                       myIsHole;
  gp_Pnt                     myPnt;
  double                     myPntTol;
  TopoDS_Solid               mySolid;
  occ::handle<BRepCheck_HSC> myHSC;
};

typedef NCollection_Vector<BRepCheck_ToolSolid> BRepCheck_VectorOfToolSolid;

BRepCheck_Solid::BRepCheck_Solid(const TopoDS_Solid& S)
{
  Init(S);
}

void BRepCheck_Solid::Blind()
{
  if (!myBlind)
  {

    myBlind = true;
  }
}

void BRepCheck_Solid::InContext(const TopoDS_Shape&) {}

void BRepCheck_Solid::Minimum()
{
  if (myMin)
  {
    return;
  }
  myMin = true;

  bool                                                   bFound, bIsHole, bFlag;
  int                                                    i, j, aNbVTS, aNbVTS1, iCntSh, iCntShInt;
  TopoDS_Solid                                           aZ;
  TopoDS_Iterator                                        aIt, aItF;
  TopoDS_Builder                                         aBB;
  TopExp_Explorer                                        aExp;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMSS;
  TopAbs_Orientation                                     aOr;
  BRepCheck_VectorOfToolSolid                            aVTS;

  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aNewList =
    new NCollection_Shared<NCollection_List<BRepCheck_Status>>();
  NCollection_List<BRepCheck_Status>& aLST = **myMap.Bound(myShape, aNewList);
  aLST.Append(BRepCheck_NoError);

  bFound = false;
  aExp.Init(myShape, TopAbs_FACE);
  for (; !bFound && aExp.More(); aExp.Next())
  {
    const TopoDS_Shape& aF = aExp.Current();
    if (!aMSS.Add(aF))
    {
      BRepCheck::Add(aLST, BRepCheck_InvalidImbricationOfShells);
      bFound = !bFound;
    }
  }

  iCntSh    = 0;
  iCntShInt = 0;
  aIt.Initialize(myShape);
  for (; aIt.More(); aIt.Next())
  {
    const TopoDS_Shape& aSx = aIt.Value();

    if (aSx.ShapeType() != TopAbs_SHELL)
    {
      aOr = aSx.Orientation();
      if (aOr != TopAbs_INTERNAL)
      {
        BRepCheck::Add(aLST, BRepCheck_BadOrientationOfSubshape);
      }
      continue;
    }

    const TopoDS_Shell& aSh = *((TopoDS_Shell*)&aSx);

    bFound = false;
    aItF.Initialize(aSh);
    for (; !bFound && aItF.More(); aItF.Next())
    {
      const TopoDS_Shape& aF = aItF.Value();
      aOr                    = aF.Orientation();
      if (aOr == TopAbs_INTERNAL)
      {
        bFound = !bFound;
      }
    }
    if (bFound)
    {
      ++iCntShInt;
      continue;
    }

    ++iCntSh;

    if (!BRep_Tool::IsClosed(aSh))
    {
      continue;
    }

    aBB.MakeSolid(aZ);
    aBB.Add(aZ, aSh);

    BRepCheck_ToolSolid aTS;

    aTS.SetSolid(aZ);
    aVTS.Append(aTS);
  }

  if (!iCntSh && iCntShInt)
  {

    BRepCheck::Add(aLST, BRepCheck_BadOrientationOfSubshape);
  }

  aNbVTS = aVTS.Size();
  if (aNbVTS < 2)
  {
    return;
  }

  aNbVTS1 = 0;
  for (i = 0; i < aNbVTS; ++i)
  {
    BRepCheck_ToolSolid& aTS = aVTS(i);

    aTS.Init();
    bIsHole = aTS.IsHole();
    if (!bIsHole)
    {
      ++aNbVTS1;
      if (aNbVTS1 > 1)
      {

        BRepCheck::Add(aLST, BRepCheck_EnclosedRegion);
        break;
      }
    }
  }

  bFound  = false;
  aNbVTS1 = aNbVTS - 1;
  for (i = 0; !bFound && i < aNbVTS1; ++i)
  {
    BRepCheck_ToolSolid& aTSi = aVTS(i);

    for (j = i + 1; !bFound && j < aNbVTS; ++j)
    {
      BRepCheck_ToolSolid& aTSj = aVTS(j);

      bFlag = aTSi.IsOut(aTSj);
      if (bFlag)
      {

        BRepCheck::Add(aLST, BRepCheck_SubshapeNotInShape);
        bFound = !bFound;
      }
    }
  }
}
