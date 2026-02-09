#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Geom2d_Curve.hpp>
#include <IGESToBRep_CurveAndSurface.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;
class IGESData_IGESEntity;
class TopoDS_Face;
class gp_Trsf2d;
class TopoDS_Vertex;
class IGESGeom_Point;
class IGESGeom_CompositeCurve;
class IGESGeom_OffsetCurve;
class IGESGeom_CurveOnSurface;
class IGESGeom_Boundary;
class Geom_BSplineCurve;
class Geom_Curve;
class Geom2d_BSplineCurve;
class Geom2d_Curve;

class IGESToBRep_TopoCurve : public IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESToBRep_TopoCurve();

  Standard_EXPORT IGESToBRep_TopoCurve(const IGESToBRep_CurveAndSurface& CS);

  Standard_EXPORT IGESToBRep_TopoCurve(const IGESToBRep_TopoCurve& CS);

  Standard_EXPORT IGESToBRep_TopoCurve(const double eps,
                                       const double epsGeom,
                                       const double epsCoeff,
                                       const bool   mode,
                                       const bool   modeapprox,
                                       const bool   optimized);

  Standard_EXPORT TopoDS_Shape TransferTopoCurve(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT TopoDS_Shape Transfer2dTopoCurve(const occ::handle<IGESData_IGESEntity>& start,
                                                   const TopoDS_Face&                      face,
                                                   const gp_Trsf2d&                        trans,
                                                   const double                            uFact);

  Standard_EXPORT TopoDS_Shape
    TransferTopoBasicCurve(const occ::handle<IGESData_IGESEntity>& start);

  Standard_EXPORT TopoDS_Shape
    Transfer2dTopoBasicCurve(const occ::handle<IGESData_IGESEntity>& start,
                             const TopoDS_Face&                      face,
                             const gp_Trsf2d&                        trans,
                             const double                            uFact);

  Standard_EXPORT TopoDS_Vertex TransferPoint(const occ::handle<IGESGeom_Point>& start);

  Standard_EXPORT TopoDS_Vertex Transfer2dPoint(const occ::handle<IGESGeom_Point>& start);

  Standard_EXPORT TopoDS_Shape
    TransferCompositeCurve(const occ::handle<IGESGeom_CompositeCurve>& start);

  Standard_EXPORT TopoDS_Shape
    Transfer2dCompositeCurve(const occ::handle<IGESGeom_CompositeCurve>& start,
                             const TopoDS_Face&                          face,
                             const gp_Trsf2d&                            trans,
                             const double                                uFact);

  Standard_EXPORT TopoDS_Shape TransferOffsetCurve(const occ::handle<IGESGeom_OffsetCurve>& start);

  Standard_EXPORT TopoDS_Shape Transfer2dOffsetCurve(const occ::handle<IGESGeom_OffsetCurve>& start,
                                                     const TopoDS_Face&                       face,
                                                     const gp_Trsf2d&                         trans,
                                                     const double uFact);

  Standard_EXPORT TopoDS_Shape
    TransferCurveOnSurface(const occ::handle<IGESGeom_CurveOnSurface>& start);

  Standard_EXPORT TopoDS_Shape
    TransferCurveOnFace(TopoDS_Face&                                face,
                        const occ::handle<IGESGeom_CurveOnSurface>& start,
                        const gp_Trsf2d&                            trans,
                        const double                                uFact,
                        const bool                                  IsCurv);

  Standard_EXPORT TopoDS_Shape TransferBoundary(const occ::handle<IGESGeom_Boundary>& start);

  Standard_EXPORT TopoDS_Shape TransferBoundaryOnFace(TopoDS_Face&                          face,
                                                      const occ::handle<IGESGeom_Boundary>& start,
                                                      const gp_Trsf2d&                      trans,
                                                      const double                          uFact);

  Standard_EXPORT void ApproxBSplineCurve(const occ::handle<Geom_BSplineCurve>& start);

  Standard_EXPORT int NbCurves() const;

  Standard_EXPORT occ::handle<Geom_Curve> Curve(const int num = 1) const;

  Standard_EXPORT void Approx2dBSplineCurve(const occ::handle<Geom2d_BSplineCurve>& start);

  Standard_EXPORT int NbCurves2d() const;

  Standard_EXPORT occ::handle<Geom2d_Curve> Curve2d(const int num = 1) const;

  Standard_EXPORT void SetBadCase(const bool value);

  Standard_EXPORT bool BadCase() const;

private:
  Standard_EXPORT TopoDS_Shape
    TransferCompositeCurveGeneral(const occ::handle<IGESGeom_CompositeCurve>& start,
                                  const bool                                  is2d,
                                  const TopoDS_Face&                          face,
                                  const gp_Trsf2d&                            trans,
                                  const double                                uFact);

  NCollection_Sequence<occ::handle<Geom_Curve>>   TheCurves;
  NCollection_Sequence<occ::handle<Geom2d_Curve>> TheCurves2d;
  bool                                            TheBadCase;
};
