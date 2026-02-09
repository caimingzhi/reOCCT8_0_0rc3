#include <BRep_TEdge.hpp>
#include <BRepLib.hpp>
#include <BRepPrimAPI_MakeRevol.hpp>
#include <BRepSweep_Revol.hpp>
#include <gp_Ax1.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepTools_ReShape.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_SurfaceOfRevolution.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Extrema_ExtCC.hpp>
#include <Extrema_POnCurv.hpp>
#include <Geom_Line.hpp>
#include <Adaptor3d_Curve.hpp>

static const TopoDS_Shape& check(const TopoDS_Shape& S)
{
  BRepLib::BuildCurves3d(S);
  return S;
}

BRepPrimAPI_MakeRevol::BRepPrimAPI_MakeRevol(const TopoDS_Shape& S,
                                             const gp_Ax1&       A,
                                             const double        D,
                                             const bool          Copy)
    : myRevol(check(S), A, D, Copy),
      myIsBuild(false)

{
  if (!CheckValidity(check(S), A))
  {
    myShape.Nullify();
    myIsBuild = true;
  }
  else
  {
    Build();
  }
}

BRepPrimAPI_MakeRevol::BRepPrimAPI_MakeRevol(const TopoDS_Shape& S,
                                             const gp_Ax1&       A,
                                             const bool          Copy)
    :

      myRevol(check(S), A, 2. * M_PI, Copy),
      myIsBuild(false)
{

  if (!CheckValidity(check(S), A))
  {
    myShape.Nullify();
    myIsBuild = true;
  }
  else
  {
    Build();
  }
}

const BRepSweep_Revol& BRepPrimAPI_MakeRevol::Revol() const
{
  return myRevol;
}

void BRepPrimAPI_MakeRevol::Build(const Message_ProgressRange&)
{
  if (myIsBuild)
  {
    return;
  }
  myShape = myRevol.Shape();
  BRepLib::UpdateInnerTolerances(myShape);

  Done();
  myIsBuild = true;

  myHist.Nullify();
  myDegenerated.Clear();
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> aDegE;
  BRep_Builder                                                                               aBB;

  TopExp_Explorer anExp(myShape, TopAbs_EDGE);

  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Shape&     anEdge = anExp.Current();
    occ::handle<BRep_TEdge> aTEdge = occ::down_cast<BRep_TEdge>(anEdge.TShape());

    if (aTEdge->Degenerated())
    {
      NCollection_List<TopoDS_Shape>* anL = aDegE.ChangeSeek(anEdge);
      if (anL)
      {

        TopoDS_Shape aCopyE = anEdge.EmptyCopied();
        aCopyE.Orientation(TopAbs_FORWARD);
        TopoDS_Iterator aVIter(anEdge.Oriented(TopAbs_FORWARD), false);
        for (; aVIter.More(); aVIter.Next())
        {
          aBB.Add(aCopyE, aVIter.Value());
        }
        aCopyE.Orientation(anEdge.Orientation());
        anL->Append(aCopyE);
        myDegenerated.Append(aCopyE);
      }
      else
      {
        anL = aDegE.Bound(anEdge, NCollection_List<TopoDS_Shape>());
        anL->Append(anEdge);
        myDegenerated.Append(anEdge);
      }
    }
  }
  if (!myDegenerated.IsEmpty())
  {
    BRepTools_ReShape aSubs;
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
         aDegF;
    bool isReplaced = false;
    anExp.Init(myShape, TopAbs_FACE);

    for (; anExp.More(); anExp.Next())
    {
      const TopoDS_Shape& aF = anExp.Current();
      TopExp_Explorer     anExpE(aF, TopAbs_EDGE);
      for (; anExpE.More(); anExpE.Next())
      {
        const TopoDS_Shape& anE = anExpE.Current();
        if (BRep_Tool::Degenerated(TopoDS::Edge(anE)))
        {
          NCollection_List<TopoDS_Shape>* anL = aDegF.ChangeSeek(aF);
          if (!anL)
          {
            anL = aDegF.Bound(aF, NCollection_List<TopoDS_Shape>());
          }
          anL->Append(anE);
        }
      }
    }

    BRepTools_ReShape aSubsF;
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator aFIter(aDegF);
    for (; aFIter.More(); aFIter.Next())
    {
      aSubs.Clear();
      isReplaced                                    = false;
      const TopoDS_Shape&                      aF   = aFIter.Key();
      const NCollection_List<TopoDS_Shape>&    aDEL = aFIter.ChangeValue();
      NCollection_List<TopoDS_Shape>::Iterator anEIter(aDEL);
      for (; anEIter.More(); anEIter.Next())
      {
        const TopoDS_Shape& anE = anEIter.Value();
        if (aDegE.IsBound(anE))
        {
          NCollection_List<TopoDS_Shape>&          aCEL = aDegE.ChangeFind(anE);
          NCollection_List<TopoDS_Shape>::Iterator anIt(aCEL);
          for (; anIt.More(); anIt.Next())
          {
            if (anIt.Value().IsEqual(anE))
            {

              aCEL.Remove(anIt);
              break;
            }
            if (anIt.Value().Orientation() == anE.Orientation())
            {

              isReplaced = true;
              aSubs.Replace(anE, anIt.Value());
              aCEL.Remove(anIt);
              break;
            }
          }
        }
      }
      if (isReplaced)
      {
        TopoDS_Shape aNF = aSubs.Apply(aF);
        aSubsF.Replace(aF, aNF);
        if (myHist.IsNull())
        {
          myHist = aSubs.History();
        }
        else
        {
          myHist->Merge(aSubs.History());
        }
        myShape = aSubsF.Apply(myShape);
        myHist->Merge(aSubsF.History());

        myHist->ReplaceModified(aF, aNF);
        aSubsF.Clear();
      }
    }
  }
}

