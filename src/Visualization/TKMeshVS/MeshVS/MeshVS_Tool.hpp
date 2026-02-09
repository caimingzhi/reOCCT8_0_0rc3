#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
class Graphic3d_AspectFillArea3d;
class MeshVS_Drawer;
class Graphic3d_MaterialAspect;
class Graphic3d_AspectLine3d;
class Graphic3d_AspectMarker3d;
class Graphic3d_AspectText3d;
class gp_Vec;

class MeshVS_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Graphic3d_AspectFillArea3d> CreateAspectFillArea3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  Standard_EXPORT static occ::handle<Graphic3d_AspectFillArea3d> CreateAspectFillArea3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const Graphic3d_MaterialAspect&   Mat,
    const bool                        UseDefaults = true);

  Standard_EXPORT static occ::handle<Graphic3d_AspectLine3d> CreateAspectLine3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  Standard_EXPORT static occ::handle<Graphic3d_AspectMarker3d> CreateAspectMarker3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  Standard_EXPORT static occ::handle<Graphic3d_AspectText3d> CreateAspectText3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  Standard_EXPORT static bool GetNormal(const NCollection_Array1<double>& Nodes, gp_Vec& Norm);

  Standard_EXPORT static bool GetAverageNormal(const NCollection_Array1<double>& Nodes,
                                               gp_Vec&                           Norm);
};
