#pragma once

#include <RWObj_Reader.hpp>

#include <Poly_Triangulation.hpp>
#include <TopoDS_Compound.hpp>

class RWObj_IShapeReceiver
{
public:
  virtual void BindNamedShape(const TopoDS_Shape&            theShape,
                              const TCollection_AsciiString& theName,
                              const RWObj_Material*          theMaterial,
                              const bool                     theIsRootShape) = 0;
};

class RWObj_TriangulationReader : public RWObj_Reader
{
  DEFINE_STANDARD_RTTIEXT(RWObj_TriangulationReader, RWObj_Reader)
public:
  RWObj_TriangulationReader()
      : myShapeReceiver(nullptr),
        myToCreateShapes(true)
  {
  }

  void SetCreateShapes(bool theToCreateShapes) { myToCreateShapes = theToCreateShapes; }

  void SetShapeReceiver(RWObj_IShapeReceiver* theReceiver) { myShapeReceiver = theReceiver; }

  Standard_EXPORT virtual occ::handle<Poly_Triangulation> GetTriangulation();

  Standard_EXPORT TopoDS_Shape ResultShape();

protected:
  Standard_EXPORT bool addMesh(const RWObj_SubMesh&      theMesh,
                               const RWObj_SubMeshReason theReason) override;

  gp_Pnt getNode(int theIndex) const override { return myNodes.Value(theIndex - 1); }

  int addNode(const gp_Pnt& thePnt) override
  {
    myNodes.Append(thePnt);
    return myNodes.Size();
  }

  void setNodeNormal(const int theIndex, const NCollection_Vec3<float>& theNormal) override
  {
    myNormals.SetValue(theIndex - 1, theNormal);
  }

  void setNodeUV(const int theIndex, const NCollection_Vec2<float>& theUV) override
  {
    myNodesUV.SetValue(theIndex - 1, theUV);
  }

  void addElement(int theN1, int theN2, int theN3, int theN4) override
  {
    myTriangles.Append(Poly_Triangle(theN1, theN2, theN3));
    if (theN4 != -1)
    {
      myTriangles.Append(Poly_Triangle(theN1, theN3, theN4));
    }
  }

protected:
  Standard_EXPORT bool addSubShape(TopoDS_Shape&       theParent,
                                   const TopoDS_Shape& theSubShape,
                                   const bool          theToExpandCompound);

protected:
  NCollection_Vector<gp_Pnt>                  myNodes;
  NCollection_Vector<NCollection_Vec3<float>> myNormals;
  NCollection_Vector<NCollection_Vec2<float>> myNodesUV;
  NCollection_Vector<Poly_Triangle>           myTriangles;

  RWObj_IShapeReceiver* myShapeReceiver;
  TopoDS_Compound       myResultShape;
  TopoDS_Compound       myLastObjectShape;

  TopoDS_Shape myLastGroupShape;

  TCollection_AsciiString myLastGroupName;
  TCollection_AsciiString myLastFaceMaterial;
  bool                    myToCreateShapes;
};
