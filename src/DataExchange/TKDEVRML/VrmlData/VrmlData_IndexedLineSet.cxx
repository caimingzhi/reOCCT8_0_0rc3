#include <VrmlData_IndexedLineSet.hpp>
#include <VrmlData_Scene.hpp>
#include <VrmlData_InBuffer.hpp>
#include <VrmlData_UnknownNode.hpp>
#include <BRep_Builder.hpp>
#include <Poly_Polygon3D.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <VrmlData_Color.hpp>
#include <VrmlData_Coordinate.hpp>

IMPLEMENT_STANDARD_RTTIEXT(VrmlData_IndexedLineSet, VrmlData_Geometry)

#ifdef _MSC_VER
  #define _CRT_SECURE_NO_DEPRECATE
  #pragma warning(disable : 4996)
#endif

Quantity_Color VrmlData_IndexedLineSet::GetColor(const int, const int)
{

  return Quantity_NOC_BLACK;
}

const occ::handle<TopoDS_TShape>& VrmlData_IndexedLineSet::TShape()
{
  if (myNbPolygons == 0)
    myTShape.Nullify();
  else if (myIsModified)
  {
    int           i;
    BRep_Builder  aBuilder;
    const gp_XYZ* arrNodes = myCoords->Values();

    TopoDS_Wire aWire;
    aBuilder.MakeWire(aWire);
    for (i = 0; i < (int)myNbPolygons; i++)
    {
      const int*                 arrIndice;
      const int                  nNodes = Polygon(i, arrIndice);
      NCollection_Array1<gp_Pnt> arrPoint(1, nNodes);
      NCollection_Array1<double> arrParam(1, nNodes);
      for (int j = 0; j < nNodes; j++)
      {
        arrPoint(j + 1).SetXYZ(arrNodes[arrIndice[j]]);
        arrParam(j + 1) = j;
      }
      const occ::handle<Poly_Polygon3D> aPolyPolygon = new Poly_Polygon3D(arrPoint, arrParam);
      TopoDS_Edge                       anEdge;
      aBuilder.MakeEdge(anEdge, aPolyPolygon);
      aBuilder.Add(aWire, anEdge);
    }
    myTShape = aWire.TShape();
  }
  return myTShape;
}

occ::handle<VrmlData_Node> VrmlData_IndexedLineSet::Clone(
  const occ::handle<VrmlData_Node>& theOther) const
{
  occ::handle<VrmlData_IndexedLineSet> aResult =
    occ::down_cast<VrmlData_IndexedLineSet>(VrmlData_Node::Clone(theOther));
  if (aResult.IsNull())
    aResult = new VrmlData_IndexedLineSet(theOther.IsNull() ? Scene() : theOther->Scene(), Name());

  if (&aResult->Scene() == &Scene())
  {
    aResult->SetCoordinates(myCoords);
    aResult->SetColors(myColors);
    aResult->SetPolygons(myNbPolygons, myArrPolygons);
    aResult->SetColorInd(myNbColors, myArrColorInd);
  }
  else
  {

    const occ::handle<VrmlData_UnknownNode> aDummyNode = new VrmlData_UnknownNode(aResult->Scene());
    if (!myCoords.IsNull())
      aResult->SetCoordinates(occ::down_cast<VrmlData_Coordinate>(myCoords->Clone(aDummyNode)));
    if (!myColors.IsNull())
      aResult->SetColors(occ::down_cast<VrmlData_Color>(myColors->Clone(aDummyNode)));

    aResult->SetPolygons(myNbPolygons, myArrPolygons);
    aResult->SetColorInd(myNbColors, myArrColorInd);
  }
  aResult->SetColorPerVertex(myColorPerVertex);
  return aResult;
}

VrmlData_ErrorStatus VrmlData_IndexedLineSet::Read(VrmlData_InBuffer& theBuffer)
{
  VrmlData_ErrorStatus  aStatus;
  const VrmlData_Scene& aScene = Scene();
  while (OK(aStatus, VrmlData_Scene::ReadLine(theBuffer)))
  {
    if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "colorPerVertex"))
      aStatus = ReadBoolean(theBuffer, myColorPerVertex);
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "coordIndex"))
      aStatus = aScene.ReadArrIndex(theBuffer, myArrPolygons, myNbPolygons);
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "colorIndex"))
      aStatus = aScene.ReadArrIndex(theBuffer, myArrColorInd, myNbColors);

    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "color"))
    {
      occ::handle<VrmlData_Node> aNode;
      aStatus  = ReadNode(theBuffer, aNode, STANDARD_TYPE(VrmlData_Color));
      myColors = occ::down_cast<VrmlData_Color>(aNode);
    }
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "coord"))
    {
      occ::handle<VrmlData_Node> aNode;
      aStatus  = ReadNode(theBuffer, aNode, STANDARD_TYPE(VrmlData_Coordinate));
      myCoords = occ::down_cast<VrmlData_Coordinate>(aNode);
    }
    else
      break;
    if (!OK(aStatus))
      break;
  }

  if (OK(aStatus) || aStatus == VrmlData_EmptyData)
    if (OK(aStatus, readBrace(theBuffer)))
    {

      ;
    }
  return aStatus;
}

VrmlData_ErrorStatus VrmlData_IndexedLineSet::Write(const char* thePrefix) const
{
  static char           header[] = "IndexedLineSet {";
  const VrmlData_Scene& aScene   = Scene();
  VrmlData_ErrorStatus  aStatus;
  if (OK(aStatus, aScene.WriteLine(thePrefix, header, GlobalIndent())))
  {

    if (OK(aStatus) && !myCoords.IsNull())
      aStatus = aScene.WriteNode("coord", myCoords);
    if (OK(aStatus))
      aStatus = aScene.WriteArrIndex("coordIndex", myArrPolygons, myNbPolygons);

    if (OK(aStatus) && !myColorPerVertex)
      aStatus = aScene.WriteLine("colorPerVertex  FALSE");
    if (OK(aStatus) && !myColors.IsNull())
      aStatus = aScene.WriteNode("color", myColors);
    if (OK(aStatus))
      aStatus = aScene.WriteArrIndex("colorIndex", myArrColorInd, myNbColors);

    aStatus = WriteClosing();
  }
  return aStatus;
}

bool VrmlData_IndexedLineSet::IsDefault() const
{
  bool aResult(true);
  if (myNbPolygons)
    aResult = false;
  else if (!myCoords.IsNull())
    aResult = myCoords->IsDefault();
  return aResult;
}
