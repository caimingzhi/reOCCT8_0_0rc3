#include <BRep_Builder.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <Contap_Contour.hpp>
#include <Extrema_ExtPC.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <HLRAlgo_Projector.hpp>
#include <HLRTopoBRep_DSFiller.hpp>
#include <HLRTopoBRep_OutLiner.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRTopoBRep_OutLiner, Standard_Transient)

HLRTopoBRep_OutLiner::HLRTopoBRep_OutLiner() = default;

HLRTopoBRep_OutLiner::HLRTopoBRep_OutLiner(const TopoDS_Shape& OriS)
    : myOriginalShape(OriS)
{
}

HLRTopoBRep_OutLiner::HLRTopoBRep_OutLiner(const TopoDS_Shape& OriS, const TopoDS_Shape& OutS)
    : myOriginalShape(OriS),
      myOutLinedShape(OutS)
{
}

void HLRTopoBRep_OutLiner::Fill(
  const HLRAlgo_Projector&                                                         P,
  NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST,
  const int                                                                        nbIso)
{
  if (!myOriginalShape.IsNull())
  {
    if (myOutLinedShape.IsNull())
    {
      gp_Vec  Vecz(0., 0., 1.);
      gp_Trsf Tr(P.Transformation());
      Tr.Invert();
      Vecz.Transform(Tr);
      Contap_Contour FO;
      if (P.Perspective())
      {
        gp_Pnt Eye;
        Eye.SetXYZ(P.Focus() * Vecz.XYZ());
        FO.Init(Eye);
      }
      else
      {
        gp_Dir DirZ(Vecz);
        FO.Init(DirZ);
      }
      HLRTopoBRep_DSFiller::Insert(myOriginalShape, FO, myDS, MST, nbIso);
      BuildShape(MST);
    }
  }
}

