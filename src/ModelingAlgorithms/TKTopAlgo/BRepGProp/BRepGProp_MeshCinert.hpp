#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GProp_GProps.hpp>
class gp_Pnt;
class TopoDS_Edge;

//! Computes the global properties of
//! of polylines represented by set of points.
//! This class is used for computation of global
//! properties of edge, which has no exact geometry
//! (3d or 2d curve), but has any of allowed
//! polygons.
//!
class BRepGProp_MeshCinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_MeshCinert();

  Standard_EXPORT void SetLocation(const gp_Pnt& CLocation);

  //! Computes the global properties of
  //! of polylines represented by set of points.
  Standard_EXPORT void Perform(const NCollection_Array1<gp_Pnt>& theNodes);

  //! Prepare set of 3d points on base of any available edge polygons:
  //! 3D polygon, polygon on triangulation, 2d polygon on surface
  //! If edge has no polygons, array thePolyg is left unchanged
  Standard_EXPORT static void PreparePolygon(const TopoDS_Edge&                        theE,
                                             occ::handle<NCollection_HArray1<gp_Pnt>>& thePolyg);
};

