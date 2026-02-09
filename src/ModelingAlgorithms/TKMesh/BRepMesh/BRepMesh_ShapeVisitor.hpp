#pragma once

#include <IMeshTools_ShapeVisitor.hpp>
#include <IMeshData_Model.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <IMeshTools_Parameters.hpp>
#include <IMeshData_Types.hpp>

class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Wire;

class BRepMesh_ShapeVisitor : public IMeshTools_ShapeVisitor
{
public:
  Standard_EXPORT BRepMesh_ShapeVisitor(const occ::handle<IMeshData_Model>& theModel);

  Standard_EXPORT ~BRepMesh_ShapeVisitor() override;

  Standard_EXPORT void Visit(const TopoDS_Face& theFace) override;

  Standard_EXPORT void Visit(const TopoDS_Edge& theEdge) override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ShapeVisitor, IMeshTools_ShapeVisitor)

private:
  bool addWire(const TopoDS_Wire& theWire, const IMeshData::IFaceHandle& theDFace);

private:
  occ::handle<IMeshData_Model>  myModel;
  IMeshData::DMapOfShapeInteger myDEdgeMap;
};
