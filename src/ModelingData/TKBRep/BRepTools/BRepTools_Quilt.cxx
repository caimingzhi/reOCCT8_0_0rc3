#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools_Quilt.hpp>
#include <Geom2d_Curve.hpp>
#include <Standard_NoSuchObject.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>

BRepTools_Quilt::BRepTools_Quilt()
    : hasCopy(false)
{
}

static bool NeedCopied(
  const TopoDS_Shape&                                                                    theShape,
  const NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& myBounds)
{

  bool            IsCopied = false;
  TopoDS_Iterator itv(theShape);
  for (; itv.More(); itv.Next())
  {
    if (myBounds.Contains(itv.Value()))
    {
      IsCopied = true;
      break;
    }
  }
  return IsCopied;
}

static void CopyShape(
  const TopoDS_Edge&                                                               E,
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& myBounds)
{
  TopoDS_Edge NE = E;
  NE.EmptyCopy();
  NE.Orientation(TopAbs_FORWARD);
  BRep_Builder B;

  TopoDS_Iterator itv;
  itv.Initialize(E, false);
  for (; itv.More(); itv.Next())
  {
    const TopoDS_Shape& V = itv.Value();
    if (myBounds.Contains(V))
    {
      B.Add(NE, myBounds.FindFromKey(V).Oriented(V.Orientation()));
    }
    else
    {
      B.Add(NE, V);
    }
  }

  double f, l;
  BRep_Tool::Range(E, f, l);
  B.Range(NE, f, l);
  myBounds.Add(E, NE.Oriented(TopAbs_FORWARD));
}

void BRepTools_Quilt::Add(const TopoDS_Shape& S)
{

  if (myBounds.Contains(S))
  {
    return;
  }

  BRep_Builder B;
  for (TopExp_Explorer wex(S, TopAbs_WIRE, TopAbs_FACE); wex.More(); wex.Next())
  {
    myBounds.Add(wex.Current(), wex.Current());
  }

  for (TopExp_Explorer eex(S, TopAbs_EDGE, TopAbs_WIRE); eex.More(); eex.Next())
  {
    myBounds.Add(eex.Current(), eex.Current());
  }

  for (TopExp_Explorer vex(S, TopAbs_VERTEX, TopAbs_EDGE); vex.More(); vex.Next())
  {
    myBounds.Add(vex.Current(), vex.Current());
  }

  for (TopExp_Explorer fex(S, TopAbs_FACE); fex.More(); fex.Next())
  {

    bool               copyFace = false;
    const TopoDS_Face& F        = TopoDS::Face(fex.Current());

    if (hasCopy)
    {

      for (TopExp_Explorer fed(F, TopAbs_EDGE); fed.More(); fed.Next())
      {

        if (myBounds.Contains(fed.Current()))
        {
          copyFace = true;
        }
        else
        {

          bool copyEdge = NeedCopied(fed.Current(), myBounds);

          const TopoDS_Edge& E = TopoDS::Edge(fed.Current());

          if (copyEdge)
          {

            copyFace = true;
            CopyShape(E, myBounds);
          }
        }
      }
    }

    TopoDS_Face NF = F;

    if (copyFace)
    {

      NF.EmptyCopy();
      NF.Orientation(TopAbs_FORWARD);

      for (TopoDS_Iterator itw(F, false); itw.More(); itw.Next())
      {
        const TopoDS_Wire& W = TopoDS::Wire(itw.Value());

        TopoDS_Wire NW;
        B.MakeWire(NW);
        TopoDS_Iterator ite(W, false);
        double          UFirst, ULast;

        for (; ite.More(); ite.Next())
        {
          const TopoDS_Edge& E  = TopoDS::Edge(ite.Value());
          TopAbs_Orientation OE = E.Orientation();
          if (myBounds.Contains(E))
          {
            const TopoDS_Edge& NE = TopoDS::Edge(myBounds.FindFromKey(E));

            if (NE.Orientation() == TopAbs_FORWARD)
            {
              B.UpdateEdge(NE,
                           BRep_Tool::CurveOnSurface(E, F, UFirst, ULast),
                           F,
                           BRep_Tool::Tolerance(E));
            }
            else
            {

              OE                            = TopAbs::Reverse(OE);
              occ::handle<Geom2d_Curve> CE  = BRep_Tool::CurveOnSurface(E, F, UFirst, ULast);
              occ::handle<Geom2d_Curve> NCE = CE->Reversed();
              B.UpdateEdge(NE, NCE, F, BRep_Tool::Tolerance(E));
              double tmp = UFirst;
              UFirst     = CE->ReversedParameter(ULast);
              ULast      = CE->ReversedParameter(tmp);
            }

            B.Range(NE, F, UFirst, ULast);

            B.Add(NW, NE.Oriented(OE));
          }
          else
          {
            B.Add(NW, E);
          }
        }
        NW.Orientation(W.Orientation());
        B.Add(NF, NW);
      }
      NF.Orientation(F.Orientation());
    }

    myBounds.Add(F, NF);
  }
}

