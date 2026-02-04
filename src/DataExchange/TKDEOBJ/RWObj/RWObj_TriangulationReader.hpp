#pragma once


#include <RWObj_Reader.hpp>

#include <Poly_Triangulation.hpp>
#include <TopoDS_Compound.hpp>

//! Interface to store shape attributes into document.
class RWObj_IShapeReceiver
{
public:
  //! @param theShape       shape to register
  //! @param theName        shape name
  //! @param theMaterial    shape material
  //! @param theIsRootShape indicates that this is a root object (free shape)
  virtual void BindNamedShape(const TopoDS_Shape&            theShape,
                              const TCollection_AsciiString& theName,
                              const RWObj_Material*          theMaterial,
                              const bool                     theIsRootShape) = 0;
};

//! RWObj_Reader implementation dumping OBJ file into Poly_Triangulation.
class RWObj_TriangulationReader : public RWObj_Reader
{
  DEFINE_STANDARD_RTTIEXT(RWObj_TriangulationReader, RWObj_Reader)
public:
  //! Constructor.
  RWObj_TriangulationReader()
      : myShapeReceiver(nullptr),
        myToCreateShapes(true)
  {
  }

  //! Set flag to create shapes.
  void SetCreateShapes(bool theToCreateShapes) { myToCreateShapes = theToCreateShapes; }

  //! Set shape receiver callback.
  void SetShapeReceiver(RWObj_IShapeReceiver* theReceiver) { myShapeReceiver = theReceiver; }

  //! Create Poly_Triangulation from collected data
  Standard_EXPORT virtual occ::handle<Poly_Triangulation> GetTriangulation();

  //! Return result shape.
  Standard_EXPORT TopoDS_Shape ResultShape();

protected:
  //! Flush active sub-mesh.
  Standard_EXPORT bool addMesh(const RWObj_SubMesh&      theMesh,
                               const RWObj_SubMeshReason theReason) override;

  //! Retrieve sub-mesh node position.
  gp_Pnt getNode(int theIndex) const override { return myNodes.Value(theIndex - 1); }

  //! Add new node.
  int addNode(const gp_Pnt& thePnt) override
  {
    myNodes.Append(thePnt);
    return myNodes.Size();
  }

  //! Ignore normal.
  void setNodeNormal(const int theIndex, const NCollection_Vec3<float>& theNormal) override
  {
    myNormals.SetValue(theIndex - 1, theNormal);
  }

  //! Ignore texture coordinates.
  void setNodeUV(const int theIndex, const NCollection_Vec2<float>& theUV) override
  {
    myNodesUV.SetValue(theIndex - 1, theUV);
  }

  //! Add element.
  void addElement(int theN1, int theN2, int theN3, int theN4) override
  {
    myTriangles.Append(Poly_Triangle(theN1, theN2, theN3));
    if (theN4 != -1)
    {
      myTriangles.Append(Poly_Triangle(theN1, theN3, theN4));
    }
  }

protected:
  //! Add sub-shape into specified shape
  Standard_EXPORT bool addSubShape(TopoDS_Shape&       theParent,
                                   const TopoDS_Shape& theSubShape,
                                   const bool          theToExpandCompound);

protected:
  NCollection_Vector<gp_Pnt> myNodes; //!< nodes   of currently filled triangulation
  NCollection_Vector<NCollection_Vec3<float>>
    myNormals; //!< normals of currently filled triangulation
  NCollection_Vector<NCollection_Vec2<float>>
                                    myNodesUV;   //!< UVs     of currently filled triangulation
  NCollection_Vector<Poly_Triangle> myTriangles; //!< indexes of currently filled triangulation

  RWObj_IShapeReceiver* myShapeReceiver;      //!< optional shape receiver
  TopoDS_Compound       myResultShape;        //!< result shape as Compound of objects
  TopoDS_Compound       myLastObjectShape;    //!< Compound containing current object groups
                                              // clang-format off
  TopoDS_Shape            myLastGroupShape;  //!< current group shape - either a single Face or Compound of Faces
                                              // clang-format on
  TCollection_AsciiString myLastGroupName;    //!< current group name
  TCollection_AsciiString myLastFaceMaterial; //!< last face material name
  bool                    myToCreateShapes;   //!< create a single triangulation
};

