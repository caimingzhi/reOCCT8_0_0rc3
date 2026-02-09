#include <BRepTools_Substitution.hpp>
#include <Standard_NullObject.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepTool_PurgeInternalEdges.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>

TopOpeBRepTool_PurgeInternalEdges::TopOpeBRepTool_PurgeInternalEdges(const TopoDS_Shape& theShape,
                                                                     const bool          PerformNow)
    : myShape(theShape),
      myIsDone(false)
{

  Standard_NullObject_Raise_if(theShape.IsNull(), "PurgeInternalEdges");

  if (PerformNow)
  {
    Perform();
  }
}

void TopOpeBRepTool_PurgeInternalEdges::Faces(
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theMapFacLstEdg)
{

  if (!myIsDone)
  {
    BuildList();
  }

  theMapFacLstEdg = myMapFacLstEdg;
}

int TopOpeBRepTool_PurgeInternalEdges::NbEdges() const
{

  Standard_NullObject_Raise_if(myShape.IsNull(), "PurgeInternalEdges : No Shape");
  int nbedges = 0;

  if (myMapFacLstEdg.Extent() > 0)
  {

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator itFacEdg;

    for (itFacEdg.Initialize(myMapFacLstEdg); itFacEdg.More(); itFacEdg.Next())
    {
      const TopoDS_Shape&                   facecur = itFacEdg.Key();
      const NCollection_List<TopoDS_Shape>& LmapEdg = myMapFacLstEdg.Find(facecur);

      nbedges += LmapEdg.Extent();
    }
  }

  return nbedges;
}

TopoDS_Shape& TopOpeBRepTool_PurgeInternalEdges::Shape()
{

  Standard_NullObject_Raise_if(myShape.IsNull(), "PurgeInternalEdges : No Shape");

  return myShape;
}

void TopOpeBRepTool_PurgeInternalEdges::BuildList()
{

  TopExp_Explorer    ExpEdge;
  TopAbs_Orientation orien;

  myMapEdgLstFac.Clear();

  TopExp::MapShapesAndAncestors(myShape, TopAbs_EDGE, TopAbs_FACE, myMapEdgLstFac);

  bool                                     ToKeep;
  int                                      iEdg;
  NCollection_List<TopoDS_Shape>::Iterator itFac, itFacToTreat;
  NCollection_List<TopoDS_Shape>           LstFacToTreat;

  for (iEdg = 1; iEdg <= myMapEdgLstFac.Extent(); iEdg++)
  {
    const TopoDS_Shape&                   edgecur = myMapEdgLstFac.FindKey(iEdg);
    const NCollection_List<TopoDS_Shape>& LmapFac = myMapEdgLstFac.FindFromKey(edgecur);

    itFac.Initialize(LmapFac);
    LstFacToTreat.Clear();

    if (LmapFac.Extent() > 1)
    {

      ToKeep = false;

      while (itFac.More() && !ToKeep)
      {
        const TopoDS_Shape& facecur = itFac.Value();

        for (ExpEdge.Init(facecur, TopAbs_EDGE); ExpEdge.More(); ExpEdge.Next())
        {
          const TopoDS_Shape& edge = ExpEdge.Current();

          orien = edge.Orientation();

          if (edge.IsSame(edgecur))
          {

            if (orien == TopAbs_INTERNAL || orien == TopAbs_EXTERNAL)
            {
              LstFacToTreat.Append(facecur);
            }
            else
            {

              LstFacToTreat.Clear();
              ToKeep = true;
            }
            break;
          }
        }

        itFac.Next();
      }
    }

    else
    {
      if (edgecur.Orientation() == TopAbs_INTERNAL || edgecur.Orientation() == TopAbs_EXTERNAL)
      {
        LstFacToTreat.Append(itFac.Value());
      }
    }

    if (!LstFacToTreat.IsEmpty())
    {
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapUniqEdg;
      for (itFacToTreat.Initialize(LstFacToTreat); itFacToTreat.More(); itFacToTreat.Next())
      {
        const TopoDS_Shape& face = itFacToTreat.Value();

        if (!myMapFacLstEdg.IsBound(face))
        {
          NCollection_List<TopoDS_Shape> LmapEdg;
          if (!mapUniqEdg.Contains(edgecur))
          {
            mapUniqEdg.Add(edgecur);
            LmapEdg.Append(edgecur);
            myMapFacLstEdg.Bind(face, LmapEdg);
          }
        }
        else
        {
          NCollection_List<TopoDS_Shape>& LmapEdg = myMapFacLstEdg.ChangeFind(face);
          if (!mapUniqEdg.Contains(edgecur))
          {
            mapUniqEdg.Add(edgecur);
            LmapEdg.Append(edgecur);
          }
        }
      }
    }
  }

  myIsDone = true;
}

void TopOpeBRepTool_PurgeInternalEdges::Perform()
{

  if (!myIsDone)
  {
    BuildList();
  }

  if (myMapFacLstEdg.Extent() > 0)
  {

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator                               itFacEdg;
    NCollection_List<TopoDS_Shape>::Iterator itEdg;
    NCollection_List<TopoDS_Shape>           EmptyList;
    BRepTools_Substitution                   Bsub;

    for (itFacEdg.Initialize(myMapFacLstEdg); itFacEdg.More(); itFacEdg.Next())
    {
      const TopoDS_Shape&                   facecur = itFacEdg.Key();
      const NCollection_List<TopoDS_Shape>& LmapEdg = myMapFacLstEdg.Find(facecur);

      for (itEdg.Initialize(LmapEdg); itEdg.More(); itEdg.Next())
      {
        Bsub.Substitute(itEdg.Value(), EmptyList);
      }
    }

    Bsub.Build(myShape);
    if (Bsub.IsCopied(myShape))
    {
      myShape = (Bsub.Copy(myShape)).First();
    }
  }
}
