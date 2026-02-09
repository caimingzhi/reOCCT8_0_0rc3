#include <BRep_Builder.hpp>
#include <LocOpe_BuildWires.hpp>
#include <LocOpe_WiresOnShape.hpp>
#include <Standard_ConstructionError.hpp>
#include <StdFail_NotDone.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>

static int FindFirstEdge(const NCollection_IndexedDataMap<TopoDS_Shape,
                                                          NCollection_List<TopoDS_Shape>,
                                                          TopTools_ShapeMapHasher>&,
                         const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&);

LocOpe_BuildWires::LocOpe_BuildWires()
    : myDone(false)
{
}

LocOpe_BuildWires::LocOpe_BuildWires(const NCollection_List<TopoDS_Shape>&   L,
                                     const occ::handle<LocOpe_WiresOnShape>& PW)
{
  Perform(L, PW);
}

void LocOpe_BuildWires::Perform(const NCollection_List<TopoDS_Shape>&   L,
                                const occ::handle<LocOpe_WiresOnShape>& PW)
{

  myDone = false;
  myRes.Clear();

  BRep_Builder    B;
  TopoDS_Compound C;
  B.MakeCompound(C);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> theMap;
  NCollection_List<TopoDS_Shape>::Iterator               itl(L);
  for (; itl.More(); itl.Next())
  {
    const TopoDS_Shape& edg = itl.Value();
    if (theMap.Add(edg) && edg.ShapeType() == TopAbs_EDGE)
    {
      B.Add(C, edg.Oriented(TopAbs_FORWARD));
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    theMapVE;
  TopExp::MapShapesAndAncestors(C, TopAbs_VERTEX, TopAbs_EDGE, theMapVE);

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> Bords;

  int i;

  for (i = 1; i <= theMapVE.Extent(); i++)
  {

    TopoDS_Vertex vtx = TopoDS::Vertex(theMapVE.FindKey(i));
    TopoDS_Edge   etmp;
    TopoDS_Vertex aV_border;
    double        partmp;
    if (theMapVE(i).Extent() == 1
        || (PW->OnVertex(vtx, aV_border) || PW->OnEdge(vtx, etmp, partmp)))
    {
      Bords.Add(vtx);
    }
  }

  while ((i = FindFirstEdge(theMapVE, Bords)) <= theMapVE.Extent())
  {
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mapE;
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>        mapV;
    const TopoDS_Edge& edgf = TopoDS::Edge(theMapVE(i).First());

    TopoDS_Vertex VF, VL;
    TopExp::Vertices(edgf, VF, VL);

    if (Bords.Contains(VL) && !Bords.Contains(VF))
    {
      mapE.Add(edgf.Oriented(TopAbs_REVERSED));
      TopoDS_Vertex temp = VF;
      VF                 = VL;
      VL                 = temp;
    }
    else
    {
      mapE.Add(edgf.Oriented(TopAbs_FORWARD));
    }
    mapV.Add(VF);

    while (!(mapV.Contains(VL) || Bords.Contains(VL)))
    {
      int                                      ind = theMapVE.FindIndex(VL);
      NCollection_List<TopoDS_Shape>::Iterator anIterl(theMapVE(ind));
      for (; anIterl.More(); anIterl.Next())
      {
        if (!mapE.Contains(anIterl.Value()))
        {
          break;
        }
      }

      if (!anIterl.More())
      {
        throw Standard_ConstructionError();
      }
      const TopoDS_Edge& theEdge = TopoDS::Edge(anIterl.Value());
      TopoDS_Vertex      Vf, Vl;
      TopExp::Vertices(theEdge, Vf, Vl);
      mapV.Add(VL);
      if (Vf.IsSame(VL))
      {
        mapE.Add(theEdge.Oriented(TopAbs_FORWARD));
        VL = Vl;
      }
      else
      {
        mapE.Add(theEdge.Oriented(TopAbs_REVERSED));
        VL = Vf;
      }
    }

    TopoDS_Wire newWire;
    B.MakeWire(newWire);

    if (mapV.Contains(VL))
    {
      TopoDS_Vertex Vf;

      int j;
      for (j = 1; j <= mapE.Extent(); j++)
      {
        const TopoDS_Edge& edg = TopoDS::Edge(mapE(j));
        if (edg.Orientation() == TopAbs_FORWARD)
        {
          Vf = TopExp::FirstVertex(edg);
        }
        else
        {
          Vf = TopExp::LastVertex(edg);
        }
        if (Vf.IsSame(VL))
        {
          break;
        }
        mapV.Remove(Vf);
      }
      for (; j <= mapE.Extent(); j++)
      {
        B.Add(newWire, mapE(j));
      }
      newWire.Closed(true);
    }
    else
    {
      mapV.Add(VL);
      for (int j = 1; j <= mapE.Extent(); j++)
      {
        B.Add(newWire, mapE(j));
      }
      newWire.Closed(false);
    }

    myRes.Append(newWire);
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itm;
    for (itm.Initialize(mapV); itm.More(); itm.Next())
    {
      const TopoDS_Vertex& vtx = TopoDS::Vertex(itm.Key());
      Bords.Add(vtx);
      int ind = theMapVE.FindIndex(vtx);
      itl.Initialize(theMapVE(ind));
      while (itl.More())
      {
        if (mapE.Contains(itl.Value()))
        {
          theMapVE(ind).Remove(itl);
        }
        else
        {
          itl.Next();
        }
      }
    }
  }

  myDone = true;
}

bool LocOpe_BuildWires::IsDone() const
{
  return myDone;
}

const NCollection_List<TopoDS_Shape>& LocOpe_BuildWires::Result() const
{
  if (!myDone)
  {
    throw StdFail_NotDone();
  }
  return myRes;
}

static int FindFirstEdge(const NCollection_IndexedDataMap<TopoDS_Shape,
                                                          NCollection_List<TopoDS_Shape>,
                                                          TopTools_ShapeMapHasher>&    theMapVE,
                         const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theBord)
{
  int i = 1;

  for (; i <= theMapVE.Extent(); i++)
  {
    if (theMapVE(i).Extent() > 0)
    {
      break;
    }
  }

  if (i > theMapVE.Extent())
  {
    return i;
  }

  int goodi = i;
  for (; i <= theMapVE.Extent(); i++)
  {
    const TopoDS_Shape& vtx = theMapVE.FindKey(i);
    if (theMapVE(i).Extent() > 0 && theBord.Contains(vtx))
    {
      goodi = i;
      break;
    }
  }
  return goodi;
}
