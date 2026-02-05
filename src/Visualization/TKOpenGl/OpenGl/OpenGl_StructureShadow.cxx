#include <OpenGl_StructureShadow.hpp>

#include <Graphic3d_GraphicDriver.hpp>
#include <Standard_ProgramError.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_StructureShadow, OpenGl_Structure)

//=================================================================================================

OpenGl_StructureShadow::OpenGl_StructureShadow(
  const occ::handle<Graphic3d_StructureManager>& theManager,
  const occ::handle<OpenGl_Structure>&           theStructure)
    : OpenGl_Structure(theManager)
{
  occ::handle<OpenGl_StructureShadow> aShadow =
    occ::down_cast<OpenGl_StructureShadow>(theStructure);
  myParent = aShadow.IsNull() ? theStructure : aShadow->myParent;

  IsInfinite = myParent->IsInfinite;
  myBndBox   = myParent->BoundingBox();

  OpenGl_Structure::SetTransformation(myParent->Transformation());
  myInstancedStructure = const_cast<OpenGl_Structure*>(myParent->InstancedStructure());
  myTrsfPers           = myParent->TransformPersistence();

  // reuse instanced structure API
  myInstancedStructure = myParent.operator->();
}

//=================================================================================================

void OpenGl_StructureShadow::Connect(Graphic3d_CStructure&)
{
  throw Standard_ProgramError("Error! OpenGl_StructureShadow::Connect() should not be called!");
}

//=================================================================================================

void OpenGl_StructureShadow::Disconnect(Graphic3d_CStructure&)
{
  throw Standard_ProgramError("Error! OpenGl_StructureShadow::Disconnect() should not be called!");
}
