#include <XBRepMesh.hpp>
#include <BRepMesh_PluginMacro.hpp>
#include <BRepMesh_IncrementalMesh.hpp>

//=================================================================================================

int XBRepMesh::Discret(const TopoDS_Shape&    theShape,
                       const double           theDeflection,
                       const double           theAngle,
                       BRepMesh_DiscretRoot*& theAlgo)
{
  int iErr;
  //
  iErr                                  = 0;
  BRepMesh_IncrementalMesh* anAlgo      = new BRepMesh_IncrementalMesh;
  anAlgo->ChangeParameters().Deflection = theDeflection;
  anAlgo->ChangeParameters().Angle      = theAngle;
  anAlgo->SetShape(theShape);
  theAlgo = anAlgo;

  return iErr;
}
DISCRETPLUGIN(XBRepMesh)
