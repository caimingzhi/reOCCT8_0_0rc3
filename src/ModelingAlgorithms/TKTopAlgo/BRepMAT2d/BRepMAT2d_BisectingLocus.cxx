#include <Bisector_Bisec.hpp>
#include <BRepMAT2d_BisectingLocus.hpp>
#include <BRepMAT2d_Explorer.hpp>
#include <Geom2d_Geometry.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <MAT2d_BiInt.hpp>
#include <MAT2d_Circuit.hpp>
#include <MAT2d_CutCurve.hpp>
#include <MAT2d_Mat2d.hpp>
#include <NCollection_Sequence.hpp>
#include <MAT2d_Tool2d.hpp>
#include <MAT_BasicElt.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <MAT_Graph.hpp>
#include <MAT_ListOfBisector.hpp>
#include <MAT_Node.hpp>
#include <Precision.hpp>
#include <Geom2d_Curve.hpp>

static void CutSketch(
  NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& Figure,
  NCollection_DataMap<MAT2d_BiInt, int>&                                    NbSect);

BRepMAT2d_BisectingLocus::BRepMAT2d_BisectingLocus()
    : isDone(false),
      nbContours(0)
{
}

void BRepMAT2d_BisectingLocus::Compute(BRepMAT2d_Explorer&    anExplo,
                                       const int              IndexLine,
                                       const MAT_Side         aSide,
                                       const GeomAbs_JoinType aJoinType,
                                       const bool             IsOpenResult)
{
  MAT2d_Mat2d                     TheMAT(IsOpenResult);
  occ::handle<MAT_ListOfBisector> TheRoots = new MAT_ListOfBisector();
  NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>> Figure;
  int                                                                      i;

  nbSect.Clear();
  theGraph   = new MAT_Graph();
  nbContours = anExplo.NumberOfContours();
  if (nbContours == 0)
  {
    return;
  }

  for (i = 1; i <= anExplo.NumberOfContours(); i++)
  {
    NCollection_Sequence<occ::handle<Geom2d_Geometry>> Line;
    Figure.Append(Line);
    for (anExplo.Init(i); anExplo.More(); anExplo.Next())
    {
      Figure.ChangeValue(i).Append(anExplo.Value());
    }
  }

  CutSketch(Figure, nbSect);

  occ::handle<MAT2d_Circuit> ACircuit = new MAT2d_Circuit(aJoinType, IsOpenResult);

  ACircuit->Perform(Figure, anExplo.GetIsClosed(), IndexLine, (aSide == MAT_Left));

  theTool.Sense(aSide);
  theTool.SetJoinType(aJoinType);
  theTool.InitItems(ACircuit);

  if (IsOpenResult)
    TheMAT.CreateMatOpen(theTool);
  else
    TheMAT.CreateMat(theTool);

  isDone = TheMAT.IsDone();
  if (!isDone)
    return;

  for (TheMAT.Init(); TheMAT.More(); TheMAT.Next())
  {
    TheRoots->BackAdd(TheMAT.Bisector());
  }

  theGraph->Perform(TheMAT.SemiInfinite(),
                    TheRoots,
                    theTool.NumberOfItems(),
                    TheMAT.NumberOfBisectors());

  if (anExplo.NumberOfContours() > 1)
  {
    NCollection_DataMap<int, occ::handle<MAT_BasicElt>> NewMap;
    int                                                 IndexLast = 1;

    for (i = 1; i <= anExplo.NumberOfContours(); i++)
    {
      RenumerationAndFusion(i, theTool.Circuit()->LineLength(i), IndexLast, NewMap);
    }

    theGraph->ChangeBasicElts(NewMap);
    theGraph->CompactArcs();
    theGraph->CompactNodes();
  }
}

