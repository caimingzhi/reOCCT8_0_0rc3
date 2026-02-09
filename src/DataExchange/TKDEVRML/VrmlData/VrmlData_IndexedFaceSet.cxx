#include <VrmlData_IndexedFaceSet.hpp>
#include <VrmlData_InBuffer.hpp>
#include <VrmlData_UnknownNode.hpp>
#include <BRep_TFace.hpp>
#include <BRepMesh_Triangulator.hpp>
#include <VrmlData_Coordinate.hpp>
#include <VrmlData_Color.hpp>
#include <VrmlData_Normal.hpp>
#include <VrmlData_TextureCoordinate.hpp>
#include <VrmlData_Scene.hpp>
#include <Precision.hpp>
#include <NCollection_Vector.hpp>
#include <NCollection_DataMap.hpp>
#include <Poly.hpp>
#include <Standard_ShortReal.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(VrmlData_IndexedFaceSet, VrmlData_Faceted)

#ifdef _MSC_VER
  #define _CRT_SECURE_NO_DEPRECATE
  #pragma warning(disable : 4996)
#endif

VrmlData_ErrorStatus VrmlData_Faceted::readData(VrmlData_InBuffer& theBuffer)
{
  VrmlData_ErrorStatus aStatus(VrmlData_EmptyData);
  bool                 aBool;
  if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "ccw"))
  {
    if (OK(aStatus, ReadBoolean(theBuffer, aBool)))
      myIsCCW = aBool;
  }
  else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "convex"))
  {
    if (OK(aStatus, ReadBoolean(theBuffer, aBool)))
      myIsConvex = aBool;
  }
  else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "solid"))
  {
    if (OK(aStatus, ReadBoolean(theBuffer, aBool)))
      myIsSolid = aBool;
  }
  else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "creaseAngle"))
  {
    double anAngle;
    if (OK(aStatus, Scene().ReadReal(theBuffer, anAngle, false, false)))
    {
      if (anAngle < -Precision::Confusion() * 0.001)
        aStatus = VrmlData_IrrelevantNumber;
      else
        myCreaseAngle = anAngle;
    }
  }
  return aStatus;
}

