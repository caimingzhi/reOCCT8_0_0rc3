#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Draw_Drawable3D.hpp>
class MeshVS_Mesh;
class Draw_Display;

class XSDRAWSTL_DrawableMesh : public Draw_Drawable3D
{

public:
  Standard_EXPORT XSDRAWSTL_DrawableMesh(const occ::handle<MeshVS_Mesh>& aMesh);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<MeshVS_Mesh> GetMesh() const;

  DEFINE_STANDARD_RTTIEXT(XSDRAWSTL_DrawableMesh, Draw_Drawable3D)

private:
  occ::handle<MeshVS_Mesh> myMesh;
};

