

#include <RWObj_TriangulationReader.hpp>

#include <BRep_Builder.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Iterator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(RWObj_TriangulationReader, RWObj_Reader)

bool RWObj_TriangulationReader::addMesh(const RWObj_SubMesh&      theMesh,
                                        const RWObj_SubMeshReason theReason)
{
  if (!myToCreateShapes)
  {
    return false;
  }

  if (occ::handle<Poly_Triangulation> aTris = GetTriangulation())
  {
    myNodes.Clear();
    myNodesUV.Clear();
    myNormals.Clear();
    myTriangles.Clear();
    if (theMesh.Group != myLastGroupName)
    {

      if (addSubShape(myLastObjectShape, myLastGroupShape, false))
      {
        if (myShapeReceiver != nullptr)
        {
          const RWObj_Material* aMaterial =
            myLastGroupShape.ShapeType() == TopAbs_FACE && !myLastFaceMaterial.IsEmpty()
              ? myMaterials.Seek(myLastFaceMaterial)
              : nullptr;
          myShapeReceiver->BindNamedShape(myLastGroupShape, myLastGroupName, aMaterial, false);
        }
      }
      myLastGroupShape = TopoDS_Shape();
      myLastGroupName  = theMesh.Group;
    }

    TopoDS_Face  aNewFace;
    BRep_Builder aBuilder;
    aBuilder.MakeFace(aNewFace, aTris);
    addSubShape(myLastGroupShape, aNewFace, true);
    myLastFaceMaterial = theMesh.Material;
    if (myShapeReceiver != nullptr)
    {
      const RWObj_Material* aMaterial = myMaterials.Seek(theMesh.Material);
      myShapeReceiver->BindNamedShape(aNewFace, "", aMaterial, false);
    }
  }

  if (theReason == RWObj_SubMeshReason_NewObject)
  {

    if (addSubShape(myLastObjectShape, myLastGroupShape, false))
    {
      if (myShapeReceiver != nullptr)
      {
        const RWObj_Material* aMaterial =
          myLastGroupShape.ShapeType() == TopAbs_FACE && !myLastFaceMaterial.IsEmpty()
            ? myMaterials.Seek(myLastFaceMaterial)
            : nullptr;
        myShapeReceiver->BindNamedShape(myLastGroupShape, myLastGroupName, aMaterial, false);
      }
    }
    myLastGroupShape = TopoDS_Shape();
    myLastGroupName.Clear();

    if (addSubShape(myResultShape, myLastObjectShape, false))
    {
      if (myShapeReceiver != nullptr)
      {
        myShapeReceiver->BindNamedShape(myLastObjectShape, theMesh.Object, nullptr, true);
      }
    }
    myLastObjectShape = TopoDS_Compound();
  }
  return true;
}

bool RWObj_TriangulationReader::addSubShape(TopoDS_Shape&       theParent,
                                            const TopoDS_Shape& theSubShape,
                                            const bool          theToExpandCompound)
{
  if (theSubShape.IsNull())
  {
    return false;
  }

  BRep_Builder aBuilder;
  if (theParent.IsNull() && theToExpandCompound)
  {
    theParent = theSubShape;
    return true;
  }

  TopoDS_Compound aComp;
  if (!theParent.IsNull() && theParent.ShapeType() == TopAbs_COMPOUND)
  {
    aComp = TopoDS::Compound(theParent);
  }
  else
  {
    aBuilder.MakeCompound(aComp);
    if (!theParent.IsNull())
    {
      aBuilder.Add(aComp, theParent);
    }
  }
  aBuilder.Add(aComp, theSubShape);
  theParent = aComp;
  return true;
}

occ::handle<Poly_Triangulation> RWObj_TriangulationReader::GetTriangulation()
{
  if (myTriangles.IsEmpty())
  {
    return occ::handle<Poly_Triangulation>();
  }

  const bool hasNormals = myNodes.Length() == myNormals.Length();
  const bool hasUV      = myNodes.Length() == myNodesUV.Length();

  occ::handle<Poly_Triangulation> aPoly =
    new Poly_Triangulation(myNodes.Length(), myTriangles.Length(), hasUV);
  for (int aNodeIter = 0; aNodeIter < myNodes.Size(); ++aNodeIter)
  {
    const gp_Pnt& aNode = myNodes.Value(aNodeIter);
    aPoly->SetNode(aNodeIter + 1, aNode);
  }
  if (hasUV)
  {
    for (int aNodeIter = 0; aNodeIter < myNodes.Size(); ++aNodeIter)
    {
      const NCollection_Vec2<float>& aNode = myNodesUV.Value(aNodeIter);
      aPoly->SetUVNode(aNodeIter + 1, gp_Pnt2d(aNode.x(), aNode.y()));
    }
  }
  if (hasNormals)
  {
    aPoly->AddNormals();
    int aNbInvalid = 0;
    for (int aNodeIter = 0; aNodeIter < myNodes.Size(); ++aNodeIter)
    {
      const NCollection_Vec3<float>& aNorm = myNormals.Value(aNodeIter);
      const float                    aMod2 = aNorm.SquareModulus();
      if (aMod2 > 0.001f)
      {
        aPoly->SetNormal(aNodeIter + 1, aNorm);
      }
      else
      {
        ++aNbInvalid;
        aPoly->SetNormal(aNodeIter + 1, NCollection_Vec3<float>(0.0f, 0.0f, 1.0f));
      }
    }
    if (aNbInvalid == myNodes.Length())
    {
      aPoly->RemoveNormals();
    }
  }

  for (int aTriIter = 0; aTriIter < myTriangles.Size(); ++aTriIter)
  {
    aPoly->SetTriangle(aTriIter + 1, myTriangles[aTriIter]);
  }

  return aPoly;
}

TopoDS_Shape RWObj_TriangulationReader::ResultShape()
{
  if (!myToCreateShapes)
  {
    if (occ::handle<Poly_Triangulation> aTris = GetTriangulation())
    {
      TopoDS_Face  aFace;
      BRep_Builder aBuilder;
      aBuilder.MakeFace(aFace, aTris);
      return aFace;
    }
    return TopoDS_Shape();
  }

  if (!myResultShape.IsNull() && myResultShape.ShapeType() == TopAbs_COMPOUND
      && myResultShape.NbChildren() == 1 && myActiveSubMesh.Object.IsEmpty())
  {
    TopoDS_Iterator aChildIter(myResultShape);
    return aChildIter.Value();
  }
  return myResultShape;
}
