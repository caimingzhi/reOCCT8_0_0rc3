#pragma once

#include <BRepAdaptor_Curve2d.hpp>
#include <ChFi3d_FilBuilder.hpp>
#include <ChFi3d_FilletShape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <ChFiDS_SurfData.hpp>
#include <NCollection_Sequence.hpp>
#include <math_Vector.hpp>
#include <TopAbs_Orientation.hpp>
#include <FilletSurf_StatusType.hpp>

class Adaptor3d_TopolTool;
class ChFiDS_Spine;
class Geom_Surface;
class Geom_Curve;
class Geom2d_Curve;
class Geom_TrimmedCurve;
class TopoDS_Shape;
class TopoDS_Face;

class FilletSurf_InternalBuilder : public ChFi3d_FilBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FilletSurf_InternalBuilder(const TopoDS_Shape&      S,
                                             const ChFi3d_FilletShape FShape = ChFi3d_Polynomial,
                                             const double             Ta     = 1.0e-2,
                                             const double             Tapp3d = 1.0e-4,
                                             const double             Tapp2d = 1.0e-5);

  Standard_EXPORT int Add(const NCollection_List<TopoDS_Shape>& E, const double R);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool Done() const;

  Standard_EXPORT int NbSurface() const;

  Standard_EXPORT const occ::handle<Geom_Surface>& SurfaceFillet(const int Index) const;

  Standard_EXPORT double TolApp3d(const int Index) const;

  Standard_EXPORT const TopoDS_Face& SupportFace1(const int Index) const;

  Standard_EXPORT const TopoDS_Face& SupportFace2(const int Index) const;

  Standard_EXPORT const occ::handle<Geom_Curve>& CurveOnFace1(const int Index) const;

  Standard_EXPORT const occ::handle<Geom_Curve>& CurveOnFace2(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurveOnFace1(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve1OnFillet(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurveOnFace2(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve2OnFillet(const int Index) const;

  Standard_EXPORT double FirstParameter() const;

  Standard_EXPORT double LastParameter() const;

  Standard_EXPORT FilletSurf_StatusType StartSectionStatus() const;

  Standard_EXPORT FilletSurf_StatusType EndSectionStatus() const;

  Standard_EXPORT void Simulate();

  Standard_EXPORT int NbSection(const int IndexSurf) const;

  Standard_EXPORT void Section(const int                       IndexSurf,
                               const int                       IndexSec,
                               occ::handle<Geom_TrimmedCurve>& Circ) const;

protected:
  Standard_EXPORT bool PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
                                   const occ::handle<Adaptor3d_TopolTool>&             I2,
                                   const double                                        MaxStep,
                                   const double                                        Fleche,
                                   const double                                        TolGuide,
                                   double&                                             First,
                                   double&                                             Last,
                                   const bool                                          Inside,
                                   const bool                                          Appro,
                                   const bool                                          Forward,
                                   const bool                                          RecOnS1,
                                   const bool                                          RecOnS2,
                                   const math_Vector&                                  Soldep,
                                   int&                                                Intf,
                                   int& Intl) override;

  Standard_EXPORT void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC1,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref1,
                                   bool&                                               Decroch1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
                                   const occ::handle<Adaptor3d_TopolTool>&             I2,
                                   const TopAbs_Orientation                            Or2,
                                   const double                                        MaxStep,
                                   const double                                        Fleche,
                                   const double                                        TolGuide,
                                   double&                                             First,
                                   double&                                             Last,
                                   const bool                                          Inside,
                                   const bool                                          Appro,
                                   const bool                                          Forward,
                                   const bool                                          RecP,
                                   const bool                                          RecS,
                                   const bool                                          RecRst,
                                   const math_Vector& Soldep) override;

  Standard_EXPORT void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& SeqData,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const TopAbs_Orientation                            Or1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
                                   const occ::handle<Adaptor3d_TopolTool>&             I2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC2,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref2,
                                   bool&                                               Decroch2,
                                   const double                                        MaxStep,
                                   const double                                        Fleche,
                                   const double                                        TolGuide,
                                   double&                                             First,
                                   double&                                             Last,
                                   const bool                                          Inside,
                                   const bool                                          Appro,
                                   const bool                                          Forward,
                                   const bool                                          RecP,
                                   const bool                                          RecS,
                                   const bool                                          RecRst,
                                   const math_Vector& Soldep) override;

  Standard_EXPORT void PerformSurf(NCollection_Sequence<occ::handle<ChFiDS_SurfData>>& Data,
                                   const occ::handle<ChFiDS_ElSpine>&                  Guide,
                                   const occ::handle<ChFiDS_Spine>&                    Spine,
                                   const int                                           Choix,
                                   const occ::handle<BRepAdaptor_Surface>&             S1,
                                   const occ::handle<Adaptor3d_TopolTool>&             I1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC1,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref1,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref1,
                                   bool&                                               Decroch1,
                                   const TopAbs_Orientation                            Or1,
                                   const occ::handle<BRepAdaptor_Surface>&             S2,
                                   const occ::handle<Adaptor3d_TopolTool>&             I2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PC2,
                                   const occ::handle<BRepAdaptor_Surface>&             Sref2,
                                   const occ::handle<BRepAdaptor_Curve2d>&             PCref2,
                                   bool&                                               Decroch2,
                                   const TopAbs_Orientation                            Or2,
                                   const double                                        MaxStep,
                                   const double                                        Fleche,
                                   const double                                        TolGuide,
                                   double&                                             First,
                                   double&                                             Last,
                                   const bool                                          Inside,
                                   const bool                                          Appro,
                                   const bool                                          Forward,
                                   const bool                                          RecP1,
                                   const bool                                          RecRst1,
                                   const bool                                          RecP2,
                                   const bool                                          RecRst2,
                                   const math_Vector& Soldep) override;
};