void BRepMAT2d_BisectingLocus::RenumerationAndFusion(
  const int                                            ILine,
  const int                                            LengthLine,
  int&                                                 IndexLast,
  NCollection_DataMap<int, occ::handle<MAT_BasicElt>>& NewMap)
{
  int  IndFirst;
  int  i, j;
  int  GeomIndexArc1, GeomIndexArc2, GeomIndexArc3, GeomIndexArc4;
  bool MergeArc1, MergeArc2;

  for (i = 1; i <= LengthLine; i++)
  {
    const NCollection_Sequence<int>& S = theTool.Circuit()->RefToEqui(ILine, i);

    IndFirst = S.Value(1);
    NewMap.Bind(IndexLast, theGraph->ChangeBasicElt(IndFirst));
    IndexLast++;

    for (j = 2; j <= S.Length(); j++)
    {
      theGraph->FusionOfBasicElts(IndFirst,
                                  S.Value(j),
                                  MergeArc1,
                                  GeomIndexArc1,
                                  GeomIndexArc2,
                                  MergeArc2,
                                  GeomIndexArc3,
                                  GeomIndexArc4);
      if (MergeArc1)
      {
        theTool.BisecFusion(GeomIndexArc1, GeomIndexArc2);
      }
      if (MergeArc2)
      {
        theTool.BisecFusion(GeomIndexArc3, GeomIndexArc4);
      }
    }
  }
}

bool BRepMAT2d_BisectingLocus::IsDone() const
{
  return isDone;
}

occ::handle<MAT_Graph> BRepMAT2d_BisectingLocus::Graph() const
{
  return theGraph;
}

int BRepMAT2d_BisectingLocus::NumberOfContours() const
{
  return nbContours;
}

int BRepMAT2d_BisectingLocus::NumberOfElts(const int IndLine) const
{
  return theTool.Circuit()->LineLength(IndLine);
}

int BRepMAT2d_BisectingLocus::NumberOfSections(const int IndLine, const int Index) const
{
  MAT2d_BiInt B(IndLine, Index);
  return nbSect(B);
}

occ::handle<MAT_BasicElt> BRepMAT2d_BisectingLocus::BasicElt(const int IndLine,
                                                             const int Index) const
{
  int i;
  int Ind = Index;

  for (i = 1; i < IndLine; i++)
  {
    Ind = Ind + theTool.Circuit()->LineLength(i);
  }
  return theGraph->BasicElt(Ind);
}

Bisector_Bisec BRepMAT2d_BisectingLocus::GeomBis(const occ::handle<MAT_Arc>& anArc,
                                                 bool&                       Reverse) const
{
  Reverse = false;

  occ::handle<Geom2d_Curve> Bis(theTool.GeomBis(anArc->GeomIndex()).Value());

  if (Bis->FirstParameter() <= -Precision::Infinite())
  {
    Reverse = true;
  }
  else if (Bis->LastParameter() < Precision::Infinite())
  {
    gp_Pnt2d PF    = Bis->Value(Bis->FirstParameter());
    gp_Pnt2d PL    = Bis->Value(Bis->LastParameter());
    gp_Pnt2d PNode = GeomElt(anArc->FirstNode());
    if (PNode.SquareDistance(PF) > PNode.SquareDistance(PL))
      Reverse = true;
  }
  return theTool.GeomBis(anArc->GeomIndex());
}

occ::handle<Geom2d_Geometry> BRepMAT2d_BisectingLocus::GeomElt(
  const occ::handle<MAT_BasicElt>& aBasicElt) const
{
  return theTool.GeomElt(aBasicElt->GeomIndex());
}

gp_Pnt2d BRepMAT2d_BisectingLocus::GeomElt(const occ::handle<MAT_Node>& aNode) const
{
  return theTool.GeomPnt(aNode->GeomIndex());
}

static void CutSketch(
  NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Geometry>>>& Figure,
  NCollection_DataMap<MAT2d_BiInt, int>&                                    NbSect)
{
  MAT2d_CutCurve Cuter;
  int            i, j, k, ico;
  int            ICurveInit;
  int            NbSection;

  for (i = 1; i <= Figure.Length(); i++)
  {
    NCollection_Sequence<occ::handle<Geom2d_Geometry>>& Contour = Figure.ChangeValue(i);
    ICurveInit                                                  = 0;

    for (j = 1; j <= Contour.Length(); j++)
    {
      ICurveInit++;
      Cuter.Perform(occ::down_cast<Geom2d_Curve>(Contour.ChangeValue(j)));
      NbSection = 1;
      if (!Cuter.UnModified())
      {
        ico       = j;
        NbSection = Cuter.NbCurves();
        for (k = 1; k <= NbSection; k++)
        {
          Contour.InsertAfter(j, Cuter.Value(k));
          j++;
        }
        Contour.Remove(ico);
        j--;
      }
      MAT2d_BiInt B(i, ICurveInit);
      NbSect.Bind(B, NbSection);
    }
  }
}
