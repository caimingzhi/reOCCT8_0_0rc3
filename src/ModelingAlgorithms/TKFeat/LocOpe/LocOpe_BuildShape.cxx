#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepClass3d_SolidClassifier.hpp>
#include <gp_Pnt.hpp>
#include <LocOpe_BuildShape.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <TopAbs.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>

static void Add(const int,
                NCollection_Map<int>&,
                NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&,
                const NCollection_IndexedDataMap<TopoDS_Shape,
                                                 NCollection_List<TopoDS_Shape>,
                                                 TopTools_ShapeMapHasher>&);

static void Propagate(const TopoDS_Shape&,
                      TopoDS_Shape&,
                      const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&,
                      NCollection_Map<int>&);

static bool IsInside(const TopoDS_Shape&, const TopoDS_Shape&);

void LocOpe_BuildShape::Perform(const NCollection_List<TopoDS_Shape>& L)
{
  int i;
  int j;
  int k;
  myRes.Nullify();

  TopoDS_Compound C;
  BRep_Builder    B;
  B.MakeCompound(C);

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mapF;
  NCollection_List<TopoDS_Shape>::Iterator                      itl;

  for (itl.Initialize(L); itl.More(); itl.Next())
  {
    if (itl.Value().ShapeType() == TopAbs_FACE && !mapF.Contains(itl.Value()))
    {
      mapF.Add(itl.Value());
      B.Add(C, itl.Value());
    }
  }

  if (mapF.Extent() == 0)
  {
    return;
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    theMapEF;
  TopExp::MapShapesAndAncestors(C, TopAbs_EDGE, TopAbs_FACE, theMapEF);

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> mapSh;
  NCollection_Map<int> mapI, mapIf;
  int                  Nbedges = theMapEF.Extent();

  NCollection_List<TopoDS_Shape> lshell;
  NCollection_List<TopoDS_Shape> lresult;

  do
  {

    for (i = 1; i <= Nbedges; i++)
    {
      if (!mapI.Contains(i))
      {
        break;
      }
    }
    if (i <= Nbedges)
    {
      mapF.Clear();
      mapIf.Clear();
      Add(i, mapI, mapF, theMapEF);
      bool               Manifold = true;
      TopoDS_Shape       FaceRef;
      TopAbs_Orientation orient;

      for (j = 1; j <= mapF.Extent(); j++)
      {
        orient = mapF(j).Orientation();
        if (orient == TopAbs_INTERNAL || orient == TopAbs_EXTERNAL)
        {
          Manifold = false;
        }
        else if (FaceRef.IsNull())
        {
          FaceRef = mapF(j);
        }
        mapIf.Add(j);
      }

      TopoDS_Shell newSh;
      B.MakeShell(newSh);
      if (!Manifold && FaceRef.IsNull())
      {

        for (j = 1; j <= mapF.Extent(); j++)
        {
          B.Add(newSh, mapF(j));
        }
      }
      else
      {

        if (!Manifold)
        {
          for (j = 1; j <= mapF.Extent(); j++)
          {
            if (mapF(j).Orientation() == TopAbs_INTERNAL
                || mapF(j).Orientation() == TopAbs_EXTERNAL)
            {
              B.Add(newSh, mapF(j));
              mapIf.Remove(j);
            }
          }
        }

        B.Add(newSh, FaceRef);
        Propagate(FaceRef, newSh, mapF, mapIf);
      }
      newSh.Closed(BRep_Tool::IsClosed(newSh));
      if (!Manifold)
      {
        lshell.Append(newSh.Oriented(TopAbs_INTERNAL));
      }
      else
      {
        NCollection_IndexedDataMap<TopoDS_Shape,
                                   NCollection_List<TopoDS_Shape>,
                                   TopTools_ShapeMapHasher>
          theMapEFbis;
        TopExp::MapShapesAndAncestors(newSh, TopAbs_EDGE, TopAbs_FACE, theMapEFbis);
        for (k = 1; k <= theMapEFbis.Extent(); k++)
        {
          const TopoDS_Edge& Ed    = TopoDS::Edge(theMapEFbis.FindKey(k));
          TopAbs_Orientation OriEd = Ed.Orientation();
          if (OriEd != TopAbs_INTERNAL && OriEd != TopAbs_EXTERNAL)
          {
            int Nbfac = theMapEFbis(k).Extent();
            if (Nbfac > 2)
            {
              break;
            }
            else if (Nbfac == 1)
            {
              if (!BRep_Tool::Degenerated(Ed))
              {
                break;
              }
            }
          }
        }
        if (k > theMapEFbis.Extent())
        {
          TopoDS_Solid newSo;
          B.MakeSolid(newSo);
          B.Add(newSo, newSh);
          BRepClass3d_SolidClassifier Class(newSo);
          Class.PerformInfinitePoint(Precision::Confusion());
          if (Class.State() == TopAbs_IN)
          {
            lresult.Append(newSh.Oriented(TopAbs_REVERSED));
          }
          else
          {
            lresult.Append(newSh);
          }
        }
        else
        {
          lshell.Append(newSh.Oriented(TopAbs_INTERNAL));
        }
      }
    }
  } while (mapI.Extent() < Nbedges);

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> imbSh;
  NCollection_List<TopoDS_Shape> LIntern;

  for (itl.Initialize(lresult); itl.More(); itl.Next())
  {
    const TopoDS_Shape& sh = itl.Value();
    TopoDS_Solid        tempo;
    B.MakeSolid(tempo);
    B.Add(tempo, sh);

    NCollection_List<TopoDS_Shape> thelist;
    imbSh.Bind(sh, thelist);
    NCollection_List<TopoDS_Shape>::Iterator itl2;
    for (itl2.Initialize(lresult);

         itl2.More();
         itl2.Next())
    {
      const TopoDS_Shape& sh2 = itl2.Value();
      if (!sh2.IsSame(sh))
      {
        if (IsInside(sh2, tempo))
        {
          LIntern.Append(sh2);
          imbSh(sh).Append(sh2);
        }
      }
    }
  }

  for (itl.Initialize(LIntern); itl.More(); itl.Next())
  {
    const TopoDS_Shape& sh = itl.Value();
    if (imbSh.IsBound(sh))
    {
      imbSh.UnBind(sh);
    }
  }

  NCollection_List<TopoDS_Shape> lsolid;
  do
  {

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator itdm(imbSh);
    for (; itdm.More(); itdm.Next())
    {
      if (itdm.Value().Extent() != 0)
      {
        break;
      }
    }
    if (itdm.More())
    {
      TopoDS_Solid newSo;
      B.MakeSolid(newSo);
      B.Add(newSo, itdm.Key());
      for (itl.Initialize(itdm.Value()); itl.More(); itl.Next())
      {
        B.Add(newSo, itl.Value().Reversed());
      }
      lsolid.Append(newSo);
      imbSh.UnBind(itdm.Key());
    }
    else
    {
      for (itdm.Initialize(imbSh); itdm.More(); itdm.Next())
      {
        TopoDS_Solid newSo;
        B.MakeSolid(newSo);
        B.Add(newSo, itdm.Key());
        lsolid.Append(newSo);
      }
      imbSh.Clear();
    }
  } while (imbSh.Extent() != 0);

  int nbsol = lsolid.Extent();
  int nbshl = lshell.Extent();

  if (nbsol == 1 && nbshl == 0)
  {
    myRes = lsolid.First();
  }
  else if (nbsol == 0 && nbshl == 1)
  {
    myRes = lshell.First();
  }
  else
  {
    B.MakeCompound(TopoDS::Compound(myRes));
    for (itl.Initialize(lsolid); itl.More(); itl.Next())
    {
      B.Add(myRes, itl.Value());
    }
    for (itl.Initialize(lshell); itl.More(); itl.Next())
    {
      B.Add(myRes, itl.Value());
    }
  }
}

static void Add(const int                                                      ind,
                NCollection_Map<int>&                                          mapI,
                NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& mapF,
                const NCollection_IndexedDataMap<TopoDS_Shape,
                                                 NCollection_List<TopoDS_Shape>,
                                                 TopTools_ShapeMapHasher>&     mapEF)

{
  if (!mapI.Add(ind))
  {
    throw Standard_ConstructionError();
  }

  NCollection_List<TopoDS_Shape>::Iterator itl(mapEF(ind));
  for (; itl.More(); itl.Next())
  {
    if (!mapF.Contains(itl.Value()))
    {
      mapF.Add(itl.Value());
      TopExp_Explorer exp;
      for (exp.Init(itl.Value(), TopAbs_EDGE);

           exp.More();
           exp.Next())
      {
        const TopoDS_Shape& edg    = exp.Current();
        int                 indedg = mapEF.FindIndex(edg);
        if (indedg == 0)
        {
          throw Standard_ConstructionError();
        }
        if (!mapI.Contains(indedg))
        {
          Add(indedg, mapI, mapF, mapEF);
        }
      }
    }
  }
}

static void Propagate(const TopoDS_Shape&                                                  F,
                      TopoDS_Shape&                                                        Sh,
                      const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& mapF,
                      NCollection_Map<int>&                                                mapIf)
{
  BRep_Builder B;
  int          indf = mapF.FindIndex(F);
  if (!mapIf.Contains(indf))
  {
    return;
  }
  mapIf.Remove(indf);
  if (mapIf.Extent() == 0)
  {
    return;
  }

  TopExp_Explorer exp;
  for (exp.Init(F, TopAbs_EDGE); exp.More(); exp.Next())
  {

    const TopoDS_Shape& edg = exp.Current();

    TopAbs_Orientation ored1 = edg.Orientation(), ored2 = TopAbs_FORWARD;

    if (ored1 == TopAbs_INTERNAL || ored1 == TopAbs_EXTERNAL)
    {
      continue;
    }

    NCollection_Map<int>::Iterator itm(mapIf);
    for (; itm.More(); itm.Next())
    {
      const TopoDS_Shape& newF = mapF(itm.Key());

      TopExp_Explorer exp2(newF, TopAbs_EDGE);
      for (; exp2.More(); exp2.Next())
      {
        if (exp2.Current().IsSame(edg))
        {
          break;
        }
      }
      if (exp2.More())
      {
        ored2 = exp2.Current().Orientation();
        break;
      }
    }
    if (itm.More())
    {
      TopoDS_Shape FtoAdd = mapF(itm.Key());
      bool         added  = false;
      if (ored2 == ored1)
      {
        FtoAdd.Reverse();
        B.Add(Sh, FtoAdd);
        added = true;
      }
      else if (ored2 == TopAbs::Reverse(ored1))
      {
        B.Add(Sh, FtoAdd);
        added = true;
      }
      if (added)
      {
        Propagate(FtoAdd, Sh, mapF, mapIf);
      }
    }
  }
}

static bool IsInside(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  BRepClass3d_SolidClassifier Class(S2);
  TopExp_Explorer             exp;
  for (exp.Init(S1, TopAbs_VERTEX); exp.More(); exp.Next())
  {

    const TopoDS_Vertex& vtx    = TopoDS::Vertex(exp.Current());
    gp_Pnt               Pttest = BRep_Tool::Pnt(vtx);
    double               Tol    = BRep_Tool::Tolerance(vtx);
    Class.Perform(Pttest, Tol);
    if (Class.State() == TopAbs_IN)
    {
      return true;
    }
    else if (Class.State() == TopAbs_OUT)
    {
      return false;
    }
  }
#ifdef OCCT_DEBUG
  std::cout << "Classification impossible sur vertex " << std::endl;
#endif

  return true;
}
