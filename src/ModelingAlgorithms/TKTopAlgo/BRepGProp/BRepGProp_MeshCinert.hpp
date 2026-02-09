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

class BRepGProp_MeshCinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_MeshCinert();

  Standard_EXPORT void SetLocation(const gp_Pnt& CLocation);

  Standard_EXPORT void Perform(const NCollection_Array1<gp_Pnt>& theNodes);

  Standard_EXPORT static void PreparePolygon(const TopoDS_Edge&                        theE,
                                             occ::handle<NCollection_HArray1<gp_Pnt>>& thePolyg);
};
