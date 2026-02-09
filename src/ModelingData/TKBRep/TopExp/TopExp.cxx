#define No_Standard_NoMoreObject
#define No_Standard_NoSuchObject
#define No_Standard_TypeMismatch

#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

void TopExp::MapShapes(const TopoDS_Shape&                                            S,
                       const TopAbs_ShapeEnum                                         T,
                       NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& M)
{
  TopExp_Explorer Ex(S, T);
  while (Ex.More())
  {
    M.Add(Ex.Current());
    Ex.Next();
  }
}

void TopExp::MapShapes(const TopoDS_Shape&                                            S,
                       NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& M,
                       const bool                                                     cumOri,
                       const bool                                                     cumLoc)
{
  M.Add(S);
  TopoDS_Iterator It(S, cumOri, cumLoc);
  while (It.More())
  {
    MapShapes(It.Value(), M);
    It.Next();
  }
}

void TopExp::MapShapes(const TopoDS_Shape&                                     S,
                       NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& M,
                       const bool                                              cumOri,
                       const bool                                              cumLoc)
{
  M.Add(S);
  TopoDS_Iterator It(S, cumOri, cumLoc);
  for (; It.More(); It.Next())
    MapShapes(It.Value(), M);
}

void TopExp::MapShapesAndAncestors(
  const TopoDS_Shape&    S,
  const TopAbs_ShapeEnum TS,
  const TopAbs_ShapeEnum TA,
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    M)
{
  NCollection_List<TopoDS_Shape> empty;

  TopExp_Explorer exa(S, TA);
  while (exa.More())
  {

    const TopoDS_Shape& anc = exa.Current();
    TopExp_Explorer     exs(anc, TS);
    while (exs.More())
    {
      int index = M.FindIndex(exs.Current());
      if (index == 0)
        index = M.Add(exs.Current(), empty);
      M(index).Append(anc);
      exs.Next();
    }
    exa.Next();
  }

  TopExp_Explorer ex(S, TS, TA);
  while (ex.More())
  {
    int index = M.FindIndex(ex.Current());
    if (index == 0)
      index = M.Add(ex.Current(), empty);
    ex.Next();
  }
}

void TopExp::MapShapesAndUniqueAncestors(
  const TopoDS_Shape&    S,
  const TopAbs_ShapeEnum TS,
  const TopAbs_ShapeEnum TA,
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
             M,
  const bool useOrientation)
{
  NCollection_List<TopoDS_Shape> empty;

  TopExp_Explorer exa(S, TA);
  while (exa.More())
  {

    const TopoDS_Shape& anc = exa.Current();
    TopExp_Explorer     exs(anc, TS);
    while (exs.More())
    {
      int index = M.FindIndex(exs.Current());
      if (index == 0)
        index = M.Add(exs.Current(), empty);
      NCollection_List<TopoDS_Shape>& aList = M(index);

      NCollection_List<TopoDS_Shape>::Iterator it(aList);
      for (; it.More(); it.Next())
        if (useOrientation ? anc.IsEqual(it.Value()) : anc.IsSame(it.Value()))
          break;
      if (!it.More())
        aList.Append(anc);
      exs.Next();
    }
    exa.Next();
  }

  TopExp_Explorer ex(S, TS, TA);
  while (ex.More())
  {
    int index = M.FindIndex(ex.Current());
    if (index == 0)
      M.Add(ex.Current(), empty);
    ex.Next();
  }
}

TopoDS_Vertex TopExp::FirstVertex(const TopoDS_Edge& E, const bool CumOri)
{
  TopoDS_Iterator ite(E, CumOri);
  while (ite.More())
  {
    if (ite.Value().Orientation() == TopAbs_FORWARD)
      return TopoDS::Vertex(ite.Value());
    ite.Next();
  }
  return TopoDS_Vertex();
}

TopoDS_Vertex TopExp::LastVertex(const TopoDS_Edge& E, const bool CumOri)
{
  TopoDS_Iterator ite(E, CumOri);
  while (ite.More())
  {
    if (ite.Value().Orientation() == TopAbs_REVERSED)
      return TopoDS::Vertex(ite.Value());
    ite.Next();
  }
  return TopoDS_Vertex();
}

void TopExp::Vertices(const TopoDS_Edge& E,
                      TopoDS_Vertex&     Vfirst,
                      TopoDS_Vertex&     Vlast,
                      const bool         CumOri)
{

  bool isFirstDefined = false;
  bool isLastDefined  = false;

  TopoDS_Iterator ite(E, CumOri);
  while (ite.More())
  {
    const TopoDS_Shape& aV = ite.Value();
    if (aV.Orientation() == TopAbs_FORWARD)
    {
      Vfirst         = TopoDS::Vertex(aV);
      isFirstDefined = true;
    }
    else if (aV.Orientation() == TopAbs_REVERSED)
    {
      Vlast         = TopoDS::Vertex(aV);
      isLastDefined = true;
    }
    ite.Next();
  }

  if (!isFirstDefined)
    Vfirst.Nullify();

  if (!isLastDefined)
    Vlast.Nullify();
}

void TopExp::Vertices(const TopoDS_Wire& W, TopoDS_Vertex& Vfirst, TopoDS_Vertex& Vlast)
{
  Vfirst = Vlast = TopoDS_Vertex();

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> vmap;
  TopoDS_Iterator                                        it(W);
  TopoDS_Vertex                                          V1, V2;

  while (it.More())
  {
    const TopoDS_Edge& E = TopoDS::Edge(it.Value());
    if (E.Orientation() == TopAbs_REVERSED)
      TopExp::Vertices(E, V2, V1);
    else
      TopExp::Vertices(E, V1, V2);

    V1.Orientation(TopAbs_FORWARD);
    V2.Orientation(TopAbs_REVERSED);
    if (!vmap.Add(V1))
      vmap.Remove(V1);
    if (!vmap.Add(V2))
      vmap.Remove(V2);

    it.Next();
  }
  if (vmap.IsEmpty())
  {
    TopoDS_Shape aLocalShape = V2.Oriented(TopAbs_FORWARD);
    Vfirst                   = TopoDS::Vertex(aLocalShape);
    aLocalShape              = V2.Oriented(TopAbs_REVERSED);
    Vlast                    = TopoDS::Vertex(aLocalShape);
  }
  else if (vmap.Extent() == 2)
  {
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator ite(vmap);

    while (ite.More() && ite.Key().Orientation() != TopAbs_FORWARD)
      ite.Next();
    if (ite.More())
      Vfirst = TopoDS::Vertex(ite.Key());
    ite.Initialize(vmap);
    while (ite.More() && ite.Key().Orientation() != TopAbs_REVERSED)
      ite.Next();
    if (ite.More())
      Vlast = TopoDS::Vertex(ite.Key());
  }
}

bool TopExp::CommonVertex(const TopoDS_Edge& E1, const TopoDS_Edge& E2, TopoDS_Vertex& V)
{
  TopoDS_Vertex firstVertex1, lastVertex1, firstVertex2, lastVertex2;
  TopExp::Vertices(E1, firstVertex1, lastVertex1);
  TopExp::Vertices(E2, firstVertex2, lastVertex2);

  if (firstVertex1.IsSame(firstVertex2) || firstVertex1.IsSame(lastVertex2))
  {
    V = firstVertex1;
    return true;
  }
  if (lastVertex1.IsSame(firstVertex2) || lastVertex1.IsSame(lastVertex2))
  {
    V = lastVertex1;
    return true;
  }
  return false;
}
