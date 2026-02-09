#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <IntCurveSurface_Intersection.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>

class IntCurveSurface_TheHCurveTool;
class Adaptor3d_HSurfaceTool;
class IntCurveSurface_ThePolygonOfHInter;
class IntCurveSurface_ThePolygonToolOfHInter;
class IntCurveSurface_ThePolyhedronOfHInter;
class IntCurveSurface_ThePolyhedronToolOfHInter;
class IntCurveSurface_TheInterferenceOfHInter;
class IntCurveSurface_TheCSFunctionOfHInter;
class IntCurveSurface_TheExactHInter;
class IntCurveSurface_TheQuadCurvExactHInter;
class IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter;
class Bnd_BoundSortBox;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;
class IntAna_IntConicQuad;
class Bnd_Box;

class IntCurveSurface_HInter : public IntCurveSurface_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_HInter();

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&   Curve,
                               const occ::handle<Adaptor3d_Surface>& Surface);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&       Curve,
                               const IntCurveSurface_ThePolygonOfHInter& Polygon,
                               const occ::handle<Adaptor3d_Surface>&     Surface);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&          Curve,
                               const IntCurveSurface_ThePolygonOfHInter&    ThePolygon,
                               const occ::handle<Adaptor3d_Surface>&        Surface,
                               const IntCurveSurface_ThePolyhedronOfHInter& Polyhedron);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&          Curve,
                               const IntCurveSurface_ThePolygonOfHInter&    ThePolygon,
                               const occ::handle<Adaptor3d_Surface>&        Surface,
                               const IntCurveSurface_ThePolyhedronOfHInter& Polyhedron,
                               Bnd_BoundSortBox&                            BndBSB);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&          Curve,
                               const occ::handle<Adaptor3d_Surface>&        Surface,
                               const IntCurveSurface_ThePolyhedronOfHInter& Polyhedron);

protected:
  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>&   Curve,
                               const occ::handle<Adaptor3d_Surface>& Surface,
                               const double                          U0,
                               const double                          V0,
                               const double                          U1,
                               const double                          V1);

  Standard_EXPORT void InternalPerformCurveQuadric(const occ::handle<Adaptor3d_Curve>&   Curve,
                                                   const occ::handle<Adaptor3d_Surface>& Surface);

  Standard_EXPORT void InternalPerform(const occ::handle<Adaptor3d_Curve>&          Curve,
                                       const IntCurveSurface_ThePolygonOfHInter&    Polygon,
                                       const occ::handle<Adaptor3d_Surface>&        Surface,
                                       const IntCurveSurface_ThePolyhedronOfHInter& Polyhedron,
                                       const double                                 U1,
                                       const double                                 V1,
                                       const double                                 U2,
                                       const double                                 V2);

  Standard_EXPORT void InternalPerform(const occ::handle<Adaptor3d_Curve>&          Curve,
                                       const IntCurveSurface_ThePolygonOfHInter&    Polygon,
                                       const occ::handle<Adaptor3d_Surface>&        Surface,
                                       const IntCurveSurface_ThePolyhedronOfHInter& Polyhedron,
                                       const double                                 U1,
                                       const double                                 V1,
                                       const double                                 U2,
                                       const double                                 V2,
                                       Bnd_BoundSortBox&                            BSB);

  Standard_EXPORT void InternalPerform(const occ::handle<Adaptor3d_Curve>&       Curve,
                                       const IntCurveSurface_ThePolygonOfHInter& Polygon,
                                       const occ::handle<Adaptor3d_Surface>&     Surface,
                                       const double                              U1,
                                       const double                              V1,
                                       const double                              U2,
                                       const double                              V2);

  Standard_EXPORT void PerformConicSurf(const gp_Lin&                         Line,
                                        const occ::handle<Adaptor3d_Curve>&   Curve,
                                        const occ::handle<Adaptor3d_Surface>& Surface,
                                        const double                          U1,
                                        const double                          V1,
                                        const double                          U2,
                                        const double                          V2);

  Standard_EXPORT void PerformConicSurf(const gp_Circ&                        Circle,
                                        const occ::handle<Adaptor3d_Curve>&   Curve,
                                        const occ::handle<Adaptor3d_Surface>& Surface,
                                        const double                          U1,
                                        const double                          V1,
                                        const double                          U2,
                                        const double                          V2);

  Standard_EXPORT void PerformConicSurf(const gp_Elips&                       Ellipse,
                                        const occ::handle<Adaptor3d_Curve>&   Curve,
                                        const occ::handle<Adaptor3d_Surface>& Surface,
                                        const double                          U1,
                                        const double                          V1,
                                        const double                          U2,
                                        const double                          V2);

  Standard_EXPORT void PerformConicSurf(const gp_Parab&                       Parab,
                                        const occ::handle<Adaptor3d_Curve>&   Curve,
                                        const occ::handle<Adaptor3d_Surface>& Surface,
                                        const double                          U1,
                                        const double                          V1,
                                        const double                          U2,
                                        const double                          V2);

  Standard_EXPORT void PerformConicSurf(const gp_Hypr&                        Hyper,
                                        const occ::handle<Adaptor3d_Curve>&   Curve,
                                        const occ::handle<Adaptor3d_Surface>& Surface,
                                        const double                          U1,
                                        const double                          V1,
                                        const double                          U2,
                                        const double                          V2);

  Standard_EXPORT void AppendIntAna(const occ::handle<Adaptor3d_Curve>&   Curve,
                                    const occ::handle<Adaptor3d_Surface>& Surface,
                                    const IntAna_IntConicQuad&            InterAna);

  Standard_EXPORT void AppendPoint(const occ::handle<Adaptor3d_Curve>&   Curve,
                                   const double                          w,
                                   const occ::handle<Adaptor3d_Surface>& Surface,
                                   const double                          u,
                                   const double                          v);

  Standard_EXPORT void AppendSegment(const occ::handle<Adaptor3d_Curve>&   Curve,
                                     const double                          u0,
                                     const double                          u1,
                                     const occ::handle<Adaptor3d_Surface>& Surface);

private:
  Standard_EXPORT void DoSurface(const occ::handle<Adaptor3d_Surface>& surface,
                                 const double                          u0,
                                 const double                          u1,
                                 const double                          v0,
                                 const double                          v1,
                                 NCollection_Array2<gp_Pnt>&           pntsOnSurface,
                                 Bnd_Box&                              boxSurface,
                                 double&                               gap);

  Standard_EXPORT void DoNewBounds(const occ::handle<Adaptor3d_Surface>& surface,
                                   const double                          u0,
                                   const double                          u1,
                                   const double                          v0,
                                   const double                          v1,
                                   const NCollection_Array2<gp_Pnt>&     pntsOnSurface,
                                   const NCollection_Array1<double>&     X,
                                   const NCollection_Array1<double>&     Y,
                                   const NCollection_Array1<double>&     Z,
                                   NCollection_Array1<double>&           Bounds);
};
