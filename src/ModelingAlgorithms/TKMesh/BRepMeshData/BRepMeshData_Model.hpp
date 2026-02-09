#pragma once

#include <IMeshData_Model.hpp>
#include <IMeshData_Types.hpp>
#include <NCollection_IncAllocator.hpp>
#include <IMeshData_Edge.hpp>

class BRepMeshData_Model : public IMeshData_Model
{
public:
  Standard_EXPORT BRepMeshData_Model(const TopoDS_Shape& theShape);

  Standard_EXPORT ~BRepMeshData_Model() override;

  double GetMaxSize() const override { return myMaxSize; }

  void SetMaxSize(const double theValue) { myMaxSize = theValue; }

  DEFINE_STANDARD_RTTIEXT(BRepMeshData_Model, IMeshData_Model)

public:
  Standard_EXPORT int FacesNb() const override;

  Standard_EXPORT const IMeshData::IFaceHandle& AddFace(const TopoDS_Face& theFace) override;

  Standard_EXPORT const IMeshData::IFaceHandle& GetFace(const int theIndex) const override;

public:
  Standard_EXPORT int EdgesNb() const override;

  Standard_EXPORT const IMeshData::IEdgeHandle& AddEdge(const TopoDS_Edge& theEdge) override;

  Standard_EXPORT const IMeshData::IEdgeHandle& GetEdge(const int theIndex) const override;

private:
  double                                myMaxSize;
  occ::handle<NCollection_IncAllocator> myAllocator;
  IMeshData::VectorOfIFaceHandles       myDFaces;
  IMeshData::VectorOfIEdgeHandles       myDEdges;
};
