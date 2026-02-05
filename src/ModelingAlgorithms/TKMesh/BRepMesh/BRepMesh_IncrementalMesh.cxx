#include <BRepMesh_IncrementalMesh.hpp>
#include <BRepMesh_Context.hpp>
#include <BRepMesh_PluginMacro.hpp>
#include <IMeshData_Face.hpp>
#include <IMeshData_Wire.hpp>
#include <IMeshTools_MeshBuilder.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_IncrementalMesh, BRepMesh_DiscretRoot)

namespace
{
  //! Default flag to control parallelization for BRepMesh_IncrementalMesh
  //! tool returned for Mesh Factory
  static bool IS_IN_PARALLEL = false;
} // namespace

//=================================================================================================

BRepMesh_IncrementalMesh::BRepMesh_IncrementalMesh()
    : myModified(false),
      myStatus(IMeshData_NoError)
{
}

//=================================================================================================

BRepMesh_IncrementalMesh::BRepMesh_IncrementalMesh(const TopoDS_Shape& theShape,
                                                   const double        theLinDeflection,
                                                   const bool          isRelative,
                                                   const double        theAngDeflection,
                                                   const bool          isInParallel)
    : myModified(false),
      myStatus(IMeshData_NoError)
{
  myParameters.Deflection = theLinDeflection;
  myParameters.Angle      = theAngDeflection;
  myParameters.Relative   = isRelative;
  myParameters.InParallel = isInParallel;

  myShape = theShape;
  Perform();
}

//=================================================================================================

BRepMesh_IncrementalMesh::BRepMesh_IncrementalMesh(const TopoDS_Shape&          theShape,
                                                   const IMeshTools_Parameters& theParameters,
                                                   const Message_ProgressRange& theRange)
    : myParameters(theParameters)
{
  myShape = theShape;
  Perform(theRange);
}

//=================================================================================================

BRepMesh_IncrementalMesh::~BRepMesh_IncrementalMesh() = default;

//=================================================================================================

void BRepMesh_IncrementalMesh::Perform(const Message_ProgressRange& theRange)
{
  occ::handle<BRepMesh_Context> aContext = new BRepMesh_Context(myParameters.MeshAlgo);
  Perform(aContext, theRange);
}

//=================================================================================================

void BRepMesh_IncrementalMesh::Perform(const occ::handle<IMeshTools_Context>& theContext,
                                       const Message_ProgressRange&           theRange)
{
  initParameters();

  theContext->SetShape(Shape());
  theContext->ChangeParameters()            = myParameters;
  theContext->ChangeParameters().CleanModel = false;

  Message_ProgressScope  aPS(theRange, "Perform incmesh", 10);
  IMeshTools_MeshBuilder aIncMesh(theContext);
  aIncMesh.Perform(aPS.Next(9));
  if (!aPS.More())
  {
    myStatus = IMeshData_UserBreak;
    return;
  }
  myStatus                                   = IMeshData_NoError;
  const occ::handle<IMeshData_Model>& aModel = theContext->GetModel();
  if (!aModel.IsNull())
  {
    for (int aFaceIt = 0; aFaceIt < aModel->FacesNb(); ++aFaceIt)
    {
      const IMeshData::IFaceHandle& aDFace = aModel->GetFace(aFaceIt);
      myStatus |= aDFace->GetStatusMask();

      for (int aWireIt = 0; aWireIt < aDFace->WiresNb(); ++aWireIt)
      {
        const IMeshData::IWireHandle& aDWire = aDFace->GetWire(aWireIt);
        myStatus |= aDWire->GetStatusMask();
      }
    }
  }
  aPS.Next(1);
  setDone();
}

//=================================================================================================

int BRepMesh_IncrementalMesh::Discret(const TopoDS_Shape&    theShape,
                                      const double           theDeflection,
                                      const double           theAngle,
                                      BRepMesh_DiscretRoot*& theAlgo)
{
  BRepMesh_IncrementalMesh* anAlgo      = new BRepMesh_IncrementalMesh();
  anAlgo->ChangeParameters().Deflection = theDeflection;
  anAlgo->ChangeParameters().Angle      = theAngle;
  anAlgo->ChangeParameters().InParallel = IS_IN_PARALLEL;
  anAlgo->SetShape(theShape);
  theAlgo = anAlgo;
  return 0; // no error
}

//=================================================================================================

bool BRepMesh_IncrementalMesh::IsParallelDefault()
{
  return IS_IN_PARALLEL;
}

//=================================================================================================

void BRepMesh_IncrementalMesh::SetParallelDefault(const bool theInParallel)
{
  IS_IN_PARALLEL = theInParallel;
}

//! Export Mesh Plugin entry function
DISCRETPLUGIN(BRepMesh_IncrementalMesh)
