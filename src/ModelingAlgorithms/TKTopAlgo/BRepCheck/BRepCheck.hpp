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

  Standard_EXPORT static double PrecCurve(const Adaptor3d_Curve& aAC3D);

  Standard_EXPORT static double PrecSurface(const occ::handle<Adaptor3d_Surface>& aAHSurf);
};
