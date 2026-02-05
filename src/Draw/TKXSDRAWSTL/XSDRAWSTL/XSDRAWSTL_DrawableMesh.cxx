#include <Draw_Display.hpp>
#include <MeshVS_Mesh.hpp>
#include <Standard_Type.hpp>
#include <XSDRAWSTL_DrawableMesh.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XSDRAWSTL_DrawableMesh, Draw_Drawable3D)

//=================================================================================================

XSDRAWSTL_DrawableMesh::XSDRAWSTL_DrawableMesh(const occ::handle<MeshVS_Mesh>& aMesh)
{
  myMesh = aMesh;
}

//=================================================================================================

void XSDRAWSTL_DrawableMesh::DrawOn(Draw_Display& /*d*/) const {}

//=================================================================================================

occ::handle<MeshVS_Mesh> XSDRAWSTL_DrawableMesh::GetMesh() const
{
  return myMesh;
}