void BRepTools_Quilt::Bind(const TopoDS_Vertex& Vold, const TopoDS_Vertex& Vnew)
{
  if (!myBounds.Contains(Vold))
  {
    myBounds.Add(Vold, Vnew);
  }
}

void BRepTools_Quilt::Bind(const TopoDS_Edge& Eold, const TopoDS_Edge& Enew)
{
  if (!myBounds.Contains(Eold))
  {
    TopoDS_Edge ENew = Enew;
    if (IsCopied(Enew))
    {
      ENew = TopoDS::Edge(Copy(Enew));
      ENew.Orientation(Enew.Orientation());
    }

    if (Eold.Orientation() != ENew.Orientation())
    {
      myBounds.Add(Eold.Oriented(TopAbs_FORWARD), ENew.Oriented(TopAbs_REVERSED));
    }
    else
    {
      myBounds.Add(Eold.Oriented(TopAbs_FORWARD), ENew.Oriented(TopAbs_FORWARD));
    }

    TopoDS_Iterator itold(Eold);
    while (itold.More())
    {
      if (!myBounds.Contains(itold.Value()))
      {

        TopAbs_Orientation anOrien = itold.Value().Orientation();
        TopoDS_Iterator    itnew(ENew);
        while (itnew.More())
        {
          if (itnew.Value().Orientation() == anOrien)
          {
            TopoDS_Vertex VNew = TopoDS::Vertex(itnew.Value());
            if (IsCopied(VNew))
            {

              VNew = TopoDS::Vertex(Copy(VNew));
            }
            myBounds.Add(itold.Value(), VNew);
            break;
          }
          itnew.Next();
        }
      }
      itold.Next();
    }
    hasCopy = true;
  }
}

bool BRepTools_Quilt::IsCopied(const TopoDS_Shape& S) const
{
  if (myBounds.Contains(S))
  {
    return !S.IsSame(myBounds.FindFromKey(S));
  }
  else
    return false;
}

const TopoDS_Shape& BRepTools_Quilt::Copy(const TopoDS_Shape& S) const
{
  Standard_NoSuchObject_Raise_if(!IsCopied(S), "BRepTools_Quilt::Copy");
  return myBounds.FindFromKey(S);
}

