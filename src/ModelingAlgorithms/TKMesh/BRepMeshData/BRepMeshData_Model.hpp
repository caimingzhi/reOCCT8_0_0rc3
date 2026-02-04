#pragma once


#include <IMeshData_Model.hpp>
#include <IMeshData_Types.hpp>
#include <NCollection_IncAllocator.hpp>
#include <IMeshData_Edge.hpp>

//! Default implementation of model entity.
class BRepMeshData_Model : public IMeshData_Model
{
public:
  //! Constructor.
  //! Initializes empty model.
  Standard_EXPORT BRepMeshData_Model(const TopoDS_Shape& theShape);

  //! Destructor.
  Standard_EXPORT ~BRepMeshData_Model() override;

  //! Returns maximum size of shape's bounding box.
  double GetMaxSize() const override { return myMaxSize; }

  //! Sets maximum size of shape's bounding box.
  void SetMaxSize(const double theValue) { myMaxSize = theValue; }

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Model, IMeshData_Model)

public: //! @name discrete faces
  //! Returns number of faces in discrete model.
  Standard_EXPORT int FacesNb() const override;

  //! Adds new face to shape model.
  Standard_EXPORT const IMeshData::IFaceHandle& AddFace(const TopoDS_Face& theFace) override;

  //! Gets model's face with the given index.
  Standard_EXPORT const IMeshData::IFaceHandle& GetFace(const int theIndex) const override;

public: //! @name discrete edges
  //! Returns number of edges in discrete model.
  Standard_EXPORT int EdgesNb() const override;

  //! Adds new edge to shape model.
  Standard_EXPORT const IMeshData::IEdgeHandle& AddEdge(const TopoDS_Edge& theEdge) override;

  //! Gets model's edge with the given index.
  Standard_EXPORT const IMeshData::IEdgeHandle& GetEdge(const int theIndex) const override;

private:
  double                                myMaxSize;
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::VectorOfIFaceHandles       myDFaces;
  IMeshData::VectorOfIEdgeHandles       myDEdges;
};

