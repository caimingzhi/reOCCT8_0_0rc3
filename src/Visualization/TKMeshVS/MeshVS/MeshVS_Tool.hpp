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

//! This class provides auxiliary methods to create different aspects
class MeshVS_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates fill area aspect with values from Drawer according to keys from DrawerAttribute
  Standard_EXPORT static occ::handle<Graphic3d_AspectFillArea3d> CreateAspectFillArea3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  //! Creates fill aspect with values from Drawer according to keys from DrawerAttribute
  //! and specific material aspect
  Standard_EXPORT static occ::handle<Graphic3d_AspectFillArea3d> CreateAspectFillArea3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const Graphic3d_MaterialAspect&   Mat,
    const bool                        UseDefaults = true);

  //! Creates line aspect with values from Drawer according to keys from DrawerAttribute
  Standard_EXPORT static occ::handle<Graphic3d_AspectLine3d> CreateAspectLine3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  //! Creates marker aspect with values from Drawer according to keys from DrawerAttribute
  Standard_EXPORT static occ::handle<Graphic3d_AspectMarker3d> CreateAspectMarker3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  //! Creates text aspect with values from Drawer according to keys from DrawerAttribute
  Standard_EXPORT static occ::handle<Graphic3d_AspectText3d> CreateAspectText3d(
    const occ::handle<MeshVS_Drawer>& theDr,
    const bool                        UseDefaults = true);

  //! Get one of normals to polygon described by these points.
  //! If the polygon isn't planar, function returns false
  Standard_EXPORT static bool GetNormal(const NCollection_Array1<double>& Nodes, gp_Vec& Norm);

  //! Get an average of normals to non-planar polygon described by these points or compute
  //! normal of planar polygon. If the polygon isn't planar, function returns false
  Standard_EXPORT static bool GetAverageNormal(const NCollection_Array1<double>& Nodes,
                                               gp_Vec&                           Norm);
};