void HLRTopoBRep_OutLiner::ProcessFace(
  const TopoDS_Face&                                                               F,
  TopoDS_Shape&                                                                    S,
  NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST)
{
  BRep_Builder    B;
  TopExp_Explorer exE, exW;

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aVEMap;
  TopExp::MapShapesAndAncestors(F, TopAbs_VERTEX, TopAbs_EDGE, aVEMap);

  TopoDS_Shape NF;

  NF = F.EmptyCopied();

  for (exW.Init(F, TopAbs_WIRE); exW.More(); exW.Next())
  {
    TopoDS_Wire W;
    B.MakeWire(W);

    for (exE.Init(exW.Current(), TopAbs_EDGE); exE.More(); exE.Next())
    {
      TopoDS_Edge E = TopoDS::Edge(exE.Current());
      if (myDS.EdgeHasSplE(E))
      {

        NCollection_List<TopoDS_Shape>::Iterator itS;
        for (itS.Initialize(myDS.EdgeSplE(E)); itS.More(); itS.Next())
        {
          TopoDS_Edge newE = TopoDS::Edge(itS.Value());
          newE.Orientation(E.Orientation());
          myDS.AddOldS(newE, E);
          B.Add(W, newE);
        }
      }
      else
      {
        B.Add(W, E);
      }
    }
    B.Add(NF, W);
  }

  myDS.AddIntL(F);
  NCollection_List<TopoDS_Shape>& OutL = myDS.AddOutL(F);

  if (myDS.FaceHasIntL(F))
  {
    TopoDS_Wire W;

    NCollection_List<TopoDS_Shape>::Iterator itE;
    for (itE.Initialize(myDS.FaceIntL(F)); itE.More(); itE.Next())
    {
      TopoDS_Edge E = TopoDS::Edge(itE.Value());
      E.Orientation(TopAbs_INTERNAL);

      BRepAdaptor_Curve C(E);
      double            par = 0.34 * C.FirstParameter() + 0.66 * C.LastParameter();
      gp_Pnt            P   = C.Value(par);
      TopoDS_Vertex     V1, V2, aV1, aV2;
      TopExp::Vertices(E, V1, V2);

      bool SameEdge = false;
      if (!V1.IsNull() && aVEMap.Contains(V1))
      {
        const NCollection_List<TopoDS_Shape>&    aEList = aVEMap.FindFromKey(V1);
        NCollection_List<TopoDS_Shape>::Iterator it(aEList);
        for (; it.More(); it.Next())
        {
          const TopoDS_Edge& aE = TopoDS::Edge(it.Value());
          TopExp::Vertices(aE, aV1, aV2);

          if ((V1.IsSame(aV1) && V2.IsSame(aV2)) || (V1.IsSame(aV2) && V2.IsSame(aV1)))
          {
            BRepAdaptor_Curve aC(aE);
            if ((C.GetType() == GeomAbs_Line) && (aC.GetType() == GeomAbs_Line))
            {
              SameEdge = true;
              break;
            }
            else
            {

              Extrema_ExtPC anExt(P, aC);
              if (anExt.IsDone())
              {
                int aNe = anExt.NbExt();
                if (aNe > 0)
                {
                  double dist = RealLast();
                  int    ec;
                  for (ec = 1; ec <= aNe; ++ec)
                  {

                    dist = std::min(dist, anExt.SquareDistance(ec));
                  }

                  if (dist <= 1.e-14)
                  {
                    SameEdge = true;
                    break;
                  }
                }
              }
            }
          }
        }
      }

      if (SameEdge)
      {
        OutL.Append(E);
        continue;
      }

      if (myDS.EdgeHasSplE(E))
      {

        NCollection_List<TopoDS_Shape>::Iterator itS;
        for (itS.Initialize(myDS.EdgeSplE(E)); itS.More(); itS.Next())
        {
          TopoDS_Shape newE = itS.Value();
          newE.Orientation(TopAbs_INTERNAL);
          if (W.IsNull())
            B.MakeWire(W);
          myDS.AddOldS(newE, F);
          B.Add(W, newE);
        }
      }
      else
      {
        if (W.IsNull())
          B.MakeWire(W);
        myDS.AddOldS(E, F);
        B.Add(W, E);
      }
    }
    if (!W.IsNull())
      B.Add(NF, W);
  }

  if (myDS.FaceHasIsoL(F))
  {
    TopoDS_Wire W;

    NCollection_List<TopoDS_Shape>::Iterator itE;
    for (itE.Initialize(myDS.FaceIsoL(F)); itE.More(); itE.Next())
    {
      TopoDS_Edge E = TopoDS::Edge(itE.Value());
      E.Orientation(TopAbs_INTERNAL);
      if (myDS.EdgeHasSplE(E))
      {

        NCollection_List<TopoDS_Shape>::Iterator itS;
        for (itS.Initialize(myDS.EdgeSplE(E)); itS.More(); itS.Next())
        {
          TopoDS_Shape newE = itS.Value();
          newE.Orientation(TopAbs_INTERNAL);
          if (W.IsNull())
            B.MakeWire(W);
          myDS.AddOldS(newE, F);
          B.Add(W, newE);
        }
      }
      else
      {
        if (W.IsNull())
          B.MakeWire(W);
        myDS.AddOldS(E, F);
        B.Add(W, E);
      }
    }
    if (!W.IsNull())
      B.Add(NF, W);
  }
  myDS.AddOldS(NF, F);
  MST.Bind(NF, MST.ChangeFind(F));

  B.Add(S, NF);
}

void HLRTopoBRep_OutLiner::BuildShape(
  NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST)
{
  TopExp_Explorer exshell, exface, exedge;
  BRep_Builder    B;
  B.MakeCompound(TopoDS::Compound(myOutLinedShape));
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> ShapeMap;

  for (exshell.Init(myOriginalShape, TopAbs_SHELL); exshell.More(); exshell.Next())
  {
    TopoDS_Shell theShell;
    B.MakeShell(theShell);
    theShell.Closed(exshell.Current().Closed());

    for (exface.Init(exshell.Current(), TopAbs_FACE); exface.More(); exface.Next())
    {
      if (ShapeMap.Add(exface.Current()))
        ProcessFace(TopoDS::Face(exface.Current()), theShell, MST);
    }
    B.Add(myOutLinedShape, theShell);
  }

  for (exface.Init(myOriginalShape, TopAbs_FACE, TopAbs_SHELL); exface.More(); exface.Next())
  {
    if (ShapeMap.Add(exface.Current()))
      ProcessFace(TopoDS::Face(exface.Current()), myOutLinedShape, MST);
  }

  for (exedge.Init(myOriginalShape, TopAbs_EDGE, TopAbs_FACE); exedge.More(); exedge.Next())
    B.Add(myOutLinedShape, exedge.Current());
}