TopoDS_Shape BRepTools_Quilt::Shells() const
{

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> M, MF;
  BRep_Builder                                                             B;
  TopoDS_Compound                                                          result;

  B.MakeCompound(result);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> MapOtherShape;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> EdgesFaces;

  for (int ii = 1; ii <= myBounds.Extent(); ii++)
  {
    const TopoDS_Shape& Shape = myBounds.FindFromIndex(ii);
    if (Shape.ShapeType() == TopAbs_FACE)
    {
      for (TopExp_Explorer aExpEdg(Shape, TopAbs_EDGE); aExpEdg.More(); aExpEdg.Next())
        EdgesFaces.Add(aExpEdg.Current());

      TopoDS_Shell       SH;
      TopAbs_Orientation NewO;

      TopExp_Explorer itf1(Shape, TopAbs_EDGE);
      for (; itf1.More(); itf1.Next())
      {
        const TopoDS_Shape& E = itf1.Current();
        if (M.IsBound(E))
        {
          SH = TopoDS::Shell(M(E));
          if (SH.Orientation() == E.Orientation())
            NewO = TopAbs::Reverse(Shape.Orientation());
          else
            NewO = Shape.Orientation();

          MF.Bind(Shape, SH.Oriented(NewO));
          break;
        }
      }

      if (SH.IsNull())
      {

        B.MakeShell(SH);
        SH.Closed(true);
        B.Add(result, SH);
        MF.Bind(Shape, SH.Oriented(Shape.Orientation()));
      }

      SH.Free(true);

      TopoDS_Shape arefShape = SH.Oriented(TopAbs_FORWARD);
      B.Add(arefShape, Shape.Oriented(MF(Shape).Orientation()));

      TopExp_Explorer itf(Shape.Oriented(TopAbs_FORWARD), TopAbs_EDGE);

      for (; itf.More(); itf.Next())
      {
        const TopoDS_Edge& E = TopoDS::Edge(itf.Current());

        if (M.IsBound(E))
        {
          const TopoDS_Shape oldShell = M(E);
          if (!oldShell.IsSame(SH))
          {

            TopAbs_Orientation anOrien = E.Orientation();
            if (MF(Shape).Orientation() == TopAbs_REVERSED)
              anOrien = TopAbs::Reverse(anOrien);

            bool Rev = (anOrien == oldShell.Orientation());

            for (TopoDS_Iterator its(oldShell); its.More(); its.Next())
            {
              const TopoDS_Face  Fo = TopoDS::Face(its.Value());
              TopAbs_Orientation NewOFo;

              if (Rev)
                NewOFo = TopAbs::Reverse(MF(Fo).Orientation());
              else
                NewOFo = MF(Fo).Orientation();

              MF.Bind(Fo, SH.Oriented(NewOFo));

              TopoDS_Shape arefShapeFo = SH.Oriented(TopAbs_FORWARD);
              B.Add(arefShapeFo, Fo.Oriented(NewOFo));
            }

            TopExp_Explorer aexp(SH, TopAbs_EDGE);
            for (; aexp.More(); aexp.Next())
            {

              if (!M.IsBound(aexp.Current()))
                continue;
              const TopoDS_Shape& ae = aexp.Current();
              TopoDS_Shape        as = M.Find(ae);
              if (as.IsSame(oldShell))
              {

                if (Rev)
                  NewO = TopAbs::Reverse(as.Orientation());
                else
                  NewO = as.Orientation();

                M.Bind(ae, SH.Oriented(NewO));
              }
            }

            B.Remove(result, oldShell.Oriented(TopAbs_FORWARD));
          }

          TopAbs_Orientation anOrien = E.Orientation();
          if (MF(Shape).Orientation() == TopAbs_REVERSED)
            anOrien = TopAbs::Reverse(anOrien);

          if (M(E).Orientation() == anOrien)
            SH.Orientable(false);

          M.UnBind(E);
        }
        else
        {
          NewO = E.Orientation();
          if (MF(Shape).Orientation() == TopAbs_REVERSED)
            NewO = TopAbs::Reverse(NewO);
          if (!E.IsNull())
            M.Bind(E, SH.Oriented(NewO));
          else
            continue;
        }
      }

      SH.Free(false);
    }
    else
      MapOtherShape.Add(Shape);
  }

  for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator it(M);
       it.More();
       it.Next())
  {
    TopoDS_Shape S = it.Value();
    S.Closed(false);
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itother(MapOtherShape);
  for (; itother.More(); itother.Next())
  {
    if (!EdgesFaces.Contains(itother.Key()) && myBounds.Contains(itother.Key()))
    {
      TopoDS_Shape aSh = myBounds.FindFromKey(itother.Key());
      B.Add(result, aSh);
    }
  }
  return result;
}
