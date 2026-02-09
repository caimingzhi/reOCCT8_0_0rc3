#include <Draw_Segment3D.hpp>
#include <DrawTrSurf_Polygon3D.hpp>
#include <Draw.hpp>
#include <TCollection_AsciiString.hpp>
#include <Poly_Polygon3D.hpp>
#include <BRepMesh_DataStructureOfDelaun.hpp>

Standard_EXPORT const char* MeshTest_DrawLinks(const char* theNameStr, void* theDataStruct)
{
  if (theNameStr == nullptr || theDataStruct == nullptr)
  {
    return "Error: name or face attribute is null";
  }
  try
  {
    const occ::handle<BRepMesh_DataStructureOfDelaun>& aMeshData =
      *(occ::handle<BRepMesh_DataStructureOfDelaun>*)theDataStruct;
    if (aMeshData.IsNull())
      return "Null mesh data structure";
    int nbLinks = aMeshData->NbLinks();
    std::cout << "nblink=" << nbLinks << std::endl;
    TCollection_AsciiString aName(theNameStr);
    for (int i = 1; i <= nbLinks; i++)
    {
      const BRepMesh_Edge& aLink = aMeshData->GetLink(i);
      if (aLink.Movability() == BRepMesh_Deleted)
        continue;
      int                         n1  = aLink.FirstNode();
      int                         n2  = aLink.LastNode();
      const BRepMesh_Vertex&      aV1 = aMeshData->GetNode(n1);
      const BRepMesh_Vertex&      aV2 = aMeshData->GetNode(n2);
      occ::handle<Draw_Segment3D> aSeg =
        new Draw_Segment3D(gp_Pnt(aV1.Coord().X(), aV1.Coord().Y(), 0),
                           gp_Pnt(aV2.Coord().X(), aV2.Coord().Y(), 0),
                           Draw_bleu);
      Draw::Set((aName + "_" + i).ToCString(), aSeg);
    }
    return theNameStr;
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

Standard_EXPORT const char* MeshTest_DrawTriangles(const char* theNameStr, void* theDataStruct)
{
  if (theNameStr == nullptr || theDataStruct == nullptr)
  {
    return "Error: name or face attribute is null";
  }
  try
  {
    const occ::handle<BRepMesh_DataStructureOfDelaun>& aMeshData =
      *(occ::handle<BRepMesh_DataStructureOfDelaun>*)theDataStruct;

    if (aMeshData.IsNull())
      return "Null mesh data structure";
    int nbElem = aMeshData->NbElements();
    std::cout << "nbelem=" << nbElem << std::endl;
    TCollection_AsciiString aName(theNameStr);
    for (int i = 1; i <= nbElem; i++)
    {
      const BRepMesh_Triangle& aTri = aMeshData->GetElement(i);
      if (aTri.Movability() == BRepMesh_Deleted)
        continue;
      int n[3];
      aMeshData->ElementNodes(aTri, n);
      const BRepMesh_Vertex&            aV1   = aMeshData->GetNode(n[0]);
      const BRepMesh_Vertex&            aV2   = aMeshData->GetNode(n[1]);
      const BRepMesh_Vertex&            aV3   = aMeshData->GetNode(n[2]);
      gp_Pnt                            aP[4] = {gp_Pnt(aV1.Coord().X(), aV1.Coord().Y(), 0),
                                                 gp_Pnt(aV2.Coord().X(), aV2.Coord().Y(), 0),
                                                 gp_Pnt(aV3.Coord().X(), aV3.Coord().Y(), 0),
                                                 gp_Pnt(aV1.Coord().X(), aV1.Coord().Y(), 0)};
      NCollection_Array1<gp_Pnt>        aPnts(aP[0], 1, 4);
      occ::handle<Poly_Polygon3D>       aPoly  = new Poly_Polygon3D(aPnts);
      occ::handle<DrawTrSurf_Polygon3D> aDPoly = new DrawTrSurf_Polygon3D(aPoly);
      Draw::Set((aName + "_" + i).ToCString(), aDPoly);
    }
    return theNameStr;
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}
