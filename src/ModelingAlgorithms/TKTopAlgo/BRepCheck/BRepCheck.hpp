#pragma once

#include <Adaptor3d_Surface.hpp>
#include <BRepCheck_Status.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <Standard_OStream.hpp>

class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Edge;
class Adaptor3d_Curve;

//! This package provides tools to check the validity
//! of the BRep.
class BRepCheck
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Add(NCollection_List<BRepCheck_Status>& List,
                                  const BRepCheck_Status              Stat);

  Standard_EXPORT static void Print(const BRepCheck_Status Stat, Standard_OStream& OS);

  Standard_EXPORT static bool SelfIntersection(const TopoDS_Wire& W,
                                               const TopoDS_Face& F,
                                               TopoDS_Edge&       E1,
                                               TopoDS_Edge&       E2);

  //! Returns the resolution on the 3d curve
  Standard_EXPORT static double PrecCurve(const Adaptor3d_Curve& aAC3D);

  //! Returns the resolution on the surface
  Standard_EXPORT static double PrecSurface(const occ::handle<Adaptor3d_Surface>& aAHSurf);
};
