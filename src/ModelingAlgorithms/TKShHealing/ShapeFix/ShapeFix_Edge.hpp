#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeConstruct_ProjectCurveOnSurface;
class TopoDS_Edge;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class ShapeAnalysis_Surface;
class ShapeBuild_ReShape;

#ifdef Status
  #undef Status
#endif

class ShapeFix_Edge : public Standard_Transient
{

public:
  Standard_EXPORT ShapeFix_Edge();

  Standard_EXPORT occ::handle<ShapeConstruct_ProjectCurveOnSurface> Projector();

  Standard_EXPORT bool FixRemovePCurve(const TopoDS_Edge& edge, const TopoDS_Face& face);

  Standard_EXPORT bool FixRemovePCurve(const TopoDS_Edge&               edge,
                                       const occ::handle<Geom_Surface>& surface,
                                       const TopLoc_Location&           location);

  Standard_EXPORT bool FixRemoveCurve3d(const TopoDS_Edge& edge);

  Standard_EXPORT bool FixAddPCurve(const TopoDS_Edge& edge,
                                    const TopoDS_Face& face,
                                    const bool         isSeam,
                                    const double       prec = 0.0);

  Standard_EXPORT bool FixAddPCurve(const TopoDS_Edge&               edge,
                                    const occ::handle<Geom_Surface>& surface,
                                    const TopLoc_Location&           location,
                                    const bool                       isSeam,
                                    const double                     prec = 0.0);

  Standard_EXPORT bool FixAddPCurve(const TopoDS_Edge&                        edge,
                                    const TopoDS_Face&                        face,
                                    const bool                                isSeam,
                                    const occ::handle<ShapeAnalysis_Surface>& surfana,
                                    const double                              prec = 0.0);

  Standard_EXPORT bool FixAddPCurve(const TopoDS_Edge&                        edge,
                                    const occ::handle<Geom_Surface>&          surface,
                                    const TopLoc_Location&                    location,
                                    const bool                                isSeam,
                                    const occ::handle<ShapeAnalysis_Surface>& surfana,
                                    const double                              prec = 0.0);

  Standard_EXPORT bool FixAddCurve3d(const TopoDS_Edge& edge);

  Standard_EXPORT bool FixVertexTolerance(const TopoDS_Edge& edge, const TopoDS_Face& face);

  Standard_EXPORT bool FixVertexTolerance(const TopoDS_Edge& edge);

  Standard_EXPORT bool FixReversed2d(const TopoDS_Edge& edge, const TopoDS_Face& face);

  Standard_EXPORT bool FixReversed2d(const TopoDS_Edge&               edge,
                                     const occ::handle<Geom_Surface>& surface,
                                     const TopLoc_Location&           location);

  Standard_EXPORT bool FixSameParameter(const TopoDS_Edge& edge, const double tolerance = 0.0);

  Standard_EXPORT bool FixSameParameter(const TopoDS_Edge& edge,
                                        const TopoDS_Face& face,
                                        const double       tolerance = 0.0);

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT void SetContext(const occ::handle<ShapeBuild_ReShape>& context);

  Standard_EXPORT occ::handle<ShapeBuild_ReShape> Context() const;

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Edge, Standard_Transient)

protected:
  occ::handle<ShapeBuild_ReShape>                   myContext;
  int                                               myStatus;
  occ::handle<ShapeConstruct_ProjectCurveOnSurface> myProjector;
};