static bool IsIntersect(const occ::handle<Adaptor3d_Curve>& theC, const gp_Ax1& theAxe)
{
  const gp_Lin anAxis(theAxe);

  if (theC->GetType() == GeomAbs_Circle)
  {
    gp_Circ       aCirc  = theC->Circle();
    const gp_Pnt& aCentr = aCirc.Location();
    double        anR2   = aCirc.Radius();
    anR2 -= Precision::Confusion();
    anR2 *= anR2;
    if (anAxis.SquareDistance(aCentr) > anR2)
    {
      return false;
    }
  }
  const occ::handle<Geom_Line> aL = new Geom_Line(anAxis);
  const GeomAdaptor_Curve      aLin(aL);
  const double                 aParTol = theC->Resolution(Precision::Confusion());
  const double aParF = theC->FirstParameter() + aParTol, aParL = theC->LastParameter() - aParTol;

  Extrema_ExtCC anExtr(*theC, aLin);
  anExtr.Perform();
  if (anExtr.IsDone() && anExtr.NbExt() > 0)
  {
    Extrema_POnCurv aP1, aP2;
    for (int i = 1; i <= anExtr.NbExt(); i++)
    {
      if (anExtr.SquareDistance(i) > Precision::SquareConfusion())
      {
        continue;
      }
      anExtr.Points(i, aP1, aP2);
      if ((aParF < aP1.Parameter()) && (aP1.Parameter() < aParL))
      {
        return true;
      }
    }
  }
  return false;
}

bool BRepPrimAPI_MakeRevol::CheckValidity(const TopoDS_Shape& theShape, const gp_Ax1& theA)
{
  TopExp_Explorer anExp(theShape, TopAbs_EDGE);
  bool            IsValid = true;
  for (; anExp.More(); anExp.Next())
  {
    const TopoDS_Edge& anE = TopoDS::Edge(anExp.Current());

    if (BRep_Tool::Degenerated(anE))
    {
      continue;
    }

    TopLoc_Location         L;
    double                  First, Last;
    occ::handle<Geom_Curve> C  = BRep_Tool::Curve(anE, L, First, Last);
    gp_Trsf                 Tr = L.Transformation();
    C                          = occ::down_cast<Geom_Curve>(C->Copy());
    C                          = new Geom_TrimmedCurve(C, First, Last);
    C->Transform(Tr);

    occ::handle<GeomAdaptor_Curve> HC = new GeomAdaptor_Curve();
    HC->Load(C, First, Last);

    int    Ratio = 1;
    double Dist;
    gp_Pnt PP;
    do
    {
      PP   = HC->Value(First + (Last - First) / Ratio);
      Dist = gp_Lin(theA).Distance(PP);
      Ratio++;
    } while (Dist < Precision::Confusion() && Ratio < 100);

    if (Ratio >= 100)
    {
      IsValid = true;
    }
    else
    {
      IsValid = !IsIntersect(HC, theA);
    }
    if (!IsValid)
    {
      break;
    }
  }

  return IsValid;
}

TopoDS_Shape BRepPrimAPI_MakeRevol::FirstShape()
{
  return myRevol.FirstShape();
}

TopoDS_Shape BRepPrimAPI_MakeRevol::LastShape()
{
  return myRevol.LastShape();
}

const NCollection_List<TopoDS_Shape>& BRepPrimAPI_MakeRevol::Generated(const TopoDS_Shape& S)
{
  myGenerated.Clear();

  if (!myRevol.IsUsed(S))
  {
    return myGenerated;
  }

  TopoDS_Shape aGS = myRevol.Shape(S);
  if (!aGS.IsNull())
  {
    if (BRepTools_History::IsSupportedType(aGS))
    {
      if (aGS.ShapeType() == TopAbs_EDGE)
      {
        bool isDeg = BRep_Tool::Degenerated(TopoDS::Edge(aGS));
        if (isDeg)
        {
          NCollection_List<TopoDS_Shape>::Iterator anIt(myDegenerated);
          for (; anIt.More(); anIt.Next())
          {
            if (aGS.IsSame(anIt.Value()))
            {
              myGenerated.Append(aGS);
              if (!myHist.IsNull())
              {
                NCollection_List<TopoDS_Shape>::Iterator anIt1(myHist->Modified(aGS));
                for (; anIt1.More(); anIt1.Next())
                {
                  myGenerated.Append(anIt1.Value());
                }
                return myGenerated;
              }
            }
          }
          return myGenerated;
        }
      }

      if (myHist.IsNull())
      {
        myGenerated.Append(aGS);
        return myGenerated;
      }

      if (myHist->Modified(aGS).IsEmpty())
      {
        myGenerated.Append(aGS);
        return myGenerated;
      }

      NCollection_List<TopoDS_Shape>::Iterator anIt(myHist->Modified(aGS));
      for (; anIt.More(); anIt.Next())
      {
        myGenerated.Append(anIt.Value());
      }
    }
  }
  return myGenerated;
}

bool BRepPrimAPI_MakeRevol::IsDeleted(const TopoDS_Shape& S)
{
  return !myRevol.IsUsed(S);
}

TopoDS_Shape BRepPrimAPI_MakeRevol::FirstShape(const TopoDS_Shape& theShape)
{
  return myRevol.FirstShape(theShape);
}

TopoDS_Shape BRepPrimAPI_MakeRevol::LastShape(const TopoDS_Shape& theShape)
{
  return myRevol.LastShape(theShape);
}

bool BRepPrimAPI_MakeRevol::HasDegenerated() const
{
  return (!myDegenerated.IsEmpty());
}

const NCollection_List<TopoDS_Shape>& BRepPrimAPI_MakeRevol::Degenerated() const
{
  return myDegenerated;
}