const occ::handle<TopoDS_TShape>& VrmlData_IndexedFaceSet::TShape()
{
  if (myNbPolygons == 0)
  {
    myTShape.Nullify();
    return myTShape;
  }
  else if (!myIsModified)
  {
    return myTShape;
  }

  const gp_XYZ* arrNodes = myCoords->Values();
  const int     nNodes   = (int)myCoords->Length();

  NCollection_Map<int>                        mapNodeId;
  NCollection_Map<int>                        mapPolyId;
  NCollection_List<NCollection_Sequence<int>> aPolygons;
  NCollection_List<gp_Dir>                    aNorms;
  int                                         i = 0;
  for (; i < (int)myNbPolygons; i++)
  {
    const int* arrIndice = myArrPolygons[i];
    int        nn        = arrIndice[0];
    if (nn < 3)
    {

      continue;
    }
    NCollection_Sequence<int> aPolygon;
    int                       in = 1;
    for (; in <= nn; in++)
    {
      if (arrIndice[in] > nNodes)
      {
        break;
      }
      aPolygon.Append(arrIndice[in]);
    }
    if (in <= nn)
    {

      continue;
    }

    gp_XYZ aSum;
    gp_XYZ aPrevP = arrNodes[aPolygon(1)];
    for (in = 2; in < aPolygon.Length(); in++)
    {
      gp_XYZ aP1 = arrNodes[aPolygon(in)];
      gp_XYZ aP2 = arrNodes[aPolygon(in + 1)];
      gp_XYZ aV1 = aP1 - aPrevP;
      gp_XYZ aV2 = aP2 - aPrevP;
      gp_XYZ S   = aV1.Crossed(aV2);
      aSum += S;
    }
    if (aSum.Modulus() < Precision::Confusion())
    {

      continue;
    }
    gp_Dir aNormal(aSum);
    mapPolyId.Add(i);
    aPolygons.Append(aPolygon);
    aNorms.Append(aNormal);

    for (in = 1; in <= aPolygon.Length(); in++)
    {
      mapNodeId.Add(arrIndice[in]);
    }
  }

  const int nbNodes(mapNodeId.Extent());
  if (!nbNodes)
  {
    myIsModified = false;
    myTShape.Nullify();
    return myTShape;
  }

  NCollection_Vector<gp_XYZ>    aNodes;
  NCollection_DataMap<int, int> mapIdId;
  for (i = 0; i < nNodes; i++)
  {
    if (mapNodeId.Contains(i))
    {
      const gp_XYZ& aN1 = arrNodes[i];
      mapIdId.Bind(i, aNodes.Length());
      aNodes.Append(aN1);
    }
  }

  NCollection_List<NCollection_Sequence<int>>::Iterator itP(aPolygons);
  for (; itP.More(); itP.Next())
  {
    NCollection_Sequence<int>& aPolygon = itP.ChangeValue();
    for (int in = 1; in <= aPolygon.Length(); in++)
    {
      int newIdx               = mapIdId.Find(aPolygon.Value(in));
      aPolygon.ChangeValue(in) = newIdx;
    }
  }

  NCollection_List<Poly_Triangle> aTriangles;
  itP.Init(aPolygons);
  for (NCollection_List<gp_Dir>::Iterator itN(aNorms); itP.More(); itP.Next(), itN.Next())
  {
    NCollection_List<Poly_Triangle> aTrias;
    try
    {
      NCollection_List<NCollection_Sequence<int>> aPList;
      aPList.Append(itP.Value());
      BRepMesh_Triangulator aTriangulator(aNodes, aPList, itN.Value());
      aTriangulator.Perform(aTrias);
      aTriangles.Append(aTrias);
    }
    catch (...)
    {
      continue;
    }
  }
  if (aTriangles.IsEmpty())
  {
    return myTShape;
  }

  occ::handle<Poly_Triangulation> aTriangulation =
    new Poly_Triangulation(aNodes.Length(), aTriangles.Extent(), false);

  for (i = 0; i < aNodes.Length(); i++)
  {
    aTriangulation->SetNode(i + 1, gp_Pnt(aNodes(i)));
  }

  NCollection_List<Poly_Triangle>::Iterator itT(aTriangles);
  for (i = 1; itT.More(); itT.Next(), i++)
  {
    aTriangulation->SetTriangle(i, itT.Value());
  }

  occ::handle<BRep_TFace> aFace = new BRep_TFace();
  aFace->Triangulation(aTriangulation);
  myTShape = aFace;

  if (myNormals.IsNull())
  {
    Poly::ComputeNormals(aTriangulation);
  }
  else
  {

    if (myNormalPerVertex)
    {
      aTriangulation->AddNormals();
      if (myArrNormalInd == nullptr)
      {
        for (i = 0; i < nbNodes; i++)
        {
          const gp_XYZ& aNormal = myNormals->Normal(i);
          aTriangulation->SetNormal(i + 1, aNormal);
        }
      }
      else
      {
        for (i = 0; i < (int)myNbPolygons; i++)
        {
          if (mapPolyId.Contains(i))
          {
            const int* anArrNodes;
            Polygon(i, anArrNodes);
            const int* arrIndice;
            int        nbn = IndiceNormals(i, arrIndice);
            for (int j = 0; j < nbn; j++)
            {
              const gp_XYZ& aNormal = myNormals->Normal(arrIndice[j]);
              aTriangulation->SetNormal(mapIdId(anArrNodes[j]) + 1, aNormal);
            }
          }
        }
      }
    }
    else
    {
    }
  }

  myIsModified = false;

  return myTShape;
}

occ::handle<VrmlData_Node> VrmlData_IndexedFaceSet::Clone(
  const occ::handle<VrmlData_Node>& theOther) const
{
  occ::handle<VrmlData_IndexedFaceSet> aResult =
    occ::down_cast<VrmlData_IndexedFaceSet>(VrmlData_Node::Clone(theOther));
  if (aResult.IsNull())
    aResult = new VrmlData_IndexedFaceSet(theOther.IsNull() ? Scene() : theOther->Scene(), Name());

  if (&aResult->Scene() == &Scene())
  {
    aResult->SetCoordinates(myCoords);
    aResult->SetNormals(myNormals);
    aResult->SetColors(myColors);
    aResult->SetPolygons(myNbPolygons, myArrPolygons);
    aResult->SetNormalInd(myNbNormals, myArrNormalInd);
    aResult->SetColorInd(myNbColors, myArrColorInd);
    aResult->SetTextureCoordInd(myNbTextures, myArrTextureInd);
  }
  else
  {

    const occ::handle<VrmlData_UnknownNode> aDummyNode = new VrmlData_UnknownNode(aResult->Scene());
    if (!myCoords.IsNull())
      aResult->SetCoordinates(occ::down_cast<VrmlData_Coordinate>(myCoords->Clone(aDummyNode)));
    if (!myNormals.IsNull())
      aResult->SetNormals(occ::down_cast<VrmlData_Normal>(myNormals->Clone(aDummyNode)));
    if (!myColors.IsNull())
      aResult->SetColors(occ::down_cast<VrmlData_Color>(myColors->Clone(aDummyNode)));

    aResult->SetPolygons(myNbPolygons, myArrPolygons);
    aResult->SetNormalInd(myNbNormals, myArrNormalInd);
    aResult->SetColorInd(myNbColors, myArrColorInd);
    aResult->SetTextureCoordInd(myNbTextures, myArrTextureInd);
  }
  aResult->SetNormalPerVertex(myNormalPerVertex);
  aResult->SetColorPerVertex(myColorPerVertex);
  return aResult;
}

