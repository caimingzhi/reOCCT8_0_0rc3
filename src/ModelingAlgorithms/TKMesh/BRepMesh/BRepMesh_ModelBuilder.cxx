#include <BRepMesh_ModelBuilder.hpp>
#include <BRepMeshData_Model.hpp>
#include <BRepMesh_ShapeVisitor.hpp>
#include <BRepMesh_ShapeTool.hpp>
#include <IMeshTools_ShapeExplorer.hpp>

#include <Bnd_Box.hpp>
#include <BRepBndLib.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_ModelBuilder, IMeshTools_ModelBuilder)

//=================================================================================================

BRepMesh_ModelBuilder::BRepMesh_ModelBuilder() = default;

//=================================================================================================

BRepMesh_ModelBuilder::~BRepMesh_ModelBuilder() = default;

//=================================================================================================

occ::handle<IMeshData_Model> BRepMesh_ModelBuilder::performInternal(
  const TopoDS_Shape&          theShape,
  const IMeshTools_Parameters& theParameters)
{
  occ::handle<BRepMeshData_Model> aModel;

  Bnd_Box aBox;
  BRepBndLib::Add(theShape, aBox, false);

  if (!aBox.IsVoid())
  {
    // Build data model for further processing.
    aModel = new BRepMeshData_Model(theShape);

    if (theParameters.Relative)
    {
      double aMaxSize;
      BRepMesh_ShapeTool::BoxMaxDimension(aBox, aMaxSize);
      aModel->SetMaxSize(aMaxSize);
    }
    else
    {
      aModel->SetMaxSize(std::max(theParameters.Deflection, theParameters.DeflectionInterior));
    }

    occ::handle<IMeshTools_ShapeVisitor> aVisitor = new BRepMesh_ShapeVisitor(aModel);

    IMeshTools_ShapeExplorer aExplorer(theShape);
    aExplorer.Accept(aVisitor);
    SetStatus(Message_Done1);
  }
  else
  {
    SetStatus(Message_Fail1);
  }

  return aModel;
}
