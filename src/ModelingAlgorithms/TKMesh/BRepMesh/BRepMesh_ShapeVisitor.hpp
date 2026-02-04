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

//! Builds discrete model of a shape by adding faces and free edges.
//! Computes deflection for corresponded shape and checks whether it
//! fits existing polygonal representation. If not, cleans shape from
//! outdated info.
class BRepMesh_ShapeVisitor : public IMeshTools_ShapeVisitor
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_ShapeVisitor(const occ::handle<IMeshData_Model>& theModel);

  //! Destructor.
  Standard_EXPORT ~BRepMesh_ShapeVisitor() override;

  //! Handles TopoDS_Face object.
  Standard_EXPORT void Visit(const TopoDS_Face& theFace) override;

  //! Handles TopoDS_Edge object.
  Standard_EXPORT void Visit(const TopoDS_Edge& theEdge) override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ShapeVisitor, IMeshTools_ShapeVisitor)

private:
  //! Adds wire to face discrete model.
  bool addWire(const TopoDS_Wire& theWire, const IMeshData::IFaceHandle& theDFace);

private:
  occ::handle<IMeshData_Model>  myModel;
  IMeshData::DMapOfShapeInteger myDEdgeMap;
};