VrmlData_ErrorStatus VrmlData_IndexedFaceSet::Read(VrmlData_InBuffer& theBuffer)
{
  VrmlData_ErrorStatus  aStatus;
  const VrmlData_Scene& aScene = Scene();
  while (OK(aStatus, VrmlData_Scene::ReadLine(theBuffer)))
  {
    if (OK(aStatus, VrmlData_Faceted::readData(theBuffer)))
      continue;
    if (aStatus != VrmlData_EmptyData)
      break;
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "colorPerVertex"))
      aStatus = ReadBoolean(theBuffer, myColorPerVertex);
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "normalPerVertex"))
      aStatus = ReadBoolean(theBuffer, myNormalPerVertex);
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "coordIndex"))
    {
      aStatus = aScene.ReadArrIndex(theBuffer, myArrPolygons, myNbPolygons);
    }
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "colorIndex"))
      aStatus = aScene.ReadArrIndex(theBuffer, myArrColorInd, myNbColors);
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "normalIndex"))
      aStatus = aScene.ReadArrIndex(theBuffer, myArrNormalInd, myNbNormals);
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "texCoordIndex"))
      aStatus = aScene.ReadArrIndex(theBuffer, myArrTextureInd, myNbTextures);

    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "texCoord"))
    {
      occ::handle<VrmlData_Node> aNode;
      aStatus    = ReadNode(theBuffer, aNode, STANDARD_TYPE(VrmlData_TextureCoordinate));
      myTxCoords = occ::down_cast<VrmlData_TextureCoordinate>(aNode);
    }
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
    else if (VRMLDATA_LCOMPARE(theBuffer.LinePtr, "normal"))
    {
      occ::handle<VrmlData_Node> aNode;
      aStatus   = ReadNode(theBuffer, aNode, STANDARD_TYPE(VrmlData_Normal));
      myNormals = occ::down_cast<VrmlData_Normal>(aNode);
    }
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

bool VrmlData_IndexedFaceSet::IsDefault() const
{
  bool aResult(true);
  if (myNbPolygons)
    aResult = false;
  else if (!myCoords.IsNull())
    aResult = myCoords->IsDefault();
  return aResult;
}

VrmlData_ErrorStatus VrmlData_IndexedFaceSet::Write(const char* thePrefix) const
{
  static char           header[] = "IndexedFaceSet {";
  const VrmlData_Scene& aScene   = Scene();
  VrmlData_ErrorStatus  aStatus;
  if (OK(aStatus, aScene.WriteLine(thePrefix, header, GlobalIndent())))
  {

    if (!IsCCW())
      aStatus = aScene.WriteLine("ccw         FALSE");
    if (OK(aStatus) && !IsSolid())
      aStatus = aScene.WriteLine("solid       FALSE");
    if (OK(aStatus) && !IsConvex())
      aStatus = aScene.WriteLine("convex      FALSE");
    if (OK(aStatus) && CreaseAngle() > Precision::Confusion())
    {
      char buf[64];
      Sprintf(buf, "%.9g", CreaseAngle());
      aStatus = aScene.WriteLine("creaseAngle", buf);
    }

    if (OK(aStatus) && !myCoords.IsNull())
      aStatus = aScene.WriteNode("coord", myCoords);
    if (OK(aStatus))
      aStatus = aScene.WriteArrIndex("coordIndex", myArrPolygons, myNbPolygons);

    if (OK(aStatus) && !myNormalPerVertex)
      aStatus = aScene.WriteLine("normalPerVertex FALSE");
    if (OK(aStatus) && !myNormals.IsNull())
      aStatus = aScene.WriteNode("normal", myNormals);
    if (OK(aStatus))
      aStatus = aScene.WriteArrIndex("normalIndex", myArrNormalInd, myNbNormals);

    if (OK(aStatus) && !myColorPerVertex)
      aStatus = aScene.WriteLine("colorPerVertex  FALSE");
    if (OK(aStatus) && !myColors.IsNull())
      aStatus = aScene.WriteNode("color", myColors);
    if (OK(aStatus))
      aStatus = aScene.WriteArrIndex("colorIndex", myArrColorInd, myNbColors);

    if (OK(aStatus) && !myTxCoords.IsNull())
      aStatus = aScene.WriteNode("texCoord", myTxCoords);
    if (OK(aStatus))
      aStatus = aScene.WriteArrIndex("texCoordIndex", myArrTextureInd, myNbTextures);

    aStatus = WriteClosing();
  }
  return aStatus;
}

Quantity_Color VrmlData_IndexedFaceSet::GetColor(const int, const int)
{

  return Quantity_NOC_BLACK;
}
