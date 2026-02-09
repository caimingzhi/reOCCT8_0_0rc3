#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_Filling.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Face;
class TopoDS_Edge;
class gp_Pnt;
class TopoDS_Shape;

class BRepOffsetAPI_MakeFilling : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakeFilling(const int    Degree      = 3,
                                            const int    NbPtsOnCur  = 15,
                                            const int    NbIter      = 2,
                                            const bool   Anisotropie = false,
                                            const double Tol2d       = 0.00001,
                                            const double Tol3d       = 0.0001,
                                            const double TolAng      = 0.01,
                                            const double TolCurv     = 0.1,
                                            const int    MaxDeg      = 8,
                                            const int    MaxSegments = 9);

  Standard_EXPORT void SetConstrParam(const double Tol2d   = 0.00001,
                                      const double Tol3d   = 0.0001,
                                      const double TolAng  = 0.01,
                                      const double TolCurv = 0.1);

  Standard_EXPORT void SetResolParam(const int  Degree      = 3,
                                     const int  NbPtsOnCur  = 15,
                                     const int  NbIter      = 2,
                                     const bool Anisotropie = false);

  Standard_EXPORT void SetApproxParam(const int MaxDeg = 8, const int MaxSegments = 9);

  Standard_EXPORT void LoadInitSurface(const TopoDS_Face& Surf);

  Standard_EXPORT int Add(const TopoDS_Edge&  Constr,
                          const GeomAbs_Shape Order,
                          const bool          IsBound = true);

  Standard_EXPORT int Add(const TopoDS_Edge&  Constr,
                          const TopoDS_Face&  Support,
                          const GeomAbs_Shape Order,
                          const bool          IsBound = true);

  Standard_EXPORT int Add(const TopoDS_Face& Support, const GeomAbs_Shape Order);

  Standard_EXPORT int Add(const gp_Pnt& Point);

  Standard_EXPORT int Add(const double        U,
                          const double        V,
                          const TopoDS_Face&  Support,
                          const GeomAbs_Shape Order);

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool IsDone() const override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT double G0Error() const;

  Standard_EXPORT double G1Error() const;

  Standard_EXPORT double G2Error() const;

  Standard_EXPORT double G0Error(const int Index);

  Standard_EXPORT double G1Error(const int Index);

  Standard_EXPORT double G2Error(const int Index);

private:
  BRepFill_Filling myFilling;
};
